/* Optional.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Optional.h>

namespace CCore {

/* class Optional */

void Optional::Destroy(Node *node)
 {
  if( node )
    {
     Destroy(Algo::Link(node).lo);
     Destroy(Algo::Link(node).hi);

     delete node;
    }
 }

} // namespace CCore


