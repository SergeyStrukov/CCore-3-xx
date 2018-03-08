/* Volume.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Volume.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardReadOutOfBound()
 {
  Printf(Exception,"CCore::VolumeFile<...>::read_all(...) : out of bound");
 }

void GuardVolumeNoFile(StrLen file_name)
 {
  Printf(Exception,"CCore::Volume<...>::open(#.q;) : no such file",file_name);
 }

} // namespace CCore

