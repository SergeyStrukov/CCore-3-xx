/* FreeType.cpp */
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

#include <CCore/inc/video/FreeType.h>

#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>
#include <CCore/inc/Exception.h>

#undef FTERRORS_H_

#define FT_ERROR_START_LIST
#define FT_ERRORDEF( e, v, s )  case v : return s;
#define FT_ERROR_END_LIST

namespace CCore {
namespace Video {
namespace FreeType {

/* DrawGlyph() */

void DrawGlyph(FrameBuf<DesktopColor> &buf,Point pos,const FT_Bitmap &bmp,VColor vc,GammaFunc gamma,bool bgr)
 {
  if( bmp.pitch<0 )
    {
     Printf(Exception,"CCore::Video::FreeType::DrawGlyph(...) : negative pitch");
    }

  switch( bmp.pixel_mode )
    {
     case FT_PIXEL_MODE_MONO :
      {
       void *base=bmp.buffer;
       Coord dx=Coord(bmp.width);
       Coord dy=Coord(bmp.rows);
       DLineType dline=DLineType(bmp.pitch);

       ColorPlane plane(base,dx,dy,dline);

       buf.glyph_safe(pos,MonoGlyph(plane),vc);
      }
     break;

     case FT_PIXEL_MODE_GRAY :
      {
       if( bmp.num_grays!=256 )
         {
          Printf(Exception,"CCore::Video::FreeType::DrawGlyph(...) : unexpected num grays #;",bmp.num_grays);
         }

       void *base=bmp.buffer;
       Coord dx=Coord(bmp.width);
       Coord dy=Coord(bmp.rows);
       DLineType dline=DLineType(bmp.pitch);

       ColorPlane plane(base,dx,dy,dline);

       buf.glyph_safe(pos,GrayGlyph(plane),vc,gamma);
      }
     break;

     case FT_PIXEL_MODE_LCD :
      {
       if( bmp.num_grays!=256 )
         {
          Printf(Exception,"CCore::Video::FreeType::DrawGlyph(...) : unexpected num grays #;",bmp.num_grays);
         }

       void *base=bmp.buffer;
       Coord dx=Coord(bmp.width/3);
       Coord dy=Coord(bmp.rows);
       DLineType dline=DLineType(bmp.pitch);

       ColorPlane plane(base,dx,dy,dline);

       buf.glyph_safe(pos,RGBGlyph(plane),vc,gamma,bgr);
      }
     break;

     default:
      {
       Printf(Exception,"CCore::Video::FreeType::DrawGlyph(...) : unexpected pixel mode #;",bmp.pixel_mode);
      }
    }
 }

/* class Error */

const char * Error::GetDesc(FT_Error error)
 {
  switch( error )
    {
     #include FT_ERRORS_H

     default: return 0;
    }
 }

/* class Lib */

Lib::Lib()
 {
  if( FT_Error error = FT_Init_FreeType(&lib) )
    {
     Printf(Exception,"CCore::Video::FreeType::Lib::Lib() : #;",Error(error));
    }
 }

Lib::~Lib()
 {
  if( FT_Error error = FT_Done_FreeType(lib) )
    {
     Printf(NoException,"CCore::Video::FreeType::Lib::~Lib() : #;",Error(error));
    }
 }

void Lib::setLCDFilter(FT_LcdFilter filter)
 {
  if( FT_Error error = FT_Library_SetLcdFilter(lib,filter) )
    {
     Printf(Exception,"CCore::Video::FreeType::Lib::setLCDFilter(...) : #;",Error(error));
    }
 }

/* class Face */

Face::Face(FT_Library lib,Mutex &mutex_,StrLen file_name,FT_Long index)
 : mutex(mutex_)
 {
  MakeString<MaxPathLen+1> out;

  if( !out.add(file_name,Null) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::Face(...,#.q;,...) : too long file name",file_name);
    }

  FT_Error error;

  {
   Mutex::Lock lock(mutex);

   error=FT_New_Face(lib,out.getZStr(),index,&face);
  }

  if( error )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::Face(...,#.q;,#;) : #;",file_name,index,Error(error));
    }
 }

Face::Face(FT_Library lib,Mutex &mutex_,StrLen file_name,bool &is_font,FT_Long index) noexcept
 : mutex(mutex_)
 {
  is_font=false;

  MakeString<MaxPathLen+1> out;

  if( !out.add(file_name,Null) )
    {
     Printf(NoException,"CCore::Video::FreeType::Face::Face(...,#.q;,...) : too long file name",file_name);

     face=0;

     return;
    }

  FT_Error error;

  {
   Mutex::Lock lock(mutex);

   error=FT_New_Face(lib,out.getZStr(),index,&face);
  }

  if( error )
    {
     face=0;
    }
  else
    {
     is_font=true;
    }
 }

Face::Face(FT_Library lib,Mutex &mutex_,StrLen dir,StrLen file_name,FT_Long index)
 : mutex(mutex_)
 {
  MakeString<MaxPathLen+1> out;

  if( !out.add(dir,'/',file_name,Null) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::Face(...,#.q;,#.q;,...) : too long file name",dir,file_name);
    }

  FT_Error error;

  {
   Mutex::Lock lock(mutex);

   error=FT_New_Face(lib,out.getZStr(),index,&face);
  }

  if( error )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::Face(...,#.q;,#.q;,#;) : #;",dir,file_name,index,Error(error));
    }
 }

Face::~Face()
 {
  if( !face ) return;

  FT_Error error;

  {
   Mutex::Lock lock(mutex);

   error=FT_Done_Face(face);
  }

  if( error )
    {
     Printf(NoException,"CCore::Video::FreeType::Face::~Face()() : #;",Error(error));
    }
 }

 // set size

void Face::setPixelSize(Coord dx,Coord dy)
 {
  if( FT_Error error = FT_Set_Pixel_Sizes(face,dx,dy) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::setPixelSize(#;,#;) : #;",dx,dy,Error(error));
    }
 }

void Face::setFixedSize(FT_Int index)
 {
  if( FT_Error error = FT_Select_Size(face,index) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::setFixedSize(#;) : #;",index,Error(error));
    }
 }

 // metrics

FT_Vector Face::getKerning(FT_UInt prev_index,FT_UInt next_index,FT_UInt mode) const
 {
  FT_Vector ret;

  if( FT_Error error = FT_Get_Kerning(face,prev_index,next_index,mode,&ret) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::getKerning(...) : #;",Error(error));
    }

  return ret;
 }

 // glyph

FT_UInt Face::getGlyphIndex(FT_ULong unicode) const
 {
  return FT_Get_Char_Index(face,unicode);
 }

void Face::loadGlyph(FT_UInt index,FT_Int32 flags)
 {
  if( FT_Error error = FT_Load_Glyph(face,index,flags) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::loadGlyph(...) : #;",Error(error));
    }
 }

bool Face::emboldenGlyph(FT_Pos strength)
 {
  if( getGlyphFormat()!=FT_GLYPH_FORMAT_OUTLINE ) return false;

  if( FT_Error error = FT_Outline_Embolden(&face->glyph->outline,strength) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::emboldenGlyph(...) : #;",Error(error));
    }

  return true;
 }

bool Face::tryEmboldenGlyph(FT_Pos strength)
 {
  if( getGlyphFormat()!=FT_GLYPH_FORMAT_OUTLINE ) return false;

  if( FT_Outline_Embolden(&face->glyph->outline,strength) ) return false;

  return true;
 }

bool Face::renderGlyph(FT_Render_Mode mode)
 {
  if( getGlyphFormat()==FT_GLYPH_FORMAT_BITMAP ) return false;

  if( FT_Error error = FT_Render_Glyph(face->glyph,mode) )
    {
     Printf(Exception,"CCore::Video::FreeType::Face::renderGlyph(...) : #;",Error(error));
    }

  return true;
 }

} // namespace FreeType
} // namespace Video
} // namespace CCore

