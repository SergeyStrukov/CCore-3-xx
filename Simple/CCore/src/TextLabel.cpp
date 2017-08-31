/* TextLabel.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/TextLabel.h>

namespace CCore {

/* functions */

StrLen BuildNumTextLabel(const char *text,unsigned num,PtrLen<char> buf)
 {
  PrintBuf out(buf);

  if( num )
    Printf(out,"#;<#;>",text,num);
  else
    Printf(out,"#;<?>",text);

  return out.close();
 }

/* class TextLabel */

StrLen TextLabel::EmptyFunc(Handle,PtrLen<char>)
 {
  return "<?>"_c;
 }

StrLen TextLabel::StringFunc(Handle ctx,PtrLen<char>)
 {
  const char *zstr=static_cast<const char *>(ctx.ptr);

  if( !zstr ) return "<null>"_c;

  return zstr;
 }

} // namespace CCore


