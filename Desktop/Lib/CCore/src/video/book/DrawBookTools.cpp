/* DrawBookTools.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/book/DrawBookTools.h>

#include <CCore/inc/Path.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {
namespace Book {
namespace DrawBook {

/* functions */

bool InsSpace(StrLen text)
 {
  if( text.len!=1 ) return true;

  switch( *text )
    {
     case '.' : case ',' : case ';' : case ':' : case ')' : return false;

     default: return true;
    }
 }

/* class FontMap */

auto FontMap::find(StrLen face,Coord size,int strength,bool bold,bool italic,Font fallback) -> Rec
 {
  const FontInfo *info=lookup.find(replace_map(face),bold,italic);

  if( !info )
    {
     Printf(NoException,"Font #.q; is not found",face);

     replace_map.addNotFound(face);

     return {fallback,true,true};
    }

  try
    {
     FreeTypeFont font(Range(info->file_name));

     SetFontSize(font,size);

     AbstractExtFont::Config cfg;

     cfg.strength=strength;

     SetFontConfig(font,cfg);

     return {font,true,false};
    }
  catch(...)
    {
     return {fallback,true,true};
    }
 }

auto FontMap::find(Book::TypeDef::Font *obj,Font fallback) -> Rec
 {
  return find(obj->face,scale*CastCoord(obj->size),obj->strength,obj->bold,obj->italic,fallback);
 }

void FontMap::SetSize(Font &font,Coord size)
 {
  SetFontSize(font,size);
 }

void FontMap::setScale(Ratio scale_)
 {
  scale=scale_;

  for(Rec &rec : map ) rec.ok=false;
 }

Font FontMap::operator () (Book::TypeDef::Font *obj,Font fallback)
 {
  if( !obj ) return fallback;

  if( ulen ext=obj->ext )
    {
     Rec &rec=map.at(ext-1);

     if( rec.ok ) return rec.font;

     if( rec.fallback )
       {
        rec.font=fallback;
       }
     else
       {
        SetSize(rec.font,scale*CastCoord(obj->size));
       }

     rec.ok=true;

     return rec.font;
    }
  else
    {
     Rec rec=find(obj,fallback);

     map.append_copy(rec);

     obj->ext=map.getLen();

     return rec.font;
    }
 }

/* class BitmapMap */

Bitmap * BitmapMap::append(StrLen file_name)
 {
  map.reserve(1);

  try
    {
     return map.append_fill(file,root,file_name);
    }
  catch(...)
    {
     return map.append_default();
    }
 }

void BitmapMap::setRoot(StrLen file_name)
 {
  SplitPath split1(file_name);
  SplitName split2(split1.path);

  file_name.len-=split2.name.len;

  root=file_name;
 }

BitmapMap::BitmapMap()
 {
 }

BitmapMap::~BitmapMap()
 {
 }

void BitmapMap::erase()
 {
  map.erase();

  file={};
  file_name=Empty;
  root=Null;
 }

void BitmapMap::setSource(const BinFileToRead &file_,const String &file_name_)
 {
  file=file_;
  file_name=file_name_;

  setRoot(Range(file_name));
 }

const Bitmap * BitmapMap::operator () (Book::TypeDef::Bitmap *obj)
 {
  if( !obj ) return 0;

  try
    {
     if( ulen ext=obj->ext )
       {
        return &map.at(ext-1);
       }
     else
       {
        Bitmap *ret=append(obj->file_name);

        obj->ext=map.getLen();

        return ret;
       }
    }
  catch(...) { return 0; }
 }

/* struct TableDesc */

void TableDesc::setBase()
 {
  Point base(space,space);

  for(ulen j : IndLim(tdy.len) )
    {
     base.x=space;

     for(ulen i : IndLim(tdx.len) )
       {
        span(i,j).base=base;

        base.x+=tdx[i]+space;
       }

     base.y+=tdy[j]+space;
    }
 }

Coord TableDesc::Size(PtrLen<const Coord> tdx,Coord space)
 {
  Coord ret=space;

  for(Coord x : tdx ) ret=AddSize(ret,AddSize(x,space));

  return ret;
 }

/* class FrameMap */

template <class T>
FrameExt * FrameMap::createType()
 {
  return new( pool.alloc(sizeof (T)) ) T();
 }

FrameExt * FrameMap::create(Book::TypeDef::OneLine *)
 {
  return createType<FrameExt_OneLine>();
 }

FrameExt * FrameMap::create(Book::TypeDef::MultiLine *)
 {
  return createType<FrameExt_MultiLine>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Text *obj)
 {
  if( !obj ) return 0;

  FrameExt *ret=0;

  obj->placement.getPtr().apply( [&] (auto *placement) { ret=create(placement); } );

  return ret;
 }

FrameExt * FrameMap::create(Book::TypeDef::FixedText *)
 {
  return createType<FrameExt>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Bitmap *)
 {
  return createType<FrameExt>();
 }

FrameExt * FrameMap::create(Book::TypeDef::TextList *)
 {
  return createType<FrameExt_TextList>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Collapse *)
 {
  return createType<FrameExt_Collapse>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Table *)
 {
  return createType<FrameExt_Table>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Frame *obj)
 {
  FrameExt *ret=0;

  obj->body.getPtr().apply( [&] (auto *obj) { ret=create(obj); } );

  if( !ret ) return createType<FrameExt>();

  return ret;
 }

void FrameMap::erase()
 {
  for(FrameExt *ext : buf ) ext->~FrameExt();

  buf.erase();

  pool.erase();
 }

FrameExt * FrameMap::operator () (Book::TypeDef::Frame *obj)
 {
  if( !obj ) return 0;

  if( ulen ext=obj->ext )
    {
     return buf.at(ext-1);
    }
  else
    {
     buf.reserve(1);

     FrameExt *ret=create(obj);

     buf.append_copy(ret);

     obj->ext=buf.getLen();

     return ret;
    }
 }

} // namespace DrawBook
} // namespace Book
} // namespace Video
} // namespace CCore


