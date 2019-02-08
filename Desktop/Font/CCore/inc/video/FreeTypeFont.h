/* FreeTypeFont.h */
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

#ifndef CCore_inc_video_FreeTypeFont_h
#define CCore_inc_video_FreeTypeFont_h

#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/GammaTable.h>
#include <CCore/inc/AutoGlobal.h>

namespace CCore {
namespace Video {

/* classes */

//enum FontHintType;

//enum FontSmoothType;

class CharMapHook;

struct AbstractExtFont;

class FreeTypeFont;

class ProbeFreeTypeFont;

/* enum FontHintType */

enum FontHintType
 {
  FontHintNone,
  FontHintNative,
  FontHintAuto
 };

const char * GetTextDesc(FontHintType fht);

/* enum FontSmoothType */

enum FontSmoothType
 {
  FontSmoothNone,
  FontSmooth,
  FontSmoothLCD_RGB,
  FontSmoothLCD_BGR
 };

const char * GetTextDesc(FontSmoothType fsm);

/* class CharMapHook */

class CharMapHook : AutoGlobal<CharMapTable>::Lock
 {
   static AutoGlobal<CharMapTable> Object;

  public:

   CharMapHook() : AutoGlobal<CharMapTable>::Lock(Object) {}

   ~CharMapHook() {}

   Unicode toUnicode(CharCodeType ch) const { return (*Object)(ch); }
 };

/* struct AbstractExtFont */

struct AbstractExtFont
 {
  struct StyleFlags
   {
    bool scalable;
    bool monospace;
    bool italic;
    bool bold;
   };

  struct Config
   {
    FontHintType fht = FontHintAuto ;
    FontSmoothType fsm = FontSmoothLCD_RGB ;
    bool use_kerning = true ;
    int strength = 0 ;
    double gamma_order = 0 ;

    Config() noexcept {}
   };

  // set params

  virtual void setSize(Coord dx,Coord dy) = 0 ;

  virtual void setFixedSize(ulen index) = 0 ;

  virtual void setConfig(const Config &cfg) = 0 ;

  // get props

  virtual StyleFlags getStyleFlags() const = 0 ;

  virtual Config getConfig() const = 0 ;

  virtual StrLen getFamily() const = 0 ;

  virtual StrLen getStyle() const = 0 ;

  virtual void getSizeList(Function<void (Coord dx,Coord dy)> func) const = 0 ;
 };

/* class FreeTypeFont */

class FreeTypeFont : public Font
 {
   struct Global;

   struct Inner;

   class Base;

   friend class ProbeFreeTypeFont;

  public:

   // constructors

   FreeTypeFont() noexcept {} // default, not a FreeType font!

   explicit FreeTypeFont(StrLen file_name);

   FreeTypeFont(StrLen file_name,bool &is_font);

   FreeTypeFont(StrLen dir,StrLen file_name); // dir/file_name

   ~FreeTypeFont() {}
 };

 // set params

void SetFontSize(const Font &font,Coord dx,Coord dy);

inline void SetFontSize(const Font &font,Point size) { SetFontSize(font,size.x,size.y); }

inline void SetFontSize(const Font &font,Coord dxy) { SetFontSize(font,dxy,dxy); }

void SetFixedFontSize(const Font &font,ulen index);

void SetFontConfig(const Font &font,const AbstractExtFont::Config &cfg);

 // get props

AbstractExtFont::StyleFlags GetFontStyleFlags(const Font &font);

AbstractExtFont::Config GetFontConfig(const Font &font);

inline FontClass GetFontClass(const Font &font) { return font->getFontClass(); }

StrLen GetFontFamily(const Font &font);

StrLen GetFontStyle(const Font &font);

void GetFontSizeList(const Font &font,Function<void (Coord dx,Coord dy)> func);

/* class ProbeFreeTypeFont */

class ProbeFreeTypeFont : NoCopy
 {
   class Inner;

   Inner *ptr;

  public:

   ProbeFreeTypeFont(StrLen file_name,bool &is_font);

   ~ProbeFreeTypeFont();

   // get props

   FontClass getClass() const;

   StrLen getFamily() const;

   StrLen getStyle() const;

   AbstractExtFont::StyleFlags getStyleFlags() const;
 };

 // get props

inline FontClass GetFontClass(const ProbeFreeTypeFont &font) { return font.getClass(); }

inline StrLen GetFontFamily(const ProbeFreeTypeFont &font) { return font.getFamily(); }

inline StrLen GetFontStyle(const ProbeFreeTypeFont &font) { return font.getStyle(); }

inline AbstractExtFont::StyleFlags GetFontStyleFlags(const ProbeFreeTypeFont &font) { return font.getStyleFlags(); }

} // namespace Video
} // namespace CCore

#endif

