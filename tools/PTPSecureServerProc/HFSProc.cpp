/* HFSProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServerProc 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "HFSProc.h"

#include <CCore/inc/Exception.h>

namespace PTPSecureServerProc {

/* class BuildClientPath */

void BuildClientPath::add(StrLen str)
 {
  if( str.len<=out.len )
    {
     str.copyTo(out.ptr);

     out+=str.len;
    }
  else
    {
     fe=FileError_TooLongPath;
    }
 }

void BuildClientPath::back()
 {
  if( level==0 )
    {
     fe=FileError_BadName;

     return;
    }

  char *ptr=out.ptr-1;

  for(; ptr[-1]!='/' ;ptr--);

  out.len+=Dist(ptr,out.ptr);

  out.ptr=ptr;

  level--;
 }

void BuildClientPath::next(StrLen name,Home home)
 {
  if( fe ) return;

  if( !name )
    {
     fe=FileError_BadName;

     return;
    }

  if( IsDot(name) )
    {
     return;
    }

  if( IsDotDot(name) )
    {
     back();

     return;
    }

  if( level==0 && IsTilde(name) )
    {
     if( home.has_home )
       {
        add("home/");

        add(home.name);

        add(StrLen("/",1));

        level+=2;
       }
     else
       {
        fe=FileError_BadName;

        return;
       }
    }
  else
    {
     add(name);

     add(StrLen("/",1));

     level++;
    }
 }

void BuildClientPath::stop(StrLen name,Home home)
 {
  if( fe ) return;

  if( !name )
    {
     fe=FileError_BadName;

     return;
    }

  if( IsDotDot(name) && level==0 )
    {
     fe=FileError_BadName;

     return;
    }

  if( level==0 && IsTilde(name) )
    {
     if( home.has_home )
       {
        add("home/");

        add(home.name);
       }
     else
       {
        fe=FileError_BadName;

        return;
       }
    }
  else
    {
     add(name);
    }
 }

void BuildClientPath::start(StrLen root)
 {
  if( !root )
    {
     fe=FileError_BadName;

     return;
    }

  add(root);

  if( !IsSlash(root.back(1)) ) add(StrLen("/",1));
 }

BuildClientPath::BuildClientPath(StrLen root,StrLen path,Home home)
 : out(Range(buf)),
   level(0),
   fe(FileError_Ok)
 {
  if( +path && IsSlash(*path) )
    {
     ++path;

     if( !path )
       {
        if( !root )
          {
           fe=FileError_BadName;

           return;
          }

        if( IsSlash(root.back(1)) ) root.len--;

        if( !root )
          {
           fe=FileError_BadName;

           return;
          }

        add(root);

        return;
       }
    }

  start(root);

  for(;;)
    {
     SplitDirName split(path);

     if( !split )
       {
        stop(path,home);

        break;
       }
     else
       {
        next(split.dir_name,home);

        path=split.path;
       }
    }
 }

/* struct FileNode */

ErrorIdType FileNode::open(StrLen root,StrLen file_name,Home home,FlagType oflags)
 {
  BuildClientPath path(root,file_name,home);

  if( FileError fe=!path ) return error(fe);

  auto result=sys_file.open(path.getStr(),FileOpenFlags(oflags));

  if( FileError fe=result.error ) return error(fe);

  file_len=result.file_len;

  return error(NoError);
 }

FileReadResult FileNode::read(FileLenType off,PtrLen<uint8> buf)
 {
  if( error_state ) return error_state;

  if( off>=file_len ) return FileReadResult(NoError,0);

  FileLenType avail=file_len-off;

  ulen len=buf.len;

  if( len>avail ) len=(ulen)avail;

  if( FileError fe=sys_file.read(off,buf.ptr,len) ) return error(fe);

  return FileReadResult(NoError,len);
 }

FileWriteResult FileNode::write(FileLenType off,PtrLen<const uint8> data)
 {
  if( error_state ) return error_state;

  if( data.len>MaxLen(off) ) return error(FileError_LenOverflow);

  auto result=sys_file.write(off,data.ptr,data.len);

  if( FileError fe=result.error ) return error(fe);

  file_len=result.file_len;

  return FileWriteResult(NoError,result.file_len);
 }

ErrorIdType FileNode::close(bool preserve_file)
 {
  FileMultiError errout;

  sys_file.close(errout,preserve_file);

  if( FileError fe=errout.getFirst() ) return error(fe);

  return NoError;
 }

/* struct MemNode */

FileReadResult MemNode::do_read(FileLenType off_,PtrLen<uint8> buf)
 {
  if( off_>=data.getLen() ) return FileReadResult(NoError,0);

  ulen off=ulen(off_);

  ulen avail=data.getLen()-off;

  Replace_min(buf.len,avail);

  buf.copy(data.getPtr()+off);

  return FileReadResult(NoError,buf.len);
 }

FileWriteResult MemNode::do_write(FileLenType off_,PtrLen<const uint8> src)
 {
  if( off_>MaxLen || src.len>MaxLen-(ulen)off_ ) return ToErrorId(FileError_LenOverflow);

  try
    {
     ulen off=ulen(off_);

     if( off<data.getLen() )
       {
        ulen avail=data.getLen()-off;

        src.takeup(avail).copyTo(data.getPtr()+off);

        if( +src ) data.extend_copy(src);
       }
     else
       {
        data.extend_default(off-data.getLen());

        if( +src ) data.extend_copy(src);
       }

     return FileWriteResult(NoError,data.getLen());
    }
  catch(CatchType)
    {
     return ToErrorId(FileError_DiskFull);
    }
 }

ErrorIdType MemNode::open(FlagType oflags_,MemNodeExt *ext_)
 {
  data.erase();

  oflags=oflags_;
  ext=ext_;

  return NoError;
 }

FileReadResult MemNode::read(FileLenType off,PtrLen<uint8> buf)
 {
  if( !(oflags&Open_Read) ) return ToErrorId(FileError_NoMethod);

  return do_read(off,buf);
 }

FileWriteResult MemNode::write(FileLenType off,PtrLen<const uint8> data)
 {
  if( !(oflags&Open_Write) ) return ToErrorId(FileError_NoMethod);

  return do_write(off,data);
 }

ErrorIdType MemNode::close(bool preserve_file)
 {
  ErrorIdType ret=NoError;

  if( ext )
    {
     ret=ext->atClose(this,preserve_file);

     delete ext;

     ext=0;
    }

  data.erase();

  return ret;
 }

/* class PrintMemNode */

PtrLen<char> PrintMemNode::do_provide(ulen)
 {
  if( error_id ) return Nothing;

  return Range(buf);
 }

void PrintMemNode::do_flush(char *ptr,ulen len)
 {
  auto result=node->do_write(off,Mutate<const uint8>(Range(ptr,len)));

  off+=len;

  error_id=result.error_id;
 }

PrintMemNode::PrintMemNode(MemNode *node_)
 : node(node_),
   off(0),
   error_id(NoError)
 {
 }

PrintMemNode::~PrintMemNode()
 {
  flush();
 }

ErrorIdType PrintMemNode::complete()
 {
  flush();

  return error_id;
 }

/* class FileSet */

FileSet::FileSet(ulen max_files)
 : set(max_files)
 {
 }

FileSet::~FileSet()
 {
 }

FileResult FileSet::open(XPoint point,StrLen root,StrLen file_name,Home home,FlagType oflags)
 {
  auto result=set.allocNode(point);

  if( !result.node ) return Error_Exhausted;

  if( ErrorIdType error_id=result.node->open(root,file_name,home,oflags) )
    {
     set.freeNode(result.node);

     return error_id;
    }

  return FileResult(result.file_id,result.node);
 }

ErrorIdType FileSet::close(FileNode *node,bool preserve_file)
 {
  ErrorIdType error_id=node->close(preserve_file);

  set.freeNode(node);

  return error_id;
 }

/* class MemSet */

MemSet::MemSet(ulen max_mems)
 : set(max_mems)
 {
 }

MemSet::~MemSet()
 {
 }

MemResult MemSet::open(XPoint point,FlagType oflags,MemNodeExt *ext)
 {
  auto result=set.allocNode(point);

  if( !result.node )
    {
     delete ext;

     return Error_Exhausted;
    }

  if( ErrorIdType error_id=result.node->open(oflags,ext) )
    {
     delete ext;

     set.freeNode(result.node);

     return error_id;
    }

  return MemResult(result.file_id,result.node);
 }

ErrorIdType MemSet::close(MemNode *node,bool preserve_file)
 {
  ErrorIdType error_id=node->close(preserve_file);

  set.freeNode(node);

  return error_id;
 }

/* class FileSystem */

FileSystem::FileSystem()
 {
  if( auto fe=fs.init() )
    {
     Printf(Exception,"PTPSecureServerProc::FileSystem::FileSystem() : #;",fe);
    }
 }

FileSystem::~FileSystem()
 {
  if( auto fe=fs.exit() )
    {
     Printf(NoException,"PTPSecureServerProc::FileSystem::~FileSystem() : #;",fe);
    }
 }

auto FileSystem::getFileType(StrLen root,StrLen path_,Home home) -> FileTypeResult
 {
  BuildClientPath path(root,path_,home);

  if( FileError fe=!path ) return FileTypeResult(fe);

  auto result=fs.getFileType(path.getStr());

  return FileTypeResult(result.error,result.type);
 }

auto FileSystem::getFileUpdateTime(StrLen root,StrLen path_,Home home) -> FileUpdateTimeResult
 {
  BuildClientPath path(root,path_,home);

  if( FileError fe=!path ) return FileUpdateTimeResult(fe);

  auto result=fs.getFileUpdateTime(path.getStr());

  return FileUpdateTimeResult(result.error,result.time);
 }

ErrorIdType FileSystem::getFileList(StrLen root,StrLen dir_name_,Home home,MemNode *node)
 {
  BuildClientPath dir_name(root,dir_name_,home);

  if( FileError fe=!dir_name ) return ToErrorId(fe);

  PrintMemNode out(node);

  Sys::FileSystem::DirCursor cur;

  cur.init(&fs,dir_name.getStr());

  if( FileError fe=cur.error ) return ToErrorId(fe);

  while( cur.next() )
    {
     Printf(out,"#; #.c;\n",StrLen(cur.file_name,cur.len),(cur.type==FileType_file)?'f':'d');
    }

  if( FileError fe=cur.error )
    {
     cur.exit();

     return ToErrorId(fe);
    }
  else
    {
     cur.exit();

     return out.complete();
    }
 }

ErrorIdType FileSystem::createFile(StrLen root,StrLen file_name,Home home)
 {
  BuildClientPath path(root,file_name,home);

  if( FileError fe=!path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.createFile(path.getStr()) );
 }

ErrorIdType FileSystem::deleteFile(StrLen root,StrLen file_name,Home home)
 {
  BuildClientPath path(root,file_name,home);

  if( FileError fe=!path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.deleteFile(path.getStr()) );
 }

ErrorIdType FileSystem::createDir(StrLen root,StrLen dir_name,Home home)
 {
  BuildClientPath path(root,dir_name,home);

  if( FileError fe=!path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.createDir(path.getStr()) );
 }

ErrorIdType FileSystem::deleteDir(StrLen root,StrLen dir_name,Home home,bool recursive)
 {
  BuildClientPath path(root,dir_name,home);

  if( FileError fe=!path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.deleteDir(path.getStr(),recursive) );
 }

ErrorIdType FileSystem::rename(StrLen root,StrLen old_path_,StrLen new_path_,Home home,bool allow_overwrite)
 {
  BuildClientPath old_path(root,old_path_,home);

  if( FileError fe=!old_path ) return ToErrorId(fe);

  BuildClientPath new_path(root,new_path_,home);

  if( FileError fe=!new_path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.rename(old_path.getStr(),new_path.getStr(),allow_overwrite) );
 }

ErrorIdType FileSystem::remove(StrLen root,StrLen path_,Home home)
 {
  BuildClientPath path(root,path_,home);

  if( FileError fe=!path ) return ToErrorId(fe);

  return ToErrorId_Ok( fs.remove(path.getStr()) );
 }

/* class HFSProc */

ClientProfile * HFSProc::getProfile(Inbound &inbound)
 {
  return dynamic_cast<ClientProfile *>(epman.getClientProfile(inbound.point));
 }

void HFSProc::function_Open(Inbound &inbound)
 {
  Tailed<Net::HFS::OpenInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( input.base.open_flags&Open_Read )
       {
        if( !profile->access_read )
          {
           inbound.error_id=Error_AccessDenied;

           return inbound.send_error(ptp);
          }
       }

     if( input.base.open_flags&Open_Write )
       {
        if( !profile->access_write )
          {
           inbound.error_id=Error_AccessDenied;

           return inbound.send_error(ptp);
          }
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen file_name=Mutate<const char>(input.tail);

  FileResult result=file_set.open(inbound.point,root,file_name,profile,input.base.open_flags);

  if( result.error_id )
    {
     log("HFSOpen(#;:#;,#.q;,#;) error : #;",desc,profile->name,file_name,FileOpenFlags(input.base.open_flags),GetErrorDesc(result.error_id));

     inbound.error_id=result.error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::OpenOutput output(result.file_id,result.node->getLen());

  log("HFSOpen(#;:#;,#.q;,#;) at slot #;",desc,profile->name,file_name,FileOpenFlags(input.base.open_flags),result.file_id.slot);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_Read(Inbound &inbound)
 {
  Net::HFS::ReadInput input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( TakeMemFlag(input.file_id) )
    {
     MemNode *node=mem_set.find(input.file_id);

     if( !node )
       {
        log("HFSRead(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     PtrLen<uint8> buf=inbound.send_buf<Net::HFS::ReadOutput>(input.len);

     FileReadResult ioresult=node->read(input.off,buf);

     if( ioresult.error_id )
       {
        log("HFSRead(...) error : #;",GetErrorDesc(ioresult.error_id));

        inbound.error_id=ioresult.error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::ReadOutput output(input.off,ioresult.len);

     inbound.send_info_tailed(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.file_id);

     if( !node )
       {
        log("HFSRead(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     PtrLen<uint8> buf=inbound.send_buf<Net::HFS::ReadOutput>(input.len);

     FileReadResult ioresult=node->read(input.off,buf);

     if( ioresult.error_id )
       {
        log("HFSRead(...) error : #;",GetErrorDesc(ioresult.error_id));

        inbound.error_id=ioresult.error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::ReadOutput output(input.off,ioresult.len);

     inbound.send_info_tailed(output,ptp);
    }
 }

void HFSProc::function_Write(Inbound &inbound)
 {
  Tailed<Net::HFS::WriteInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( TakeMemFlag(input.base.file_id) )
    {
     MemNode *node=mem_set.find(input.base.file_id);

     if( !node )
       {
        log("HFSWrite(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     FileWriteResult ioresult=node->write(input.base.off,input.tail);

     if( ioresult.error_id )
       {
        log("HFSWrite(...) error : #;",GetErrorDesc(ioresult.error_id));

        inbound.error_id=ioresult.error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::WriteOutput output(ioresult.file_len);

     inbound.send_info(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.base.file_id);

     if( !node )
       {
        log("HFSWrite(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     FileWriteResult ioresult=node->write(input.base.off,input.tail);

     if( ioresult.error_id )
       {
        log("HFSWrite(...) error : #;",GetErrorDesc(ioresult.error_id));

        inbound.error_id=ioresult.error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::WriteOutput output(ioresult.file_len);

     inbound.send_info(output,ptp);
    }
 }

void HFSProc::function_Close(Inbound &inbound)
 {
  Net::HFS::CloseInput input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( TakeMemFlag(input.file_id) )
    {
     MemNode *node=mem_set.find(input.file_id);

     if( !node )
       {
        log("HFSClose(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     if( ErrorIdType error_id=mem_set.close(node,input.preserve_file) )
       {
        log("HFSClose(...) error : #;",GetErrorDesc(error_id));

        inbound.error_id=error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::CloseOutput output;

     log("HFSClose(...#;) at mem slot #;",(input.preserve_file?",preserve":""),input.file_id.slot);

     inbound.send_info(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.file_id);

     if( !node )
       {
        log("HFSClose(...) error : invalid file_id");

        inbound.error_id=ToErrorId(FileError_BadId);

        return inbound.send_error(ptp);
       }

     if( ErrorIdType error_id=file_set.close(node,input.preserve_file) )
       {
        log("HFSClose(...) error : #;",GetErrorDesc(error_id));

        inbound.error_id=error_id;

        return inbound.send_error(ptp);
       }

     Net::HFS::CloseOutput output;

     log("HFSClose(...#;) at slot #;",(input.preserve_file?",preserve":""),input.file_id.slot);

     inbound.send_info(output,ptp);
    }
 }

void HFSProc::function_GetFileType(Inbound &inbound)
 {
  Tailed<Net::HFS::GetFileTypeInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_read )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen path=Mutate<const char>(input.tail);

  auto result=filesys.getFileType(root,path,profile);

  if( result.error_id )
    {
     log("HFSGetFileType(#;:#;,#.q;) error : #;",desc,profile->name,path,GetErrorDesc(result.error_id));

     inbound.error_id=result.error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::GetFileTypeOutput output(result.type);

  log("HFSGetFileType(#;:#;,#.q;) = #;",desc,profile->name,path,result.type);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_GetFileList(Inbound &inbound)
 {
  Tailed<Net::HFS::GetFileListInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_read )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen dir_name=Mutate<const char>(input.tail);

  MemResult result=mem_set.open(inbound.point,Open_Read);

  if( result.error_id )
    {
     log("HFSGetFileList(#;:#;,#.q;) error : #;",desc,profile->name,dir_name,GetErrorDesc(result.error_id));

     inbound.error_id=result.error_id;

     return inbound.send_error(ptp);
    }

  if( ErrorIdType error_id=filesys.getFileList(root,dir_name,profile,result.node) )
    {
     mem_set.close(result.node);

     log("HFSGetFileList(#;:#;,#.q;) error : #;",desc,profile->name,dir_name,GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::GetFileListOutput output(result.file_id,result.node->getLen());

  log("HFSGetFileList(#;:#;,#.q;) at mem slot #;",desc,profile->name,dir_name,result.file_id.slot);

  SetMemFlag(output.file_id);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_CreateFile(Inbound &inbound)
 {
  Tailed<Net::HFS::CreateFileInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen file_name=Mutate<const char>(input.tail);

  if( ErrorIdType error_id=filesys.createFile(root,file_name,profile) )
    {
     log("HFSCreateFile(#;:#;,#.q;) error : #;",desc,profile->name,file_name,GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::CreateFileOutput output;

  log("HFSCreateFile(#;:#;,#.q;)",desc,profile->name,file_name);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_DeleteFile(Inbound &inbound)
 {
  Tailed<Net::HFS::DeleteFileInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen file_name=Mutate<const char>(input.tail);

  if( ErrorIdType error_id=filesys.deleteFile(root,file_name,profile) )
    {
     log("HFSDeleteFile(#;:#;,#.q;) error : #;",desc,profile->name,file_name,GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::DeleteFileOutput output;

  log("HFSDeleteFile(#;:#;,#.q;)",desc,profile->name,file_name);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_CreateDir(Inbound &inbound)
 {
  Tailed<Net::HFS::CreateDirInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen dir_name=Mutate<const char>(input.tail);

  if( ErrorIdType error_id=filesys.createDir(root,dir_name,profile) )
    {
     log("HFSCreateDir(#;:#;,#.q;) error : #;",desc,profile->name,dir_name,GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::CreateDirOutput output;

  log("HFSCreateDir(#;:#;,#.q;)",desc,profile->name,dir_name);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_DeleteDir(Inbound &inbound)
 {
  Tailed<Net::HFS::DeleteDirInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen dir_name=Mutate<const char>(input.tail);

  if( ErrorIdType error_id=filesys.deleteDir(root,dir_name,profile,input.base.recursive) )
    {
     log("HFSDeleteDir(#;:#;,#.q;#;) error : #;",desc,profile->name,dir_name,(input.base.recursive?",recursive":""),GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::DeleteDirOutput output;

  log("HFSDeleteDir(#;:#;,#.q;#;)",desc,profile->name,dir_name,(input.base.recursive?",recursive":""));

  inbound.send_info(output,ptp);
 }

void HFSProc::function_Rename(Inbound &inbound)
 {
  Net::HFS::RenameInput input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen old_path=Mutate<const char>(input.old_path.path);
  StrLen new_path=Mutate<const char>(input.new_path.path);

  if( ErrorIdType error_id=filesys.rename(root,old_path,new_path,profile,input.allow_overwrite) )
    {
     log("HFSRename(#;:#;,#.q;,#.q;#;) error : #;",desc,profile->name,old_path,new_path,(input.allow_overwrite?",overwrite":""),GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::RenameOutput output;

  log("HFSRename(#;:#;,#.q;,#.q;#;)",desc,profile->name,old_path,new_path,(input.allow_overwrite?",overwrite":""));

  inbound.send_info(output,ptp);
 }

void HFSProc::function_Remove(Inbound &inbound)
 {
  Tailed<Net::HFS::RemoveInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_write )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen path=Mutate<const char>(input.tail);

  if( ErrorIdType error_id=filesys.remove(root,path,profile) )
    {
     log("HFSRemove(#;:#;,#.q;) error : #;",desc,profile->name,path,GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::RemoveOutput output;

  log("HFSRemove(#;:#;,#.q;)",desc,profile->name,path);

  inbound.send_info(output,ptp);
 }

void HFSProc::function_GetFileUpdateTime(Inbound &inbound)
 {
  Tailed<Net::HFS::GetFileUpdateTimeInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  ClientProfile *profile=getProfile(inbound);

  if( profile )
    {
     if( !profile->access_read )
       {
        inbound.error_id=Error_AccessDenied;

        return inbound.send_error(ptp);
       }
    }
  else
    {
     inbound.error_id=Error_NoProfile;

     return inbound.send_error(ptp);
    }

  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);

  StrLen path=Mutate<const char>(input.tail);

  auto result=filesys.getFileUpdateTime(root,path,profile);

  if( result.error_id )
    {
     log("HFSGetFileUpdateTime(#;:#;,#.q;) error : #;",desc,profile->name,path,GetErrorDesc(result.error_id));

     inbound.error_id=result.error_id;

     return inbound.send_error(ptp);
    }

  Net::HFS::GetFileUpdateTimeOutput output(result.file_time);

  log("HFSGetFileUpdateTime(#;:#;,#.q;) = #;",desc,profile->name,path,result.file_time);

  inbound.send_info(output,ptp);
 }

HFSProc::HFSProc(ServerProcBase *base,StrLen root_,Net::PSec::EndpointManager &epman_,ulen max_files,ulen max_mems)
 : ProcBase(base),
   file_set(max_files),
   mem_set(max_mems),
   root(root_),
   epman(epman_)
 {
 }

HFSProc::~HFSProc()
 {
 }

void HFSProc::inbound(Inbound &inbound)
 {
  switch( inbound.serv_func.function_id )
    {
     case Net::HFS::FunctionId_Open :        function_Open(inbound); break;

     case Net::HFS::FunctionId_Read :        function_Read(inbound); break;

     case Net::HFS::FunctionId_Write :       function_Write(inbound); break;

     case Net::HFS::FunctionId_Close :       function_Close(inbound); break;

     case Net::HFS::FunctionId_GetFileType : function_GetFileType(inbound); break;

     case Net::HFS::FunctionId_GetFileList : function_GetFileList(inbound); break;

     case Net::HFS::FunctionId_CreateFile :  function_CreateFile(inbound); break;

     case Net::HFS::FunctionId_DeleteFile :  function_DeleteFile(inbound); break;

     case Net::HFS::FunctionId_CreateDir :   function_CreateDir(inbound); break;

     case Net::HFS::FunctionId_DeleteDir :   function_DeleteDir(inbound); break;

     case Net::HFS::FunctionId_Rename :      function_Rename(inbound); break;

     case Net::HFS::FunctionId_Remove :      function_Remove(inbound); break;

     case Net::HFS::FunctionId_GetFileUpdateTime : function_GetFileUpdateTime(inbound); break;

     default:
      {
       inbound.error_id=Error_NoFunction;

       inbound.send_error(ptp);
      }
    }
 }

void HFSProc::tick()
 {
  // do nothing
 }

void HFSProc::session(XPoint point)
 {
  file_set.purge(point);
  mem_set.purge(point);
 }

bool HFSProc::exist(FunctionIdType function_id)
 {
  return ( function_id>=Net::HFS::FunctionId_Open && function_id<=Net::HFS::FunctionId_Remove )
         || function_id==Net::HFS::FunctionId_GetFileUpdateTime ;
 }

} // namespace PTPSecureServerProc

