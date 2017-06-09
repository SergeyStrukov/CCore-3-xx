/* FileNameCmp.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FileNameCmp_h
#define CCore_inc_video_FileNameCmp_h

#include <CCore/inc/Cmp.h>

namespace CCore {
namespace Video {

/* functions */

CmpResult NativeNameCmp(StrLen a,StrLen b);

CmpResult ExtNameCmp(StrLen a,StrLen b);

inline bool NativeNameLess(StrLen a,StrLen b) { return NativeNameCmp(a,b)<0; }

inline bool ExtNameLess(StrLen a,StrLen b) { return ExtNameCmp(a,b)<0; }

} // namespace Video
} // namespace CCore

#endif

