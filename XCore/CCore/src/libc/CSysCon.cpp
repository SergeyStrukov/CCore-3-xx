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

#if 0

RetFileOp<Size> FileSystem::ConRead(void *buf_,Size buf_size)
 {
  if( buf_size==0 ) return buf_size;

  char *buf=static_cast<char *>(buf_);

  StdioReadCon::Access con;

  if( !con ) return FileResult_ReadFault;

  Size off=0;
  char ch;

  for(;;)
    {
     if( con->get(DefaultTimeout,ch) )
       {
        switch( ch )
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
                buf[off++]=ch;

                con->put(ch);

                if( off>=buf_size ) return off;
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

#endif

} // namespace LibC_Internal

