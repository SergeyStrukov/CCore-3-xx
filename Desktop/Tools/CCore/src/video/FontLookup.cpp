/* FontLookup.cpp */
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

#include <CCore/inc/video/FontLookup.h>

namespace CCore {
namespace Video {

/* class FontLookup::Step */

StepResult FontLookup::Step::finish(FontLookup &obj,StepResult result)
 {
  if( result==StepFinalOk ) obj.buildIndex();

  return result;
 }

FontLookup::Step::Step()
 {
 }

FontLookup::Step::~Step()
 {
 }

StepResult FontLookup::Step::start(FontLookup &obj,bool use_cache)
 {
  return finish(obj,dbstep.start(obj.fdb,use_cache));
 }

StepResult FontLookup::Step::step(IncrementalProgress &progress,FontLookup &obj)
 {
  return finish(obj,dbstep.step(progress,obj.fdb));
 }

void FontLookup::Step::erase() noexcept
 {
  dbstep.erase();
 }

/* class FontLookup */

FontCouple FontLookup::Build(const FontInfo *info,Coord font_size,const FreeTypeFont::Config &font_config)
 {
  try
    {
     FontCouple ret;

     ret.param.engine_type=FontParam::EngineFreeType;
     ret.param.file_name=info->file_name;
     ret.param.size_type=FontParam::SizeXY;
     ret.param.set_size.size_xy=font_size;
     ret.param.cfg=font_config;

     ret.create();

     return ret;
    }
  catch(...)
    {
     return FontCouple();
    }
 }

void FontLookup::buildIndex()
 {
  index.build(fdb, [] (const FontInfo &obj) { return obj.scalable; } ,
                   [] (const FontInfo &a,const FontInfo &b) { return AlphaCmp(CmpAsStr(a.family),CmpAsStr(b.family),
                                                                              a.bold,b.bold,
                                                                              a.italic,b.italic); } );
 }

FontLookup::FontLookup(InitType type)
 {
  switch( type )
    {
     case Populate :
      {
       fdb.populate();
       buildIndex();
      }
     break;

     case Cache :
      {
       fdb.cache();
       buildIndex();
      }
     break;
    }
 }

FontLookup::~FontLookup()
 {
 }

const FontInfo * FontLookup::find(StrLen family,bool bold,bool italic) const
 {
  return index.find( [=] (const FontInfo &obj) { return AlphaCmp(CmpAsStr(obj.family),CmpAsStr(family),
                                                                 obj.bold,bold,
                                                                 obj.italic,italic); } );
 }

FontCouple FontLookup::build(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config) const
 {
  const FontInfo *info=find(family,bold,italic);

  if( !info ) return FontCouple();

  return Build(info,font_size,font_config);
 }

/* class DialogFontLookup */

DialogFontLookup::DialogFontLookup() // TODO
 {

 }

} // namespace Video
} // namespace CCore

