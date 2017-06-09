/* FreeType.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FreeType_h
#define CCore_inc_video_FreeType_h

#include <CCore/inc/video/DrawBuf.h>
#include <CCore/inc/Task.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_LCD_FILTER_H
#include FT_TRUETYPE_TABLES_H

namespace CCore {
namespace Video {
namespace FreeType {

/* Round...() */

inline Coord Round(FT_Pos x) { return IntRShift(x+32,6); }

inline Coord RoundUp(FT_Pos x) { return IntRShift(x+63,6); }

inline Coord RoundDown(FT_Pos x) { return IntRShift(x,6); }

inline const char * NonNullPtr(const char *str) { return str?str:""; }

/* DrawGlyph() */

void DrawGlyph(FrameBuf<DesktopColor> &buf,Point pos,const FT_Bitmap &bmp,VColor vc,GammaFunc gamma,bool bgr);

/* classes */

class Error;

class Lib;

struct Placement;

class Face;

/* class Error */

class Error
 {
   FT_Error error;

  private:

   static const char * GetDesc(FT_Error error);

  public:

   explicit Error(FT_Error error_) : error(error_) {}

   void print(PrinterType &out) const
    {
     if( const char *desc=GetDesc(error) )
       {
        Putobj(out,desc);
       }
     else
       {
        Printf(out,"code #;",error);
       }
    }
 };

/* class Lib */

class Lib : NoCopy
 {
   FT_Library lib;

  public:

   Lib();

   explicit Lib(FT_LcdFilter filter) : Lib() { setLCDFilter(filter); }

   ~Lib();

   operator FT_Library() const { return lib; }

   void setLCDFilter(FT_LcdFilter filter);
 };

/* struct Placement */

struct Placement
 {
  FT_Int left; // base.x+left
  FT_Int top;  // base.y-top

  // 26.6 fixed

  FT_Pos delta_x;
  FT_Pos delta_y;

  Placement() {}

  Placement(FT_GlyphSlot slot)
   {
    left=slot->bitmap_left;
    top=slot->bitmap_top;
    delta_x=slot->advance.x;
    delta_y=slot->advance.y;
   }

  Point toBase(Point pos) const { return pos+Point(-left,top); }

  Point toPos(Point base) const { return base+Point(left,-top); }

  Point getDelta() const
   {
    return Point(Round(delta_x),Round(delta_y));
   }
 };

/* class Face */

class Face : NoCopy
 {
   Mutex &mutex;

   FT_Face face;

  public:

   Face(FT_Library lib,Mutex &mutex,StrLen file_name,FT_Long index=0);

   Face(FT_Library lib,Mutex &mutex,StrLen file_name,bool &is_font,FT_Long index=0);

   Face(FT_Library lib,Mutex &mutex,StrLen dir,StrLen file_name,FT_Long index=0); // dir/file_name

   ~Face();

   // props

   bool isScalable() const { return FT_IS_SCALABLE(face); }

   bool isMonospace() const { return FT_IS_FIXED_WIDTH(face); }

   bool isBold() const { return face->style_flags&FT_STYLE_FLAG_BOLD; }

   bool isItalic() const { return face->style_flags&FT_STYLE_FLAG_ITALIC; }

   bool hasKerning() const { return FT_HAS_KERNING(face); }

   bool isSFNT() const { return FT_IS_SFNT(face); }

   const char * getFamily() const { return NonNullPtr(face->family_name); }

   const char * getStyle() const { return NonNullPtr(face->style_name); }

   PtrLen<const FT_Bitmap_Size> getSizeList() const { return Range(face->available_sizes,face->num_fixed_sizes); }

   // tables

   const TT_HoriHeader * getTTHoriHeader() const { return static_cast<const TT_HoriHeader *>(FT_Get_Sfnt_Table(face,FT_SFNT_HHEA)); }

#if 0

   const TT_Header * getTTHeader() const { return static_cast<const TT_Header *>(FT_Get_Sfnt_Table(face,FT_SFNT_HEAD)); }

   const TT_OS2 * getTTOS2Header() const { return static_cast<const TT_OS2 *>(FT_Get_Sfnt_Table(face,FT_SFNT_OS2)); }

#endif

   // set size

   void setPixelSize(Coord dx,Coord dy);

   void setFixedSize(FT_Int index);

   // metrics

   const FT_Size_Metrics & getMetrics() const { return face->size->metrics; }

#if 0

   const FT_BBox & getBBox() const { return face->bbox; }

   FT_BBox getScaledBBox() const;

#endif

   FT_Vector getKerning(FT_UInt prev_index,FT_UInt next_index,FT_UInt mode=FT_KERNING_DEFAULT) const;

   // glyph

   FT_UInt getGlyphIndex(FT_ULong unicode) const;

   void loadGlyph(FT_UInt index,FT_Int32 flags=FT_LOAD_DEFAULT);

   bool emboldenGlyph(FT_Pos strength);

   bool tryEmboldenGlyph(FT_Pos strength);

   bool renderGlyph(FT_Render_Mode mode=FT_RENDER_MODE_NORMAL);

   // glyph metrics

   FT_Glyph_Format getGlyphFormat() const { return face->glyph->format; }

   const FT_Glyph_Metrics & getGlyphMetrics() const { return face->glyph->metrics; }

   Placement getGlyphPlacement() const { return face->glyph; }

   // draw

   const FT_Bitmap & getGlyphBitmap() const { return face->glyph->bitmap; }

   bool drawGlyph(FrameBuf<DesktopColor> &buf,Point pos,VColor vc,GammaFunc gamma,bool bgr=false) const
    {
     DrawGlyph(buf,pos,getGlyphBitmap(),vc,gamma,bgr);

     return pos.x<buf.dX();
    }
 };

} // namespace FreeType
} // namespace Video
} // namespace CCore

#endif

