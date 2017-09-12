/* CSysCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/libc/CSysFile.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/StdioReadCon.h>

/* namespace LibC_Internal */

namespace LibC_Internal {

/* using */

using namespace CCore;

/* struct FileSystem : Console */

void FileSystem::AttachStdX()
 {
  // do nothing
 }

void FileSystem::DetachStdX()
 {
  // do nothing
 }

RetFileOp<Size> FileSystem::ConWrite(const void *buf,Size buf_size)
 {
  PrintCon::Print(static_cast<const char *>(buf),buf_size);

  return buf_size;
 }

RetFileOp<Size> FileSystem::ConRead(void *buf_,Size buf_size)
 {
  if( buf_size==0 ) return 0;

  if( buf_size<MaxSymbolLen ) return FileResult_ReadFault;

  char *buf=static_cast<char *>(buf_);

  StdioReadCon::Access con;

  if( !con ) return FileResult_ReadFault;

  Size off=0;
  ReadConCode ch;

  for(;;)
    {
     if( off+MaxSymbolLen>buf_size ) return off;

     if( con->get(DefaultTimeout,ch) )
       {
        switch( ToChar(ch) )
          {
           case '\r' :
           case '\n' :
            {
             buf[off++]='\n';

             con->put("\r\n"_c);
            }
           return off;

           case '\b' :
            {
             if( off>0 )
               {
                off--;

                con->put("\b \b"_c);
               }
            }
           break;

           default:
            {
             if( CharIsPrintable(ch) )
               {
                off=PutSymbol(buf,off,ch);

                con->put(ch);
               }
            }
          }
       }
     else
       {
        return off;
       }
    }
 }

} // namespace LibC_Internal

