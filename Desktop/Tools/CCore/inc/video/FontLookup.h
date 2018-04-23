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

/* classes */

class FontLookup;

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

   FontCouple build(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config={}) const; // noexcept
 };

} // namespace Video
} // namespace CCore

#endif

