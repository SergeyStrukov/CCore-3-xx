/* SysFileSystem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysFileSystem.h>
#include <CCore/inc/sys/SysFileInternal.h>

#include <CCore/inc/Path.h>

namespace CCore {
namespace Sys {

/* namespace Private_SysFileSystem */

namespace Private_SysFileSystem {

/* functions */

StrLen Wildcard(StrLen dir)
 {
  return PathIsBase(dir)? "*"_c : "/*"_c ;
 }

StrLen Dotcard(StrLen dir)
 {
  return PathIsBase(dir)? "."_c : ""_c ;
 }

/* class EmptyDirEngine */

class EmptyDirEngine : NoCopy
 {
   WChar buf[MaxPathLen+1];
   Win64::FindFileData data;

  private:

   FileError deleteDir(ulen dir_len)
    {
     if( FileError fe=emptyDir(dir_len) ) return fe;

     buf[dir_len]=0;

     return MakeErrorIf(FileError_OpFault, !Win64::RemoveDirectoryW(buf) );
    }

   bool set(ulen dir_len,const WChar *file_name,ulen len)
    {
     if( len>MaxPathLen-dir_len ) return false;

     Range(file_name,len).copyTo(buf+dir_len);

     buf[dir_len+len]=0;

     return true;
    }

   FileError remove(ulen dir_len,const WChar *file_name,ulen len,bool is_dir)
    {
     if( !set(dir_len+1,file_name,len) ) return FileError_TooLongPath;

     if( is_dir )
       {
        return deleteDir(dir_len+1+len);
       }
     else
       {
        if( !Win64::DeleteFileW(buf) ) return MakeError(FileError_OpFault);

        return FileError_Ok;
       }
    }

   static bool IsDot(const WChar *file_name,ulen len)
    {
     return len==1 && file_name[0]=='.' ;
    }

   static bool IsDotDot(const WChar *file_name,ulen len)
    {
     return len==2 && file_name[0]=='.' && file_name[1]=='.' ;
    }

   static bool IsSpecial(const WChar *file_name,ulen len)
    {
     return IsDot(file_name,len) || IsDotDot(file_name,len) ;
    }

   FileError emptyDir(ulen dir_len)
    {
     if( dir_len>MaxPathLen-2 ) return FileError_TooLongPath;

     buf[dir_len]='/';
     buf[dir_len+1]='*';
     buf[dir_len+2]=0;

     Win64::handle_t h_find=Win64::FindFirstFileW(buf,&data);

     if( h_find==Win64::InvalidFileHandle ) return MakeError(FileError_OpFault);

     do
       {
        ulen len=ZLen(data.file_name);

        if( !IsSpecial(data.file_name,len) )
          {
           if( FileError fe=remove(dir_len,data.file_name,len,data.attr&Win64::FileAttributes_Directory) )
             {
              Win64::FindClose(h_find);

              return fe;
             }
          }
       }
     while( Win64::FindNextFileW(h_find,&data) );

     Win64::error_t error_=Win64::GetLastError();

     Win64::FindClose(h_find);

     if( error_!=Win64::ErrorNoMoreFiles ) return MakeError(FileError_OpFault,error_);

     return FileError_Ok;
    }

  public:

   EmptyDirEngine() {}

   FileError emptyDir(const WChar *dir_name,ulen len)
    {
     if( len>MaxPathLen ) return FileError_TooLongPath;

     Range(dir_name,len).copyTo(buf);

     return emptyDir(len);
    }
 };

/* DeleteDirRecursive() */

FileError DeleteDirRecursive(const WChar *dir_name,ulen len)
 {
  EmptyDirEngine engine;

  if( FileError fe=engine.emptyDir(dir_name,len) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win64::RemoveDirectoryW(dir_name) );
 }

/* Execz() */

FileError Execz(const WChar *dir,const WChar *program,WChar *arg)
 {
  Win64::flags_t flags=Win64::CreateNewConsole;

  Win64::StartupInfo info{};

  info.cb=sizeof info;

  Win64::ProcessInfo pinfo;

  if( Win64::CreateProcessW(program,arg,0,0,false,flags,0,dir,&info,&pinfo) )
    {
     Win64::CloseHandle(pinfo.h_process);
     Win64::CloseHandle(pinfo.h_thread);

     return FileError_Ok;
    }
  else
    {
     return MakeError(FileError_OpFault);
    }
 }

} // namespace Private_SysFileSystem

using namespace Private_SysFileSystem;

/* struct FileSystem::DirCursor */

void FileSystem::DirCursor::init(FileSystem *,StrLen dir_name) noexcept
 {
  is_closed=true;

  if( !dir_name )
    {
     error=FileError_BadName;

     return;
    }

  FileName path;

  if( auto fe=path.prepare(dir_name,Wildcard(dir_name)) )
    {
     error=fe;
    }
  else
    {
     Win64::FindFileData data;

     handle=Win64::FindFirstFileW(path,&data);

     if( handle==Win64::InvalidFileHandle )
       {
        Win64::error_t error_=Win64::GetLastError();

        if( error_!=Win64::ErrorFileNotFound )
          {
           error=MakeError(FileError_OpFault,error_);
          }
        else
          {
           error=FileError_Ok;
          }
       }
     else
       {
        len=Full(data.file_name,Range(file_name));

        if( len==MaxULen )
          {
           Win64::FindClose(handle);

           error=FileError_TooLongPath;
          }
        else
          {
           is_first=true;
           is_closed=false;

           type=(data.attr&Win64::FileAttributes_Directory)?FileType_dir:FileType_file;

           error=FileError_Ok;
          }
       }
    }
 }

void FileSystem::DirCursor::exit() noexcept
 {
  if( !is_closed )
    {
     Win64::FindClose(handle);
    }
 }

bool FileSystem::DirCursor::next() noexcept
 {
  if( is_closed ) return false;

  if( is_first )
    {
     is_first=false;

     return true;
    }

  Win64::FindFileData data;

  if( FindNextFileW(handle,&data) )
    {
     len=Full(data.file_name,Range(file_name));

     if( len==MaxULen )
       {
        is_closed=true;

        Win64::FindClose(handle);

        error=FileError_TooLongPath;

        return false;
       }
     else
       {
        type=(data.attr&Win64::FileAttributes_Directory)?FileType_dir:FileType_file;

        return true;
       }
    }

  Win64::error_t error_=Win64::GetLastError();

  if( error_!=Win64::ErrorNoMoreFiles )
    {
     error=MakeError(FileError_OpFault,error_);
    }

  is_closed=true;

  Win64::FindClose(handle);

  return false;
 }

/* struct FileSystem */

FileError FileSystem::init() noexcept
 {
  return FileError_Ok;
 }

FileError FileSystem::exit() noexcept
 {
  return FileError_Ok;
 }

auto FileSystem::getFileType(StrLen path_) noexcept -> TypeResult
 {
  TypeResult ret;
  FileName path;

  if( auto fe=path.prepare(path_) )
    {
     ret.type=FileType_none;
     ret.error=fe;
    }
  else
    {
     Win64::flags_t attr=Win64::GetFileAttributesW(path);

     if( attr==Win64::InvalidFileAttributes )
       {
        ret.type=FileType_none;
        ret.error=FileError_Ok;
       }
     else
       {
        ret.type=(attr&Win64::FileAttributes_Directory)?FileType_dir:FileType_file;
        ret.error=FileError_Ok;
       }
    }

  return ret;
 }

auto FileSystem::getFileUpdateTime(StrLen path_) noexcept -> CmpTimeResult
 {
  CmpTimeResult ret;
  FileName path;

  if( auto fe=path.prepare(path_) )
    {
     ret.time=0;
     ret.error=fe;
    }
  else
    {
     Win64::handle_t h_file=Win64::CreateFileW(path,Win64::AccessRead,Win64::ShareRead,0,Win64::OpenExisting,Win64::FileBackupSemantic,0);

     if( h_file==Win64::InvalidFileHandle )
       {
        ret.time=0;
        ret.error=FileError_Ok;
       }
     else
       {
        Win64::FileTime result;

        if( Win64::GetFileTime(h_file,0,0,&result) )
          {
           ret.time=ToCmpFileTime(result);
           ret.error=FileError_Ok;
          }
        else
          {
           ret.time=0;
           ret.error=MakeError(FileError_OpFault);
          }

        Win64::CloseHandle(h_file);
       }
    }

  return ret;
 }

FileError FileSystem::createFile(StrLen file_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(file_name) ) return fe;

  Win64::flags_t access_flags = 0 ;

  Win64::flags_t share_flags = 0 ;

  Win64::options_t creation_options = Win64::CreateNew ;

  Win64::flags_t file_flags = Win64::FileAttributeNormal ;

  Win64::handle_t h_file = Win64::CreateFileW(path,access_flags,share_flags,0,creation_options,file_flags,0) ;

  if( h_file==Win64::InvalidFileHandle ) return MakeError(FileError_OpenFault);

  Win64::CloseHandle(h_file);

  return FileError_Ok;
 }

FileError FileSystem::deleteFile(StrLen file_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(file_name) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win64::DeleteFileW(path) );
 }

FileError FileSystem::createDir(StrLen dir_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(dir_name) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win64::CreateDirectoryW(path,0) );
 }

FileError FileSystem::deleteDir(StrLen dir_name,bool recursive) noexcept
 {
  if( !dir_name ) return FileError_BadName;

  FileName path;

  if( auto fe=path.prepare(dir_name,Dotcard(dir_name)) ) return fe;

  if( recursive ) return DeleteDirRecursive(path,path.len);

  return MakeErrorIf(FileError_OpFault, !Win64::RemoveDirectoryW(path) );
 }

FileError FileSystem::rename(StrLen old_path_,StrLen new_path_,bool allow_overwrite) noexcept
 {
  FileName old_path;

  if( auto fe=old_path.prepare(old_path_) ) return fe;

  FileName new_path;

  if( auto fe=new_path.prepare(new_path_) ) return fe;

  Win64::flags_t flags=allow_overwrite?Win64::MoveFileEx_AllowOverwrite:0;

  return MakeErrorIf(FileError_OpFault, !Win64::MoveFileExW(old_path,new_path,flags) );
 }

FileError FileSystem::remove(StrLen path_) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(path_) ) return fe;

  Win64::flags_t attr=Win64::GetFileAttributesW(path);

  if( attr==Win64::InvalidFileAttributes ) return MakeError(FileError_NoPath);

  if( attr&Win64::FileAttributes_Directory )
    {
     return MakeErrorIf(FileError_OpFault, !Win64::RemoveDirectoryW(path) );
    }
  else
    {
     return MakeErrorIf(FileError_OpFault, !Win64::DeleteFileW(path) );
    }
 }

FileError FileSystem::exec(StrLen dir,StrLen program,StrLen arg) noexcept
 {
  const ulen Len1=MaxPathLen+1;
  const ulen Len2=32_KByte;

  TempBuf<WChar> temp(2*Len1+Len2);

  if( !temp ) return FileError_SysOverload;

  WChar *dirz=temp;
  WChar *programz=dirz+Len1;
  WChar *argz=programz+Len1;

  if( auto fe=MakeZStr(dir,Range(dirz,Len1)).error ) return fe;

  if( auto fe=MakeZStr(program,Range(programz,Len1)).error ) return fe;

  if( auto fe=MakeZStr(arg,Range(argz,Len2)).error ) return fe;

  return Execz(dirz,programz,argz);
 }

auto FileSystem::pathOf(StrLen path_,char buf[MaxPathLen+1]) noexcept -> PathOfResult
 {
  PathOfResult ret;

  FileName path;

  if( auto fe=path.prepare(path_) )
    {
     ret.path=Empty;
     ret.error=fe;

     return ret;
    }

  WCharToUtf8<MaxPathLen+1> temp;

  temp.len=Win64::GetFullPathNameW(path,temp.Len,temp.buf,0);

  if( temp.len )
    {
     if( temp.len>MaxPathLen )
       {
        ret.path=Empty;
        ret.error=FileError_TooLongPath;
       }
     else
       {
        ulen len=temp.full(Range(buf,MaxPathLen));

        if( len==MaxULen )
          {
           ret.path=Empty;
           ret.error=FileError_TooLongPath;
          }
        else
          {
           buf[len]=0;

           ret.path=StrLen(buf,len);
           ret.error=FileError_Ok;

           PathBase::TurnSlash(Range(buf,len));
          }
       }
    }
  else
    {
     ret.path=Empty;
     ret.error=MakeError(FileError_OpFault);
    }

  return ret;
 }

} // namespace Sys
} // namespace CCore


