/* PretextFileToMem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/PretextFileToMem.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class PretextMap */

void PretextMap::add(StrLen file_name,StrLen text)
 {
  list.append_copy({file_name,text});
 }

PretextMap::PretextMap(bool check_dev_) noexcept
 : check_dev(check_dev_)
 {
 }

PretextMap::~PretextMap()
 {
 }

auto PretextMap::operator () (StrLen file_name) -> Result
 {
  if( !ready )
    {
     list.erase();

     prepare();

     Sort(Range(list));

     ready=true;
    }

  if( check_dev )
    {
     if( !file_name.hasPrefix("pretext:"_c) ) return {Null,false};
    }

  auto r=Range(list);

  Algon::BinarySearch_if(r, [file_name] (const Rec &obj) { return !StrLess(obj.file_name,file_name); } );

  if( +r && !StrLess(file_name,r->file_name) ) return {Mutate<const uint8>(r->text),true};

  if( check_dev )
    {
     Printf(Exception,"CCore::PretextMap::operator () (#.q;) : no such file",file_name);
    }

  return {Null,false};
 }

} // namespace CCore

