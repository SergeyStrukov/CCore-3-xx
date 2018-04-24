/* FontLookup.h */
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

#ifndef CCore_inc_video_FontLookup_h
#define CCore_inc_video_FontLookup_h

#include <CCore/inc/video/FontDatabase.h>
#include <CCore/inc/video/FontParam.h>

namespace CCore {
namespace Video {

/* words */

enum BoldType { Bold };

enum ItalicType { Italic };

/* classes */

struct FontId;

struct Bolder;

class FontLookup;

/* struct FontId */

struct FontId
 {
  StrLen family;
  bool bold = false ;
  bool italic = false ;

  FontId(StrLen family_) : family(family_) {}

  FontId(const char *family_) : family(family_) {}

  FontId(const ConstTypeRangeableType<char> &obj) : family(Range_const(obj)) {}
 };

inline FontId operator | (FontId id,BoldType) { id.bold=true; return id; }

inline FontId operator | (FontId id,ItalicType) { id.italic=true; return id; }

/* struct Bolder */

struct Bolder : FreeTypeFont::Config
 {
  explicit Bolder(int strength_) { strength=strength_; }
 };

/* class FontLookup */

class FontLookup : NoCopy
 {
   FontDatabase fdb;
   FontIndex index;

  private:

   static FontCouple Build(const FontInfo *info,Coord font_size,const FreeTypeFont::Config &font_config);

   void buildIndex();

  public:

   enum InitType
    {
     None,
     Populate,
     Cache
    };

   explicit FontLookup(InitType type=Cache);

   ~FontLookup();

   // incremental

   class Step : NoCopy
    {
      FontDatabase::Step dbstep;

     private:

      StepResult finish(FontLookup &obj,StepResult result);

     public:

      Step();

      ~Step();

      StepResult start(FontLookup &obj,bool use_cache=true);

      StepResult step(IncrementalProgress &progress,FontLookup &obj);

      void erase() noexcept;
    };

   using Incremental = IncrementalBuilder<FontLookup,Step> ;

   void cache(Incremental &inc,bool use_cache=true) { inc.start(*this,use_cache); }

   // methods

   const FontInfo * find(StrLen family,bool bold,bool italic) const;

   const FontInfo * find(FontId id) const { return find(id.family,id.bold,id.italic); }

   FontCouple build(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config={}) const; // noexcept

   FontCouple build(FontId id,Coord font_size,const FreeTypeFont::Config &font_config={}) const { return build(id.family,id.bold,id.italic,font_size,font_config); }
 };

} // namespace Video
} // namespace CCore

#endif

