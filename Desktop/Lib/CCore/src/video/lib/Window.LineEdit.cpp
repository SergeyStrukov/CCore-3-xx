/* Window.LineEdit.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Window.LineEdit.h>

#include <CCore/inc/algon/EuclidRotate.h>

namespace CCore {
namespace Video {

/* functions */

void InsChar(Char *base,ulen total,ulen pos,Char ch)
 {
  total++;

  auto r=RangeReverse(base+pos,total-pos);

  for(; r.len>1 ;++r) r[0]=r[1];

  r[0]=ch;
 }

ulen DelCharRange(Char *base,ulen total,ulen off,ulen len)
 {
  if( off>=total || len==0 ) return 0;

  Replace_min(len,total-off);

  ulen tail_off=off+len;
  ulen tail_len=total-tail_off;

  auto src=Range(base+tail_off,tail_len);
  auto dst=base+off;

  for(; +src ;++src,++dst) *dst=*src;

  return len;
 }

void RotateCharRange(Char *base,ulen total,ulen pos,ulen len)
 {
  total+=len;

  Algon::EuclidRotate_suffix(Range(base+pos,total-pos),len);
 }

} // namespace Video
} // namespace CCore

