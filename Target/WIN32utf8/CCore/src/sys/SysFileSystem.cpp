/* SysFileSystem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysFileSystem.h>
#include <CCore/inc/sys/SysFileInternal.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Sys {

/* namespace Private_SysFileSystem */

namespace Private_SysFileSystem {

/* class EmptyDirEngine */

class EmptyDirEngine : NoCopy
 {
   WChar buf[MaxPathLen+1];
   Win32::FindFileData data;

  private:

   FileError deleteDir(ulen dir_len)
    {
     if( FileError fe=emptyDir(dir_len) ) return fe;

     buf[dir_len]=0;

     return MakeErrorIf(FileError_OpFault, !Win32::RemoveDirectoryW(buf) );
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
        if( !Win32::DeleteFileW(buf) ) return MakeError(FileError_OpFault);

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

     Win32::handle_t h_find=Win32::FindFirstFileW(buf,&data);

     if( h_find==Win32::InvalidFileHandle ) return MakeError(FileError_OpFault);

     do
       {
        ulen len=ZLen(data.file_name);

        if( !IsSpecial(data.file_name,len) )
          {
           if( FileError fe=remove(dir_len,data.file_name,len,data.attr&Win32::FileAttributes_Directory) )
             {
              Win32::FindClose(h_find);

              return fe;
             }
          }
       }
     while( FindNextFileW(h_find,&data) );

     Win32::error_t error_=Win32::GetLastError();

     Win32::FindClose(h_find);

     if( error_!=Win32::ErrorNoMoreFiles ) return MakeError(FileError_OpFault,error_);

     return FileError_Ok;
    }

  public:

   EmptyDirEngine() {}

   FileError emptyDir(const WChar *dir_name)
    {
     ulen len=ZLen(dir_name);

     if( len>MaxPathLen ) return FileError_TooLongPath;

     Range(dir_name,len).copyTo(buf);

     return emptyDir(len);
    }
 };

/* DeleteDirRecursive() */

FileError DeleteDirRecursive(const WChar *dir_name)
 {
  EmptyDirEngine engine;

  if( FileError fe=engine.emptyDir(dir_name) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win32::RemoveDirectoryW(dir_name) );
 }

/* Execz() */

FileError Execz(const WChar *dir,const WChar *program,WChar *arg)
 {
  Win32::flags_t flags=Win32::CreateNewConsole;

  Win32::StartupInfo info{};

  info.cb=sizeof info;

  Win32::ProcessInfo pinfo;

  if( Win32::CreateProcessW(program,arg,0,0,false,flags,0,dir,&info,&pinfo) )
    {
     Win32::CloseHandle(pinfo.h_process);
     Win32::CloseHandle(pinfo.h_thread);

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

  FileName path;

  if( auto fe=path.prepare(dir_name,"/*"_c) )
    {
     error=fe;
    }
  else
    {
     Win32::FindFileData data;

     handle=Win32::FindFirstFileW(path,&data);

     if( handle==Win32::InvalidFileHandle )
       {
        Win32::error_t error_=Win32::GetLastError();

        if( error_!=Win32::ErrorFileNotFound )
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
           Win32::FindClose(handle);

           error=FileError_TooLongPath;
          }
        else
          {
           is_first=true;
           is_closed=false;

           type=(data.attr&Win32::FileAttributes_Directory)?FileType_dir:FileType_file;

           error=FileError_Ok;
          }
       }
    }
 }

void FileSystem::DirCursor::exit() noexcept
 {
  if( !is_closed )
    {
     Win32::FindClose(handle);
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

  Win32::FindFileData data;

  if( FindNextFileW(handle,&data) )
    {
     len=Full(data.file_name,Range(file_name));

     if( len==MaxULen )
       {
        is_closed=true;

        Win32::FindClose(handle);

        error=FileError_TooLongPath;

        return false;
       }
     else
       {
        type=(data.attr&Win32::FileAttributes_Directory)?FileType_dir:FileType_file;

        return true;
       }
    }

  Win32::error_t error_=Win32::GetLastError();

  if( error_!=Win32::ErrorNoMoreFiles )
    {
     error=MakeError(FileError_OpFault,error_);
    }

  is_closed=true;

  Win32::FindClose(handle);

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
     Win32::flags_t attr=Win32::GetFileAttributesW(path);

     if( attr==Win32::InvalidFileAttributes )
       {
        ret.type=FileType_none;
        ret.error=FileError_Ok;
       }
     else
       {
        ret.type=(attr&Win32::FileAttributes_Directory)?FileType_dir:FileType_file;
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
     Win32::handle_t h_file=Win32::CreateFileW(path,Win32::AccessRead,Win32::ShareRead,0,Win32::OpenExisting,Win32::FileBackupSemantic,0);

     if( h_file==Win32::InvalidFileHandle )
       {
        ret.time=0;
        ret.error=FileError_Ok;
       }
     else
       {
        Win32::FileTime result;

        if( Win32::GetFileTime(h_file,0,0,&result) )
          {
           ret.time=ToCmpFileTime(result);
           ret.error=FileError_Ok;
          }
        else
          {
           ret.time=0;
           ret.error=MakeError(FileError_OpFault);
          }

        Win32::CloseHandle(h_file);
       }
    }

  return ret;
 }

FileError FileSystem::createFile(StrLen file_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(file_name) ) return fe;

  Win32::flags_t access_flags = 0 ;

  Win32::flags_t share_flags = 0 ;

  Win32::options_t creation_options = Win32::CreateNew ;

  Win32::flags_t file_flags = Win32::FileAttributeNormal ;

  Win32::handle_t h_file = Win32::CreateFileW(path,access_flags,share_flags,0,creation_options,file_flags,0) ;

  if( h_file==Win32::InvalidFileHandle ) return MakeError(FileError_OpenFault);

  Win32::CloseHandle(h_file);

  return FileError_Ok;
 }

FileError FileSystem::deleteFile(StrLen file_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(file_name) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win32::DeleteFileW(path) );
 }

FileError FileSystem::createDir(StrLen dir_name) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(dir_name) ) return fe;

  return MakeErrorIf(FileError_OpFault, !Win32::CreateDirectoryW(path,0) );
 }

FileError FileSystem::deleteDir(StrLen dir_name,bool recursive) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(dir_name) ) return fe;

  if( recursive ) return DeleteDirRecursive(path);

  return MakeErrorIf(FileError_OpFault, !Win32::RemoveDirectoryW(path) );
 }

FileError FileSystem::rename(StrLen old_path_,StrLen new_path_,bool allow_overwrite) noexcept
 {
  FileName old_path;

  if( auto fe=old_path.prepare(old_path_) ) return fe;

  FileName new_path;

  if( auto fe=new_path.prepare(new_path_) ) return fe;

  Win32::flags_t flags=allow_overwrite?Win32::MoveFileEx_AllowOverwrite:0;

  return MakeErrorIf(FileError_OpFault, !Win32::MoveFileExW(old_path,new_path,flags) );
 }

FileError FileSystem::remove(StrLen path_) noexcept
 {
  FileName path;

  if( auto fe=path.prepare(path_) ) return fe;

  Win32::flags_t attr=Win32::GetFileAttributesW(path);

  if( attr==Win32::InvalidFileAttributes ) return MakeError(FileError_NoPath);

  if( attr&Win32::FileAttributes_Directory )
    {
     return MakeErrorIf(FileError_OpFault, !Win32::RemoveDirectoryW(path) );
    }
  else
    {
     return MakeErrorIf(FileError_OpFault, !Win32::DeleteFileW(path) );
    }
 }

FileError FileSystem::exec(StrLen dir,StrLen program,StrLen arg) noexcept
 {
  SilentReportException report;

  try
    {
     const ulen Len1=MaxPathLen+1;
     const ulen Len2=32_KByte;

     DynArray<WChar> temp(DoRaw(2*Len1+Len2));

     WChar *dirz=temp.getPtr();
     WChar *programz=dirz+Len1;
     WChar *argz=programz+Len1;

     if( auto fe=MakeZStr(dir,Range(dirz,Len1)) ) return fe;

     if( auto fe=MakeZStr(program,Range(programz,Len1)) ) return fe;

     if( auto fe=MakeZStr(arg,Range(argz,Len2)) ) return fe;

     return Execz(dirz,programz,argz);
    }
  catch(CatchType)
    {
     return FileError_SysOverload;
    }
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

  temp.len=Win32::GetFullPathNameW(path,temp.Len,temp.buf,0);

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

           PathBase::TurnSlash(Range(buf,len));

           ret.path=StrLen(buf,len);
           ret.error=FileError_Ok;
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


