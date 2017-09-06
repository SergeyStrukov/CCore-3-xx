/* StringScan.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/scanf/StringScan.h>

#include <CCore/inc/StrMap.h>

namespace CCore {

/* struct StringScanOpt */

StringScanOpt::StringScanOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  if( ParseChar_try(dev,'.') && Parse_try(dev,type) )
    {
     if( !dev.finish() ) setDefault();
    }
  else
    {
     setDefault();
    }
 }

/* class StringSetScan */

auto StringSetScan::Select(PtrLen<Rec> r,char ch,ulen off) -> PtrLen<Rec>
 {
  return StrNextFrame(r,off,ch, [] (const Rec &rec) { return rec.str; } );
 }

auto StringSetScan::Select(PtrLen<Rec> r,ulen off) -> PtrLen<Rec>
 {
  return StrLastFrame(r,off, [] (const Rec &rec) { return rec.str; } );
 }

void StringSetScan::prepare()
 {
  auto r=Range(list);

  for(ulen i=0; i<r.len ;i++) r[i].index=i+1;

  IncrSort(r, [] (Rec a,Rec b) { return StrLess(a.str,b.str); } );
 }

StringSetScan::StringSetScan(std::initializer_list<const char *> zstr_list)
 : list(zstr_list)
 {
  prepare();
 }

StringSetScan::StringSetScan(std::initializer_list<StrLen> str_list)
 : list(str_list)
 {
  prepare();
 }

StringSetScan::~StringSetScan()
 {
 }

} // namespace CCore


