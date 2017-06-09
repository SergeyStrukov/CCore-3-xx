/* PrintAsyncFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/print/PrintAsyncFile.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Path.h>

namespace CCore {

/* class PrintAsyncFile */

PtrLen<char> PrintAsyncFile::do_provide(ulen)
 {
  auto result=file.getWritePacket();

  packet=result.packet;

  return Mutate<char>(result.buf);
 }

void PrintAsyncFile::do_flush(char *,ulen len)
 {
  file.write(file_pos,len,Replace_null(packet));

  file_pos+=len;
 }

PrintAsyncFile::PrintAsyncFile(MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
 }

PrintAsyncFile::PrintAsyncFile(StrLen file_name,FileOpenFlags oflags,MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
  open(file_name,oflags);
 }

PrintAsyncFile::PrintAsyncFile(StrLen dev_name,StrLen dev_file_name,FileOpenFlags oflags,MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
  open(dev_name,dev_file_name,oflags);
 }

PrintAsyncFile::~PrintAsyncFile()
 {
  flush();
 }

void PrintAsyncFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  FilePosType file_len=file.open(file_name,oflags);

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }

void PrintAsyncFile::open(StrLen dev_name,StrLen dev_file_name,FileOpenFlags oflags)
 {
  FilePosType file_len=file.open(dev_name,dev_file_name,oflags);

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }

void PrintAsyncFile::exec2(StrLen dir,StrLen program,MSec timeout,ulen max_packets)
 {
  SplitDevName split_dir(dir);

  if( !split_dir )
    {
     Printf(Exception,"CCore::PrintAsyncFile::exec2(#.q;,...) : bad name",dir);
    }

  SplitDevName split_program(program);

  if( !split_program )
    {
     Printf(Exception,"CCore::PrintAsyncFile::exec2(,#.q;,...) : bad name",program);
    }

  if( !split_dir.dev_name.equal(split_program.dev_name) )
    {
     Printf(Exception,"CCore::PrintAsyncFile::exec2(#.q;,#.q;,...) : different devices",dir,program);
    }

  AsyncFileSystem fs(split_dir.dev_name,timeout,max_packets);

  exec2(fs,split_dir.dev_path,split_program.dev_path);
 }

void PrintAsyncFile::exec2(AsyncFileSystem &fs,StrLen dev_dir,StrLen dev_program)
 {
  fs.exec2(dev_dir,dev_program,file);

  file_pos=0;
 }

void PrintAsyncFile::soft_close(FileMultiError &errout)
 {
  flush();

  file.soft_close(errout);
 }

void PrintAsyncFile::close()
 {
  flush();

  file.close();
 }

} // namespace CCore


