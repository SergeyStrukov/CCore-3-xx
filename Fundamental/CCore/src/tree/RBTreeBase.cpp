/* RBTreeBase.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/tree/RBTreeBase.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardRBTreeCheckFailed(const char *text)
 {
  Printf(Exception,"CCore::GuardRBTreeCheck(...) : ( #; ) is false",text);
 }

/* enum RBFlag */

const char * GetTextDesc(RBFlag flag)
 {
  switch( flag )
    {
     case RBFlag_BlackBlack : return "B-B";
     case RBFlag_HiRed      : return "B-R";
     case RBFlag_LoRed      : return "R-B";
     case RBFlag_RedRed     : return "R-R";

     default: return "???";
    }
 }

} // namespace CCore


