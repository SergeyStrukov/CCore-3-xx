/* FreeTypeFont.cpp */
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

#include <CCore/inc/video/FreeTypeFont.h>

#include <CCore/inc/video/FreeType.h>

#include <CCore/inc/TextTools.h>

#ifdef CCORE_UTF8
# include <CCore/inc/CompactMap.h>
#endif

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

/* class CharMapHook */

AutoGlobal<CharMapTable> CharMapHook::Object CCORE_INITPRI_3 ;

/* struct FreeTypeFont::Global */

struct FreeTypeFont::Global
 {
  Mutex mutex;
  FreeType::Lib lib;

  Global() : mutex("!FreeTypeFont"),lib(FT_LCD_FILTER_DEFAULT) {}
 };

/* GetFontClass() */

static FontClass GetFontClass(const FreeType::Face &face)
 {
  if( auto *ptr=face.getTTOS2Header() )
    {
     uint16 fc=ptr->sFamilyClass;

     return Correct( FontClass(fc>>8) );
    }

  return FontHasNoClass;
 }

/* struct FreeTypeFont::Inner */

struct FreeTypeFont::Inner : AutoGlobal<Global>::Lock , CharMapHook
 {
  // data

  mutable FreeType::Face face;
  mutable bool use_strength = true ;
  AbstractExtFont::Config cfg;
  GammaTable gamma_table;

  FontSize font_size;

  struct CharX
   {
    Coord dx;
    Coord dx0;
    Coord dx1;
   };

  using IndexType = FT_UInt ;

#ifdef CCORE_UTF8

  mutable CompactRadixTreeMap<IndexType,CharX> map;

#else

  CharX map[256];

#endif

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

#ifdef CCORE_UTF8

  IndexType indexOf(Char ch) const
   {
    return face.getGlyphIndex(ch);
   }

#else

  IndexType indexOf(Char ch) const
   {
    return face.getGlyphIndex(toUnicode(ch));
   }

#endif

  Coord kerning(IndexType &prev_index,Char ch) const
   {
    Coord ret=0;

    auto index=indexOf(ch);

    if( prev_index && index )
      {
       FT_Vector delta=face.getKerning(prev_index,index);

       ret=FreeType::Round(delta.x);
      }

    prev_index=index;

    return ret;
   }

  CharX glyph_index(IndexType index) const
   {
    face.loadGlyph(index,ToFlags(cfg.fht));

    if( use_strength )
      {
       if( !face.tryEmboldenGlyph(cfg.strength) ) use_strength=false;
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

#ifdef CCORE_UTF8

  CharX glyph(Char ch) const
   {
    IndexType index=indexOf(ch);

    auto result=map.find_or_add(index);

    if( result.new_flag )
      {
       CharX ret=glyph_index(index);

       *result.obj=ret;

       return ret;
      }
    else
      {
       return *result.obj;
      }
   }

  void setCharX(char,IndexType index,CharX met)
   {
    Replace_min(font_size.min_dx,met.dx);
    Replace_max(font_size.max_dx,met.dx);
    Replace_max(font_size.dx0,met.dx0);
    Replace_max(font_size.dx1,met.dx1);

    map.find_or_add(index,met);
   }

#else

  CharX glyph(Char ch) const
   {
    return map[uint8(ch)];
   }

  void setCharX(char ch,IndexType,CharX met)
   {
    Replace_min(font_size.min_dx,met.dx);
    Replace_max(font_size.max_dx,met.dx);
    Replace_max(font_size.dx0,met.dx0);
    Replace_max(font_size.dx1,met.dx1);

    map[uint8(ch)]=met;
   }

#endif

  CharX glyph(IndexType &prev_index,Char ch) const
   {
    CharX ret=glyph(ch);
    Coord delta=kerning(prev_index,ch);

    ret.dx+=delta;

    return ret;
   }

  void updateFontSize()
   {
    use_strength = (cfg.strength!=0) ;

    if( !face.hasKerning() ) cfg.use_kerning=false;

    font_size.min_dx=MaxCoord;
    font_size.max_dx=0;
    font_size.dx0=0;
    font_size.dx1=0;

#ifdef CCORE_UTF8

    map.erase();

#endif

    AllChars( [this] (char ch)
                     {
                      IndexType index=face.getGlyphIndex(toUnicode(ch));

                      CharX met=glyph_index(index);

                      setCharX(ch,index,met);

                     } );

    Coord dy=FreeType::RoundUp(face.getMetrics().height);
    Coord by=FreeType::RoundUp(face.getMetrics().ascender);
    Coord ey=FreeType::RoundUp(-face.getMetrics().descender);

    if( by+ey>dy )
      {
       font_size.dy=by+ey+1;
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
          Coord P=ptr->caret_Slope_Run;
          Coord Q=ptr->caret_Slope_Rise;

          if( P!=0 && Q>0 )
            {
             font_size.skew=CoordMulDiv(P,font_size.dy,Q); // (P/Q)*font_size.dy
            }
         }
      }
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,Char ch,VColor vc) const
   {
    auto index=indexOf(ch);

    face.loadGlyph(index,ToFlags(cfg.fht));

    if( cfg.strength ) face.emboldenGlyph(cfg.strength);

    face.renderGlyph(ToMode(cfg.fsm));

    auto placement=face.getGlyphPlacement();

    bool ret=face.drawGlyph(buf,placement.toPos(base),vc,gamma_table.getFunc(),cfg.fsm==FontSmoothLCD_BGR);

    base+=placement.getDelta();

    return ret;
   }

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,IndexType &prev_index,Char ch,VColor vc) const
   {
    auto index=indexOf(ch);

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

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,Char ch,ulen ch_index,PointMap map,CharFunction func) const
   {
    auto index=indexOf(ch);

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

  bool glyph(FrameBuf<DesktopColor> &buf,Point &base,IndexType &prev_index,Char ch,ulen ch_index,PointMap map,CharFunction func) const
   {
    auto index=indexOf(ch);

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

class FreeTypeFont::Base : public FontBase , Inner , public AbstractExtFont
 {
  private:

   void textRun(AbstractSparseString &str,FuncArgType<CharX> func) const
    {
     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [this,&index,func] (Char ch) { func( glyph(index,ch) ); } );
       }
     else
       {
        str.apply( [this,func] (Char ch) { func( glyph(ch) ); } );
       }
    }

   void textRunWhile(AbstractSparseString &str,FuncType<bool,CharX> func) const
    {
     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [this,&index,func] (Char ch) { return func( glyph(index,ch) ); } );
       }
     else
       {
        str.apply( [this,func] (Char ch) { return func( glyph(ch) ); } );
       }
    }

   Coord toBaseline(Point point) const
    {
     if( font_size.skew )
       {
        Coord delta=CoordMulDiv(font_size.skew,point.y,font_size.dy); // (skew/dy)*y

        return point.x+delta;
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

   Coord text_dx(AbstractSparseString &str) const
    {
     Coord ret=0;

     textRun(str, [&] (CharX met)
                      {
                       ret+=met.dx;

                      } );

     return ret;
    }

   ulen skipCount(AbstractSparseString &str,Coord &x) const // return suffix length
    {
     ulen ret=0;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [&] (Char ch)
                       {
                        Coord delta=kerning(index,ch);
                        CharX met=glyph(ch);

                        if( x+met.dx+met.dx1<0 )
                          {
                           x+=delta+met.dx;

                           return true;
                          }
                        else
                          {
                           ret=1;

                           return false;
                          }

                       } );

        ret+=str.getCount();
       }
     else
       {
        str.apply( [&] (Char ch)
                       {
                        CharX met=glyph(ch);

                        if( x+met.dx+met.dx1<0 )
                          {
                           x+=met.dx;

                           return true;
                          }
                        else
                          {
                           ret=1;

                           return false;
                          }

                       } );

        ret+=str.getCount();
       }

     return ret;
    }

   Coord skip(AbstractSparseString &str,Coord x) const
    {
     if( x>=0 )
       {
        return x;
       }

     ulen len=skipCount(str,x);

     str.cutSuffix(len);

     return x;
    }

   Coord skip(AbstractSparseString &str,Coord x,ulen &index) const
    {
     if( x>=0 )
       {
        index=0;

        return x;
       }

     ulen len=skipCount(str,x);

     str.cutSuffix(len,index);

     return x;
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
          Coord tdx=text_dx(str);

          x=skip(str,dx-font_size.dx1-tdx);
         }
        break;

        case AlignX_Center :
         {
          Coord tdx=text_dx(str);

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
          Coord tdx=text_dx(str);

          x=skip(str,dx-font_size.dx1-tdx,index);
         }
        break;

        case AlignX_Center :
         {
          Coord tdx=text_dx(str);

          x=skip(str,(dx-tdx)/2,index);
         }
        break;

        default: index=0; x=place.x;
       }

     return {x,y};
    }

   void text(FrameBuf<DesktopColor> &buf,Point base,AbstractSparseString &str,VColor vc) const
    {
     if( base.y<font_size.by-font_size.dy || base.y>buf.dY()+font_size.by ) return;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [&] (Char ch) { return glyph(buf,base,index,ch,vc); } );
       }
     else
       {
        str.apply( [&] (Char ch) { return glyph(buf,base,ch,vc); } );
       }
    }

   void text(FrameBuf<DesktopColor> &buf,Point base,AbstractSparseString &str,ulen ch_index,PointMap map,CharFunction func) const
    {
     if( base.y<font_size.by-font_size.dy || base.y>buf.dY()+font_size.by ) return;

     if( cfg.use_kerning )
       {
        IndexType index=0;

        str.apply( [&] (Char ch) { return glyph(buf,base,index,ch,ch_index++,map,func); } );
       }
     else
       {
        str.apply( [&] (Char ch) { return glyph(buf,base,ch,ch_index++,map,func); } );
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

   virtual FontClass getFontClass() const
    {
     return GetFontClass(face);
    }

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

     ret.dx=0;

     bool first=true;

     textRun(str, [&] (CharX met)
                      {
                       ret.dx+=met.dx;

                       if( Change(first,false) ) ret.dx0=met.dx0;

                       ret.dx1=met.dx1;

                      } );

     ret.full_dx=ret.dx+font_size.dx0+font_size.dx1;

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

   // AbstractExtFont

    // set params

   virtual void setSize(Coord dx,Coord dy)
    {
     face.setPixelSize(dx,dy);

     updateFontSize();
    }

   virtual void setFixedSize(ulen index)
    {
     face.setFixedSize((FT_Int)index);

     updateFontSize();
    }

   virtual void setConfig(const Config &cfg_)
    {
     cfg=cfg_;

     updateFontSize();

     if( cfg.gamma_order!=gamma_table.getOrder() ) gamma_table.fill(cfg.gamma_order);
    }

    // get props

   virtual StyleFlags getStyleFlags() const
    {
     StyleFlags ret;

     ret.scalable=face.isScalable();
     ret.monospace=face.isMonospace();
     ret.italic=face.isItalic();
     ret.bold=face.isBold();

     return ret;
    }

   virtual Config getConfig() const
    {
     return cfg;
    }

   virtual StrLen getFamily() const
    {
     return face.getFamily();
    }

   virtual StrLen getStyle() const
    {
     return face.getStyle();
    }

   virtual void getSizeList(Function<void (Coord dx,Coord dy)> func) const
    {
     for(auto size : face.getSizeList() ) func(size.width,size.height);
    }
 };

/* class FreeTypeFont */

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

void SetFontSize(const Font &font,Coord dx,Coord dy)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) ptr->setSize(dx,dy);
 }

void SetFixedFontSize(const Font &font,ulen index)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) ptr->setFixedSize(index);
 }

void SetFontConfig(const Font &font,const AbstractExtFont::Config &cfg)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) ptr->setConfig(cfg);
 }

 // get props

AbstractExtFont::StyleFlags GetFontStyleFlags(const Font &font)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) return ptr->getStyleFlags();

  return {};
 }

AbstractExtFont::Config GetFontConfig(const Font &font)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) return ptr->getConfig();

  return {};
 }

StrLen GetFontFamily(const Font &font)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) return ptr->getFamily();

  return "Unknown"_c;
 }

StrLen GetFontStyle(const Font &font)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) return ptr->getStyle();

  return Null;
 }

void GetFontSizeList(const Font &font,Function<void (Coord dx,Coord dy)> func)
 {
  if( auto *ptr=font.castPtr<AbstractExtFont>() ) ptr->getSizeList(func);
 }

/* class ProbeFreeTypeFont::Inner */

class ProbeFreeTypeFont::Inner : public MemBase_nocopy , AutoGlobal<FreeTypeFont::Global>::Lock
 {
   mutable FreeType::Face face;

  public:

   Inner(StrLen file_name,bool &is_font);

   ~Inner();

   FontClass getClass() const;

   StrLen getFamily() const;

   StrLen getStyle() const;

   AbstractExtFont::StyleFlags getStyleFlags() const;
 };

ProbeFreeTypeFont::Inner::Inner(StrLen file_name,bool &is_font)
 : AutoGlobal<FreeTypeFont::Global>::Lock(FreeTypeFont::Inner::Object),
   face(FreeTypeFont::Inner::Object->lib,FreeTypeFont::Inner::Object->mutex,file_name,is_font)
 {
 }

ProbeFreeTypeFont::Inner::~Inner()
 {
 }

FontClass ProbeFreeTypeFont::Inner::getClass() const
 {
  return GetFontClass(face);
 }

StrLen ProbeFreeTypeFont::Inner::getFamily() const
 {
  return face.getFamily();
 }

StrLen ProbeFreeTypeFont::Inner::getStyle() const
 {
  return face.getStyle();
 }

AbstractExtFont::StyleFlags ProbeFreeTypeFont::Inner::getStyleFlags() const
 {
  AbstractExtFont::StyleFlags ret;

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

FontClass ProbeFreeTypeFont::getClass() const
 {
  return ptr->getClass();
 }

StrLen ProbeFreeTypeFont::getFamily() const
 {
  return ptr->getFamily();
 }

StrLen ProbeFreeTypeFont::getStyle() const
 {
  return ptr->getStyle();
 }

AbstractExtFont::StyleFlags ProbeFreeTypeFont::getStyleFlags() const
 {
  return ptr->getStyleFlags();
 }

} // namespace Video
} // namespace CCore

