/* FontReplace.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/FontReplace.h>

namespace App {

/* class FontReplace */

FontReplace::FontReplace()
 {
 }

FontReplace::~FontReplace()
 {
 }

StrLen FontReplace::operator () (StrLen face) const
 {
  StrKey key(face);

  if( const String *obj=map.find(key) )
    {
     if( StrLen ret=Range(*obj) ; +ret ) return ret;
    }

  return face;
 }

void FontReplace::addNotFound(StrLen face)
 {
  StrKey key(face);

  map.find_or_add(key);
 }

void FontReplace::load()
 {
 }

void FontReplace::save()
 {
 }

} // namespace App
