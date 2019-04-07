/* SysFileSystem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysFileSystem.h>

#include <CCore/inc/sys/SysInternal.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/CmdlineParser.h>

#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#ifndef _DIRENT_HAVE_D_TYPE
#error "Bad dirent"
#endif

namespace CCore {
namespace Sys {

/* namespace Private_SysFileSystem */

namespace Private_SysFileSystem {

/* functions */

StrLen Dotcard(StrLen dir)
 {
  return PathIsBase(dir)? "."_c : ""_c ;
 }

/* class EmptyDirEngine */

class EmptyDirEngine : NoCopy
 {
   char buf[MaxPathLen+1];

  private:

   FileError deleteDir(ulen dir_len)
    {
     if( FileError fe=emptyDir(dir_len) ) return fe;

     buf[dir_len]=0;

     if( rmdir(buf)==-1 ) return MakeError(FileError_OpFault);

     return FileError_Ok;
    }

   bool set(ulen dir_len,StrLen file_name)
    {
     if( file_name.len>MaxPathLen-dir_len ) return false;

     file_name.copyTo(buf+dir_len);

     buf[dir_len+file_name.len]=0;

     return true;
    }

   FileError remove(ulen dir_len,StrLen file_name,bool is_dir)
    {
     if( !set(dir_len+1,file_name) ) return FileError_TooLongPath;

     if( is_dir )
       {
        return deleteDir(dir_len+1+file_name.len);
       }
     else
       {
        if( unlink(buf)==-1 ) return MakeError(FileError_OpFault);

        return FileError_Ok;
       }
    }

   FileError emptyDir(ulen dir_len)
    {
     if( dir_len>MaxPathLen-1 ) return FileError_TooLongPath;

     buf[dir_len]='/';
     buf[dir_len+1]=0;

     DIR *dir=opendir(buf);

     if( !dir ) return MakeError(FileError_OpFault);

     errno=0;

     while( dirent *result=readdir(dir) )
       {
        StrLen file_name(result->d_name);

        if( !PathBase::IsSpecial(file_name) )
          {
           if( FileError fe=remove(dir_len,file_name,result->d_type==DT_DIR) )
             {
              closedir(dir);

              return fe;
             }
          }

        errno=0;
       }

     int error=errno;

     closedir(dir);

     if( error ) return MakeError(FileError_OpFault,error);

     return FileError_Ok;
    }

  public:

   EmptyDirEngine() {}

   FileError emptyDir(StrLen dir_name)
    {
     if( dir_name.len>MaxPathLen ) return FileError_TooLongPath;

     dir_name.copyTo(buf);

     return emptyDir(dir_name.len);
    }
 };

/* DeleteDirRecursive() */

FileError DeleteDirRecursive(StrLen dir_name)
 {
  EmptyDirEngine engine;

  if( FileError fe=engine.emptyDir(dir_name) ) return fe;

  if( rmdir(dir_name.ptr)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }

/* class StrPool */

class StrPool : NoCopy
 {
   ElementPool pool;

  public:

   StrPool() : pool(4_KByte) {}

   ~StrPool() {}

   char * add(StrLen str)
    {
     auto buf=pool.createArray_raw<char>(LenAdd(str.len,1));

     str.copyTo(buf.ptr);

     buf.back(1)=0;

     return buf.ptr;
    }

   char * add(BuilderType<char> builder)
    {
     char *buf=pool.createArray_raw<char>(LenAdd(builder.getLen(),1)).ptr;

     StrLen str=builder(buf);

     buf[str.len]=0;

     return buf;
    }
 };

/* class StrList */

class StrList : NoCopy
 {
   StrPool &pool;
   DynArray<char *> list;

  public:

   explicit StrList(StrPool &pool_) : pool(pool_),list(DoReserve,100) {}

   ~StrList() {}

   void add(StrLen str)
    {
     list.append_copy(pool.add(str));
    }

   void add(BuilderType<char> builder)
    {
     list.append_copy(pool.add(builder));
    }

   char ** complete()
    {
     list.append_copy(0);

     return list.getPtr();
    }

   void prepareArg(StrLen program,StrLen arg);
 };

void StrList::prepareArg(StrLen program,StrLen arg)
 {
  add(program);

  CmdlineParser parser(arg);

  for(;;)
    {
     auto builder=parser.next();

     if( !builder ) break;

     add(builder);
    }
 }

FileError Spawn(char *wdir,char *path,char **argv,char **envp)
 {
  volatile FileError error=FileError_Ok;

  switch( pid_t child_pid=vfork() )
    {
     case -1 : return MakeError(FileError_OpFault);

     case 0 :
      {
       char temp[PATH_MAX+1];
       char *path1=path;

       if( *path!='/' && strchr(path,'/') )
         {
          if( char *result=realpath(path,temp) )
            {
             path1=result;
            }
          else
            {
             error=MakeError(FileError_OpFault);

             _exit(124);
            }
         }

       if( chdir(wdir) )
         {
          error=MakeError(FileError_OpFault);

          _exit(125);
         }

       execvpe(path1,argv,envp);

       error=MakeError(FileError_OpFault);

       _exit( ( error==ENOENT )? 126 : 127 );
      }

     default:
      {
       waitpid(child_pid,0,WNOHANG);

       return error;
      }
    }
 }

} // namespace Private_SysFileSystem

using namespace Private_SysFileSystem;

/* struct FileSystem::DirCursor */

void FileSystem::DirCursor::init(FileSystem *,StrLen dir_name) noexcept
 {
  if( !dir_name )
    {
     dir=0;
     error=FileError_BadName;

     return;
    }

  FileName path;

  if( path.set(dir_name) )
    {
     dir=opendir(path);

     if( dir )
       error=FileError_Ok;
     else
       error=MakeError(FileError_OpFault);
    }
  else
    {
     dir=0;
     error=FileError_TooLongPath;
    }
 }

void FileSystem::DirCursor::exit() noexcept
 {
  if( dir )
    {
     closedir(static_cast<DIR *>(dir));
    }
 }

bool FileSystem::DirCursor::next() noexcept
 {
  if( !dir ) return false;

  errno=0;

  if( dirent *result=readdir(static_cast<DIR *>(dir)) )
    {
     StrLen name(result->d_name);

     if( name.len>MaxPathLen )
       {
        error=FileError_TooLongPath;

        closedir(static_cast<DIR *>(dir));

        dir=0;

        return false;
       }

     name.copyTo(file_name);
     len=name.len;
     type=(result->d_type==DT_DIR)?FileType_dir:FileType_file;
     error=FileError_Ok;

     return true;
    }
  else
    {
     int error_=errno;

     if( error_ )
       {
        error=MakeError(FileError_OpFault,error_);
       }
     else
       {
        error=FileError_Ok;
       }

     closedir(static_cast<DIR *>(dir));

     dir=0;

     return false;
    }
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

auto FileSystem::getFileType(StrLen path) noexcept -> TypeResult
 {
  FileName file_name;

  if( !file_name.set(path) ) return {FileType_none,FileError_TooLongPath};

  struct stat result;

  if( stat(file_name,&result)==-1 )
    {
     int error=errno;

     if( error==ENOENT || error==ENOTDIR ) return {FileType_none,FileError_Ok};

     return {FileType_none,MakeError(FileError_OpFault,error)};
    }

  return {(S_ISDIR(result.st_mode))?FileType_dir:FileType_file,FileError_Ok};
 }

auto FileSystem::getFileUpdateTime(StrLen path) noexcept -> CmpTimeResult
 {
  FileName file_name;

  if( !file_name.set(path) ) return {0,FileError_TooLongPath};

  struct stat result;

  if( stat(file_name,&result)==-1 )
    {
     int error=errno;

     if( error==ENOENT || error==ENOTDIR ) return {0,FileError_Ok};

     return {0,MakeError(FileError_OpFault,error)};
    }

  CmpFileTimeType time=TimeSpec(result.st_mtim).getNanoSec();

  if( !time ) time=1;

  return {time,FileError_Ok};
 }

FileError FileSystem::createFile(StrLen file_name_) noexcept
 {
  FileName file_name;

  if( !file_name.set(file_name_) ) return FileError_TooLongPath;

  int flags=O_RDWR|O_CREAT|O_EXCL;
  int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;

  int handle=open(file_name,flags,mode);

  if( handle==-1 ) return MakeError(FileError_OpenFault);

  close(handle);

  return FileError_Ok;
 }

FileError FileSystem::deleteFile(StrLen file_name_) noexcept
 {
  FileName file_name;

  if( !file_name.set(file_name_) ) return FileError_TooLongPath;

  if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }

FileError FileSystem::createDir(StrLen dir_name) noexcept
 {
  FileName file_name;

  if( !file_name.set(dir_name) ) return FileError_TooLongPath;

  int mode=S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP;

  if( mkdir(file_name,mode)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }

FileError FileSystem::deleteDir(StrLen dir_name,bool recursive) noexcept
 {
  if( !dir_name ) return FileError_BadName;

  FileName path;

  if( !path.set(dir_name,Dotcard(dir_name)) ) return FileError_TooLongPath;

  if( recursive ) return DeleteDirRecursive(StrLen(path,dir_name.len));

  if( rmdir(path)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }

FileError FileSystem::rename(StrLen old_path_,StrLen new_path_,bool allow_overwrite) noexcept
 {
  FileName old_path;

  if( !old_path.set(old_path_) ) return FileError_TooLongPath;

  FileName new_path;

  if( !new_path.set(new_path_) ) return FileError_TooLongPath;

  if( allow_overwrite )
    {
     struct stat result;

     if( stat(new_path,&result)==-1 )
       {
        int error=errno;

        if( error!=ENOENT && error!=ENOTDIR ) return MakeError(FileError_OpFault);
       }
     else
       {
        if( S_ISDIR(result.st_mode) ) return FileError_FileExist;
       }

     if( ::rename(old_path,new_path)==-1 ) return MakeError(FileError_OpFault);
    }
  else
    {
     struct stat result;

     if( stat(new_path,&result)==-1 )
       {
        int error=errno;

        if( error!=ENOENT && error!=ENOTDIR ) return MakeError(FileError_OpFault);
       }
     else
       {
        return FileError_FileExist;
       }

     if( ::rename(old_path,new_path)==-1 ) return MakeError(FileError_OpFault);
    }

  return FileError_Ok;
 }

FileError FileSystem::remove(StrLen path) noexcept
 {
  FileName file_name;

  if( !file_name.set(path) ) return FileError_TooLongPath;

  struct stat result;

  if( stat(file_name,&result)==-1 )
    {
     int error=errno;

     if( error==ENOENT || error==ENOTDIR ) return FileError_NoPath;

     return MakeError(FileError_OpFault,error);
    }

  if( S_ISDIR(result.st_mode) )
    {
     if( rmdir(file_name)==-1 ) return MakeError(FileError_OpFault);

     return FileError_Ok;
    }
  else
    {
     if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);

     return FileError_Ok;
    }
 }

FileError FileSystem::exec(StrLen dir,StrLen program,StrLen arg) noexcept
 {
  SilentReportException report;

  try
    {
     char temp[MaxPathLen+1];

     auto result=pathOf(dir,temp);

     if( result.error ) return result.error;

     StrPool pool;
     StrList argc(pool);

     char *path=pool.add(program);

     argc.prepareArg(program,arg);

     return Spawn(temp,path,argc.complete(),environ);
    }
  catch(CatchType)
    {
     return FileError_SysOverload;
    }
 }

auto FileSystem::pathOf(StrLen path_,char buf[MaxPathLen+1]) noexcept -> PathOfResult
 {
  FileName path;

  if( !path.set(path_) ) return PathOfResult{StrLen(),FileError_TooLongPath};

  char temp[PATH_MAX+1];

  if( char *result=realpath(path,temp) )
    {
     StrLen src(result);

     if( src.len>MaxPathLen )
       {
        return PathOfResult{StrLen(),FileError_TooLongPath};
       }
     else
       {
        src.copyTo(buf);

        return PathOfResult{StrLen(buf,src.len),FileError_Ok};
       }
    }
  else
    {
     return PathOfResult{StrLen(),MakeError(FileError_OpFault)};
    }
 }

} // namespace Sys
} // namespace CCore


