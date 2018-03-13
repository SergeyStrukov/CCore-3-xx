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

void GuardVolumeFileTooLong(StrLen file_name,ulen max_len,FilePosType file_len)
 {
  Printf(Exception,"CCore::VolumeFileToMem<...>::VolumeFileToMem(...,#.q;,max_len=#;) : file is too long #;",file_name,max_len,file_len);
 }

/* class VolumeDir */

template <UIntType UInt,UIntType UInt1>
void VolumeDir::CheckBounds(UInt off,UInt len,UInt1 total)
 {
  if( len>total || off>total-len )
    {
     Printf(Exception,"CCore::VolumeDir::fill(...) : bad file data");
    }
 }

auto VolumeDir::makeRec(Entry entry,FilePosType file_len) -> Rec
 {
  CheckBounds(entry.name_off,entry.name_len,names.getLen());
  CheckBounds(entry.body_off,entry.body_len,file_len);

  return {StrLen(names.getPtr()+entry.name_off,entry.name_len),entry.body_off,entry.body_len};
 }

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

