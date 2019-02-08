/* FontParam.h */
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

#ifndef CCore_inc_video_FontParam_h
#define CCore_inc_video_FontParam_h

#include <CCore/inc/video/FreeTypeFont.h>

#include <CCore/inc/String.h>

namespace CCore {
namespace Video {

/* classes */

struct FontParam;

struct FontCouple;

/* struct FontParam */

struct FontParam
 {
  // engine_type

  enum EngineType
   {
    EngineDefault,
    EngineFreeType
   };

  friend const char * GetTextDesc(EngineType engine_type);

  EngineType engine_type = EngineDefault ;

  // file_name

  String file_name;

  // size_type

  enum SizeType
   {
    SizeXY,
    SizePoint,
    SizeIndex
   };

  friend const char * GetTextDesc(SizeType size_type);

  SizeType size_type = SizeXY ;

  // set_size

  union SetSize
   {
    Coord size_xy;
    Point size;
    ulen index;

    SetSize() noexcept { size_xy=0; }
   };

  SetSize set_size;

  // cfg

  AbstractExtFont::Config cfg;

  // constructors

  FontParam() noexcept {}

  // methods

  Font create() const;
 };

/* struct FontCouple */

struct FontCouple
 {
  Font font;
  FontParam param;

  FontCouple() noexcept {}

  void create() { font=param.create(); }
 };

} // namespace Video
} // namespace CCore

#endif

