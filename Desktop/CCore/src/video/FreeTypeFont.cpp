/* FreeTypeFont.cpp */
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

#include <CCore/inc/video/FreeTypeFont.h>

#include <CCore/inc/video/FreeType.h>

#include <CCore/inc/AutoGlobal.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* enum FontHintType */

const char * GetTextDesc(FontHintType fht)
 {
  switch( fht )
    {
     default: return "???";

     case FontHintNone : return "FontHintNone";

     case FontHintNative : return "FontHintNative";

     case FontHintAuto : return "FontHintAuto";
    }
 }

inline FT_Int32 ToFlags(FontHintType fht)
 {
  switch( fht )
    {
     default: return FT_LOAD_NO_HINTING|FT_LOAD_NO_AUTOHINT;

     case FontHintNative : return FT_LOAD_NO_AUTOHINT;

     case FontHintAuto : return FT_LOAD_FORCE_AUTOHINT;
    }
 }

/* enum FontSmoothType */

const char * GetTextDesc(FontSmoothType fsm)
 {
  switch( fsm )
    {
     default: return "???";

     case FontSmoothNone : return "FontSmoothNone";

     case FontSmooth : return "FontSmooth";

     case FontSmoothLCD_RGB : return "FontSmoothLCD_RGB";

     case FontSmoothLCD_BGR : return "FontSmoothLCD_BGR";
    }
 }

inline FT_Render_Mode ToMode(FontSmoothType fsm)
 {
  switch( fsm )
    {
     default: return FT_RENDER_MODE_MONO;

     case FontSmooth : return FT_RENDER_MODE_NORMAL;

     case FontSmoothLCD_RGB :
     case FontSmoothLCD_BGR : return FT_RENDER_MODE_LCD;
    }
 }

/* struct FreeTypeFont::Global */

struct FreeTypeFont::Global
 {
  Mutex mutex;
  FreeType::Lib lib;
  CharMapTable map;

  Global() : mutex("FreeTypeFont"),lib(FT_LCD_FILTER_DEFAULT) {}
 };

/* struct FreeTypeFont::Inner */

struct FreeTypeFont::Inner : AutoGlobal<Global>::Lock
 {
  // data

  mutable FreeType::Face face;
  Config cfg;
  GammaTable gamma_table;

  FontSize font_size;

  struct CharX
   {
    Coord dx;
    Coord dx0;
    Coord dx1;
   };

  CharX char_x[256];

  // constructors

  explicit Inner(StrLen file_name)
   : AutoGlobal<Global>::Lock(Object),
     face(Object->lib,Object->mutex,file_name)
   {
    updateFontSize();
   }

  Inner(StrLen file_name,bool &is_font)
   : AutoGlobal<Global>::Lock(Object),
     face(Object->lib,Object->mutex,file_name,is_font)
   {
    if( is_font )
      {
       try
         {
          updateFontSize();
         }
       catch(...)
         {
          Printf(NoException,"file_name #;",file_name);

          is_font=false;
         }
      }
   }

  Inner(StrLen dir,StrLen file_name)
   : AutoGlobal<Global>::Lock(Object),
     face(Object->lib,Object->mutex,dir,file_name)
   {
    updateFontSize();
   }

  ~Inner() {}

  // methods

  using IndexType = FT_UInt ;

  CharX text(char ch)
   {
    auto index=face.getGlyphIndex(Object->map(ch));

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength )
      {
       if( !face.tryEmboldenGlyph(cfg.strength) ) cfg.strength=0;
      }

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    auto &metrics=face.getGlyphMetrics();

    Coord dx0=0;
    Coord dx1=0;

    if( metrics.horiBearingX<0 )
      {
       dx0=FreeType::RoundUp(-metrics.horiBearingX);
      }

    FT_Pos extra=metrics.horiBearingX+metrics.width-metrics.horiAdvance;

    if( extra>0 )
      {
       dx1=FreeType::RoundUp(extra);
      }

    return {placement.getDelta().x,dx0,dx1};
   }

  Coord kerning(IndexType &prev_index,char ch) const
   {
    Coord ret=0;

    auto index=face.getGlyphIndex(Object->map(ch));

    if( prev_index && index )
      {
       FT_Vector delta=face.getKerning(prev_index,index);

       ret=FreeType::Round(delta.x);
      }

    prev_index=index;

    return ret;
   }

  CharX table_text(char ch) const
   {
    return char_x[uint8(ch)];
   }

  CharX table_text(IndexType &prev_index,char ch) const
   {
    CharX ret=table_text(ch);
    Coord delta=kerning(prev_index,ch);

    ret.dx+=delta;

    return ret;
   }

  void updateFontSize()
   {
    if( !face.hasKerning() ) cfg.use_kerning=false;

    font_size.min_dx=MaxCoord;
    font_size.max_dx=0;
    font_size.dx0=0;
    font_size.dx1=0;

    for(int i=-128; i<128 ;i++)
      {
       char ch=char(i);
       CharX met=text(ch);

       Replace_min(font_size.min_dx,met.dx);
       Replace_max(font_size.max_dx,met.dx);
       Replace_max(font_size.dx0,met.dx0);
       Replace_max(font_size.dx1,met.dx1);

       char_x[uint8(ch)]=met;
      }

    Coord dy=FreeType::RoundUp(face.getMetrics().height);
    Coord by=FreeType::RoundUp(face.getMetrics().ascender);
    Coord ey=FreeType::RoundUp(-face.getMetrics().descender);

    if( by+ey>dy )
      {
       font_size.dy=by+ey;
       font_size.by=by;
      }
    else
      {
       font_size.dy=dy;
       font_size.by=by+(dy-by-ey)/2;
      }

    font_size.skew=0;

    if( face.isSFNT() )
      {
       if( const TT_HoriHeader *ptr=face.getTTHoriHeader() )
         {
          MCoord P=ptr->caret_Slope_Run;
          MCoord Q=ptr->caret_Slope_Rise;

          if( P!=0 && Q>0 )
            {
             font_size.skew=Coord( (DCoord(P)*font_size.dy)/Q ); // (P/Q)*font_size.dy
            }
         }
      }
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,char ch,VColor vc) const
   {
    auto index=face.getGlyphIndex(Object->map(ch));

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength ) face.emboldenGlyph(cfg.strength);

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    bool ret=face.drawGlyph(buf,placement.toPos(base),vc,gamma_table.getFunc(),cfg.fsm==FontSmoothLCD_BGR);

    base+=placement.getDelta();

    return ret;
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,IndexType &prev_index,char ch,VColor vc) const
   {
    auto index=face.getGlyphIndex(Object->map(ch));

    if( prev_index && index )
      {
       FT_Vector delta=face.getKerning(prev_index,index);

       base+={FreeType::Round(delta.x),FreeType::Round(delta.y)};
      }

    prev_index=index;

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength ) face.emboldenGlyph(cfg.strength);

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    bool ret=face.drawGlyph(buf,placement.toPos(base),vc,gamma_table.getFunc(),cfg.fsm==FontSmoothLCD_BGR);

    base+=placement.getDelta();

    return ret;
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,char ch,ulen ch_index,PointMap map,CharFunction func) const
   {
    auto index=face.getGlyphIndex(Object->map(ch));

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength ) face.emboldenGlyph(cfg.strength);

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    Point delta=placement.getDelta();
    VColor vc=func(ch_index,ch,map(base),delta);

    bool ret=face.drawGlyph(buf,placement.toPos(base),vc,gamma_table.getFunc(),cfg.fsm==FontSmoothLCD_BGR);

    base+=delta;

    return ret;
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,IndexType &prev_index,char ch,ulen ch_index,PointMap map,CharFunction func) const
   {
    auto index=face.getGlyphIndex(Object->map(ch));

    if( prev_index && index )
      {
       FT_Vector delta=face.getKerning(prev_index,index);

       base+={FreeType::Round(delta.x),FreeType::Round(delta.y)};
      }

    prev_index=index;

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength ) face.emboldenGlyph(cfg.strength);

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    Point delta=placement.getDelta();
    VColor vc=func(ch_index,ch,map(base),delta);

    bool ret=face.drawGlyph(buf,placement.toPos(base),vc,gamma_table.getFunc(),cfg.fsm==FontSmoothLCD_BGR);

    base+=delta;

    return ret;
   }

  // global

  static AutoGlobal<Global> Object;
 };

AutoGlobal<FreeTypeFont::Global> FreeTypeFont::Inner::Object CCORE_INITPRI_3 ;

/* class FreeTypeFont::Base */

class FreeTypeFont::Base : public FontBase , Inner
 {
  private:

   void textRun(AbstractSparseString &str,FuncArgType<CharX> func) const
    {
     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.applyChar( [this,&index,func] (char ch) { func( table_text(index,ch) ); } );
       }
     else
       {
        str.applyChar( [this,func] (char ch) { func( table_text(ch) ); } );
       }
    }

   void textRunWhile(AbstractSparseString &str,FuncType<bool,CharX> func) const
    {
     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.applyChar( [this,&index,func] (char ch) { return func( table_text(index,ch) ); } );
       }
     else
       {
        str.applyChar( [this,func] (char ch) { return func( table_text(ch) ); } );
       }
    }

   Coord toBaseline(Point point) const
    {
     if( font_size.skew )
       {
        Coord delta=To16( (font_size.skew*MCoord(point.y))/font_size.dy ); // (skew/dy)*y

        return IntAdd(point.x,delta);
       }
     else
       {
        return point.x;
       }
    }

   ulen prefixLen(AbstractSparseString &str,Coord x) const
    {
     ulen ret=0;

     if( x<0 ) return ret;

     textRunWhile(str,[&] (CharX met)
                          {
                           x-=met.dx;

                           if( x<0 ) return false;

                           ret++;

                           return true;

                          } );

     return ret;
    }

   // draw text

   MCoord text_dx(AbstractSparseString &str) const
    {
     MCoord ret=0;

     textRun(str, [&] (CharX met)
                      {
                       if( ret>=0 && met.dx>MaxMCoord-ret )
                         {
                          Printf(Exception,"CCore::Video::FreeTypeFont::Base::text_dx(...) : overflow");
                         }

                       ret+=met.dx;

                      } );

     return ret;
    }

   ulen skipCount(AbstractSparseString &str,MCoord &x) const // return suffix length
    {
     ULenSat ret;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [&] (StrLen str)
                       {
                        if( ret>0 )
                          {
                           ret+=str.len;
                          }
                        else
                          {
                           for(; +str ;++str)
                             {
                              char ch=*str;
                              Coord delta=kerning(index,ch);
                              CharX met=table_text(ch);

                              if( x+met.dx+met.dx1<0 )
                                {
                                 x+=delta+met.dx;
                                }
                              else
                                {
                                 ret=str.len;

                                 break;
                                }
                             }
                          }

                       } );
       }
     else
       {
        str.apply( [&] (StrLen str)
                       {
                        if( ret>0 )
                          {
                           ret+=str.len;
                          }
                        else
                          {
                           for(; +str ;++str)
                             {
                              CharX met=table_text(*str);

                              if( x+met.dx+met.dx1<0 )
                                {
                                 x+=met.dx;
                                }
                              else
                                {
                                 ret=str.len;

                                 break;
                                }
                             }
                          }

                       } );
       }

     if( ret.overflow )
       {
        Printf(Exception,"CCore::Video::FreeTypeFont::Base::skipCount(...) : overflow");
       }

     return ret.value;
    }

   Coord skip(AbstractSparseString &str,MCoord x) const
    {
     if( x>=0 )
       {
        return Coord(x);
       }

     ulen len=skipCount(str,x);

     str.cutSuffix(len);

     return Coord(x);
    }

   Coord skip(AbstractSparseString &str,MCoord x,ulen &index) const
    {
     if( x>=0 )
       {
        index=0;

        return Coord(x);
       }

     ulen len=skipCount(str,x);

     str.cutSuffix_index(len,index);

     return Coord(x);
    }

   Point prepare(Coord dx,Coord dy,TextPlace place,AbstractSparseString &str) const
    {
     Coord y;

     switch( place.align_y )
       {
        case AlignY_Top : y=font_size.by; break;

        case AlignY_Center : y=(dy-font_size.dy)/2+font_size.by; break;

        case AlignY_Bottom : y=dy-font_size.dy+font_size.by; break;

        default: y=place.y;
       }

     Coord x;

     switch( place.align_x )
       {
        case AlignX_Left : x=font_size.dx0; break;

        case AlignX_Right :
         {
          MCoord tdx=text_dx(str);

          x=skip(str,dx-font_size.dx1-tdx);
         }
        break;

        case AlignX_Center :
         {
          MCoord tdx=text_dx(str);

          x=skip(str,(dx-tdx)/2);
         }
        break;

        default: x=place.x;
       }

     return {x,y};
    }

   Point prepare(Coord dx,Coord dy,TextPlace place,AbstractSparseString &str,ulen &index) const
    {
     Coord y;

     switch( place.align_y )
       {
        case AlignY_Top : y=font_size.by; break;

        case AlignY_Center : y=(dy-font_size.dy)/2+font_size.by; break;

        case AlignY_Bottom : y=dy-font_size.dy+font_size.by; break;

        default: y=place.y;
       }

     Coord x;

     switch( place.align_x )
       {
        case AlignX_Left : index=0; x=font_size.dx0; break;

        case AlignX_Right :
         {
          MCoord tdx=text_dx(str);

          x=skip(str,dx-font_size.dx1-tdx,index);
         }
        break;

        case AlignX_Center :
         {
          MCoord tdx=text_dx(str);

          x=skip(str,(dx-tdx)/2,index);
         }
        break;

        default: index=0; x=place.x;
       }

     return {x,y};
    }

   void text(FrameBuf<DesktopColor> &buf,Point base,AbstractSparseString &str,VColor vc) const
    {
     if( base.y<font_size.by-font_size.dy || base.y>buf.dY()+(MCoord)font_size.by ) return;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.applyChar( [&] (char ch) { return glyph(buf,base,index,ch,vc); } );
       }
     else
       {
        str.applyChar( [&] (char ch) { return glyph(buf,base,ch,vc); } );
       }
    }

   void text(FrameBuf<DesktopColor> &buf,Point base,AbstractSparseString &str,ulen ch_index,PointMap map,CharFunction func) const
    {
     if( base.y<font_size.by-font_size.dy || base.y>buf.dY()+(MCoord)font_size.by ) return;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.applyChar( [&] (char ch) { return glyph(buf,base,index,ch,ch_index++,map,func); } );
       }
     else
       {
        str.applyChar( [&] (char ch) { return glyph(buf,base,ch,ch_index++,map,func); } );
       }
    }

   void text(DrawBuf buf,Coord dx,Coord dy,TextPlace place,AbstractSparseString &str,VColor vc) const
    {
     if( !buf ) return;

     Point base=prepare(dx,dy,place,str);

     text(buf.getFrameBuf(),buf.map(base),str,vc);
    }

   void text(DrawBuf buf,Coord dx,Coord dy,TextPlace place,AbstractSparseString &str,CharFunction func) const
    {
     if( !buf ) return;

     ulen index;
     Point base=prepare(dx,dy,place,str,index);

     text(buf.getFrameBuf(),buf.map(base),str,index,-buf.getMapper(),func);
    }

  public:

   // constructors

   explicit Base(StrLen file_name) : Inner(file_name) {}

   Base(StrLen file_name,bool &is_font) : Inner(file_name,is_font) {}

   Base(StrLen dir,StrLen file_name) : Inner(dir,file_name) {}

   virtual ~Base() {}

   // AbstractFont

   virtual FontSize getSize() const
    {
     return font_size;
    }

   virtual TextSize text(AbstractSparseString &str) const
    {
     TextSize ret;

     ret.dy=font_size.dy;
     ret.by=font_size.by;
     ret.dx0=0;
     ret.dx1=0;
     ret.skew=font_size.skew;

     CoordAcc acc;
     bool first=true;

     textRun(str, [&] (CharX met)
                      {
                       acc.add(met.dx);

                       if( first ) first=false,ret.dx0=met.dx0;

                       ret.dx1=met.dx1;

                      } );

     ret.dx=acc.value;

     if( ret.dx<0 ) ret.dx=0;

     acc.add(font_size.dx0);
     acc.add(font_size.dx1);

     ret.full_dx=acc.value;
     ret.overflow=acc.overflow;

     return ret;
    }

   virtual ulen fit(AbstractSparseString &str,Coord full_dx) const
    {
     if( full_dx<0 ) return 0;

     return prefixLen(str,full_dx-font_size.dx0-font_size.dx1);
    }

   virtual ulen position(AbstractSparseString &str,Point point) const
    {
     Coord x=toBaseline(point);

     if( x<0 ) return 0;

     return 1+prefixLen(str,x);
    }

   virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,VColor vc) const
    {
     text(buf.cutRebase(pane),pane.dx,pane.dy,place,str,vc);
    }

   virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,CharFunction func) const
    {
     text(buf.cutRebase(pane),pane.dx,pane.dy,place,str,func);
    }

   // set params

   void setSize(Coord dx,Coord dy)
    {
     face.setPixelSize(dx,dy);

     updateFontSize();
    }

   void setFixedSize(ulen index)
    {
     face.setFixedSize((FT_Int)index);

     updateFontSize();
    }

   void setConfig(const Config &cfg_)
    {
     cfg=cfg_;

     updateFontSize();

     if( cfg.gamma_order!=gamma_table.getOrder() ) gamma_table.fill(cfg.gamma_order);
    }

   // get props

   StyleFlags getStyleFlags() const
    {
     StyleFlags ret;

     ret.scalable=face.isScalable();
     ret.monospace=face.isMonospace();
     ret.italic=face.isItalic();
     ret.bold=face.isBold();

     return ret;
    }

   Config getConfig() const
    {
     return cfg;
    }

   StrLen getFamily() const
    {
     return face.getFamily();
    }

   StrLen getStyle() const
    {
     return face.getStyle();
    }

   void getSizeList(Function<void (Coord dx,Coord dy)> func) const
    {
     for(auto size : face.getSizeList() ) func(size.width,size.height);
    }
 };

/* class FreeTypeFont */

auto FreeTypeFont::getBase() const -> Base *
 {
  return castPtr<Base>();
 }

 // constructors

FreeTypeFont::FreeTypeFont(StrLen file_name)
 : Font(new Base(file_name))
 {
 }

FreeTypeFont::FreeTypeFont(StrLen file_name,bool &is_font)
 : Font(new Base(file_name,is_font))
 {
 }

FreeTypeFont::FreeTypeFont(StrLen dir,StrLen file_name)
 : Font(new Base(dir,file_name))
 {
 }

 // set params

void FreeTypeFont::setSize(Coord dx,Coord dy)
 {
  if( Base *base=getBase() ) base->setSize(dx,dy);
 }

void FreeTypeFont::setFixedSize(ulen index)
 {
  if( Base *base=getBase() ) base->setFixedSize(index);
 }

void FreeTypeFont::setConfig(const Config &cfg)
 {
  if( Base *base=getBase() ) base->setConfig(cfg);
 }

 // get props

auto FreeTypeFont::getStyleFlags() const -> StyleFlags
 {
  if( Base *base=getBase() ) return base->getStyleFlags();

  return {};
 }

auto FreeTypeFont::getConfig() const -> Config
 {
  if( Base *base=getBase() ) return base->getConfig();

  return {};
 }

StrLen FreeTypeFont::getFamily() const
 {
  if( Base *base=getBase() ) return base->getFamily();

  return "Unknown"_c;
 }

StrLen FreeTypeFont::getStyle() const
 {
  if( Base *base=getBase() ) return base->getStyle();

  return Null;
 }

void FreeTypeFont::getSizeList(Function<void (Coord dx,Coord dy)> func) const
 {
  if( Base *base=getBase() ) base->getSizeList(func);
 }

/* class ProbeFreeTypeFont::Inner */

class ProbeFreeTypeFont::Inner : public MemBase_nocopy , AutoGlobal<FreeTypeFont::Global>::Lock
 {
   mutable FreeType::Face face;

  public:

   Inner(StrLen file_name,bool &is_font);

   ~Inner();

   StrLen getFamily() const;

   StrLen getStyle() const;

   FreeTypeFont::StyleFlags getStyleFlags() const;
 };

ProbeFreeTypeFont::Inner::Inner(StrLen file_name,bool &is_font)
 : AutoGlobal<FreeTypeFont::Global>::Lock(FreeTypeFont::Inner::Object),
   face(FreeTypeFont::Inner::Object->lib,FreeTypeFont::Inner::Object->mutex,file_name,is_font)
 {
 }

ProbeFreeTypeFont::Inner::~Inner()
 {
 }

StrLen ProbeFreeTypeFont::Inner::getFamily() const
 {
  return face.getFamily();
 }

StrLen ProbeFreeTypeFont::Inner::getStyle() const
 {
  return face.getStyle();
 }

FreeTypeFont::StyleFlags ProbeFreeTypeFont::Inner::getStyleFlags() const
 {
  FreeTypeFont::StyleFlags ret;

  ret.scalable=face.isScalable();
  ret.monospace=face.isMonospace();
  ret.italic=face.isItalic();
  ret.bold=face.isBold();

  return ret;
 }

/* class ProbeFreeTypeFont */

ProbeFreeTypeFont::ProbeFreeTypeFont(StrLen file_name,bool &is_font)
 {
  ptr=new Inner(file_name,is_font);
 }

ProbeFreeTypeFont::~ProbeFreeTypeFont()
 {
  delete ptr;
 }

StrLen ProbeFreeTypeFont::getFamily() const
 {
  return ptr->getFamily();
 }

StrLen ProbeFreeTypeFont::getStyle() const
 {
  return ptr->getStyle();
 }

FreeTypeFont::StyleFlags ProbeFreeTypeFont::getStyleFlags() const
 {
  return ptr->getStyleFlags();
 }

} // namespace Video
} // namespace CCore

