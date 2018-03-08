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

/* class VolumeDir */

VolumeDir::VolumeDir()
 {
 }

VolumeDir::~VolumeDir()
 {
 }

auto VolumeDir::find(StrLen file_name) const -> Rec
 {
  auto r=Range(list);

  Algon::BinarySearch_if(r, [file_name] (const Rec &obj) { return !StrLess(obj.file_name,file_name); } );

  if( !r || StrLess(file_name,r->file_name) )
    {
     Printf(Exception,"CCore::VolumeDir::find(#.q;) : no such file",file_name);
    }

  return *r;
 }

} // namespace CCore

