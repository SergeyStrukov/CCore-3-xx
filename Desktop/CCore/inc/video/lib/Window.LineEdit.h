/* Window.LineEdit.h */
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

#ifndef CCore_inc_video_lib_Window_LineEdit_h
#define CCore_inc_video_lib_Window_LineEdit_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.LineEdit.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Video {

/* functions */

void InsChar(char *base,ulen total,ulen pos,char ch);

ulen DelCharRange(char *base,ulen total,ulen off,ulen len);

void RotateCharRange(char *base,ulen total,ulen pos,ulen len);

/* classes */

template <class Shape> class LineEditWindowOf;

/* class LineEditWindowOf<Shape> */

template <class Shape>
class LineEditWindowOf : public SubWindow
 {
   SimpleArray<char> storage;

   DeferTick defer_tick;

  protected:

   Shape shape;

   DeferInput<LineEditWindowOf<Shape> > input;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoffMax)) ) redraw();
    }

   void addXOff(Coordinate count)
    {
     Coordinate xoff=shape.xoff+count*shape.dxoff;

     setXOff(+xoff);
    }

   void startDrag(Point point)
    {
     if( Change(shape.drag,true) )
       {
        shape.drag_base=point;
        shape.xoff_base=shape.xoff;

        captureMouse();
       }
    }

   void dragTo(Point point)
    {
     Coordinate xoff=shape.xoff_base-(Coordinate(point.x)-shape.drag_base.x);

     setXOff(+xoff);
    }

   void endDrag()
    {
     shape.drag=false;

     releaseMouse();
    }

   void endDrag(Point point)
    {
     endDrag();

     dragTo(point);
    }

   void select(ulen pos1,ulen pos2)
    {
     if( pos1<pos2 )
       {
        shape.select_off=pos1;
        shape.select_len=pos2-pos1;
       }
     else
       {
        shape.select_off=pos2;
        shape.select_len=pos1-pos2;
       }
    }

   void select(ulen new_pos)
    {
     if( shape.select_len )
       {
        ulen epos=shape.select_off+shape.select_len;

        if( shape.pos==shape.select_off )
          {
           select(epos,new_pos);
          }
        else if( shape.pos==epos )
          {
           select(shape.select_off,new_pos);
          }
        else
          {
           shape.select_off=0;
           shape.select_len=0;
          }
       }
     else
       {
        select(shape.pos,new_pos);
       }
    }

   void posCursor(Point point)
    {
     ulen new_pos=Min(shape.getPosition(point),shape.len);

     if( shape.mouse_pos )
       {
        select(new_pos);
       }
     else
       {
        shape.mouse_pos=true;

        shape.select_off=0;
        shape.select_len=0;
       }

     shape.pos=new_pos;

     redraw();
    }

   void posCursorEnd()
    {
     shape.mouse_pos=false;
    }

   void posCursorEnd(Point point)
    {
     posCursor(point);

     posCursorEnd();
    }

   void cursorPos(bool shift,ulen new_pos)
    {
     if( shape.pos!=new_pos )
       {
        if( shift )
          {
           select(new_pos);
          }
        else
          {
           shape.select_off=0;
           shape.select_len=0;
          }

        shape.pos=new_pos;
       }
    }

   void keyLeft(bool shift,unsigned repeat=1)
    {
     if( !shape.pos )
       {
        shape.xoff=0;

        redraw();

        return;
       }

     CapDown(repeat,shape.pos);

     if( repeat )
       {
        cursorPos(shift,shape.pos-repeat);

        shape.cursor=true;

        shape.showCursor();

        redraw();
       }
    }

   void keyRight(bool shift,unsigned repeat=1)
    {
     if( shape.pos==shape.len )
       {
        shape.xoff=shape.xoffMax;

        redraw();

        return;
       }

     CapDown(repeat,shape.len-shape.pos);

     if( repeat )
       {
        cursorPos(shift,shape.pos+repeat);

        shape.cursor=true;

        shape.showCursor();

        redraw();
       }
    }

   void keyHome(bool shift)
    {
     cursorPos(shift,0);

     shape.cursor=true;

     shape.xoff=0;

     redraw();
    }

   void keyEnd(bool shift)
    {
     cursorPos(shift,shape.len);

     shape.cursor=true;

     shape.xoff=shape.xoffMax;

     redraw();
    }

   void insChar(char ch)
    {
     if( shape.len<shape.text_buf.len )
       {
        InsChar(shape.text_buf.ptr,shape.len,shape.pos,ch);

        shape.len++;
        shape.pos++;
       }
    }

   void delRange(ulen off,ulen len)
    {
     shape.len-=DelCharRange(shape.text_buf.ptr,shape.len,off,len);
    }

   void delSelectedRange()
    {
     if( !shape.select_len ) return;

     delRange(shape.select_off,shape.select_len);

     shape.pos=shape.select_off;
     shape.select_off=0;
     shape.select_len=0;
    }

   void finishChange()
    {
     shape.cursor=true;

     shape.setMax();

     Replace_min(shape.xoff,shape.xoffMax);

     shape.showCursor();

     redraw();

     changed.assert();
    }

   void delChar(unsigned repeat=1)
    {
     delRange(shape.pos,repeat);

     finishChange();
    }

   void delSelection()
    {
     delSelectedRange();

     finishChange();
    }

   void copy()
    {
     if( !shape.select_len ) return;

     getFrameHost()->textToClipboard(Range(shape.text_buf.ptr+shape.select_off,shape.select_len));
    }

   void cut()
    {
     copy();

     delSelection();
    }

   void past()
    {
     delSelectedRange();

     char *base=shape.text_buf.ptr;

     CopyFunction func(base+shape.len,shape.text_buf.len-shape.len);

     getFrameHost()->textFromClipboard(func.function_copy());

     func.cutEOL();

     ulen len=func.buf.len;

     RotateCharRange(base,shape.len,shape.pos,len);

     shape.len+=len;
     shape.pos+=len;

     finishChange();
    }

   void keyOther(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Home :
         {
          keyHome(kmod&KeyMod_Shift);
         }
        break;

        case VKey_End :
         {
          keyEnd(kmod&KeyMod_Shift);
         }
        break;

        case VKey_c :
         {
          if( kmod&KeyMod_Ctrl ) copy();
         }
        break;

        case VKey_v :
         {
          if( kmod&KeyMod_Ctrl ) past();
         }
        break;

        case VKey_Insert :
         {
          if( kmod&KeyMod_Ctrl )
            copy();
          else if( kmod&KeyMod_Shift )
            past();
         }
        break;

        case VKey_Enter :
         {
          entered.assert();
         }
        break;
       }
    }

   void tick()
    {
     if( shape.tick()  )
       {
        shape.cursor=!shape.cursor;

        redraw();
       }
    }

   void tickStart()
    {
     shape.cursor=true;

     defer_tick.start();
    }

   void tickStop()
    {
     shape.cursor=false;

     defer_tick.stop();
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   static const ulen DefBufLen = 1_KByte ;

   template <class ... TT>
   LineEditWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      storage(DefBufLen),
      shape(Range(storage), std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&LineEditWindowOf<Shape>::tick);
    }

   template <class ... TT>
   LineEditWindowOf(SubWindowHost &host,ulen buf_len,TT && ... tt)
    : SubWindow(host),
      storage(buf_len),
      shape(Range(storage), std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&LineEditWindowOf<Shape>::tick);
    }

   virtual ~LineEditWindowOf()
    {
    }

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   Point getMinSize(StrLen sample_text) const { return shape.getMinSize(sample_text); }

   bool isEnabled() const { return shape.enable; }

   bool isAlerted() const { return shape.alert; }

   void enable(bool enable=true)
    {
     if( enable )
       {
        if( Change(shape.enable,true) )
          {
           if( shape.focus ) tickStart();

           redraw();
          }
       }
     else
       {
        if( Change(shape.enable,false) )
          {
           if( shape.focus ) tickStop();

           redraw();
          }
       }
    }

   void disable() { enable(false); }

   void hideInactiveCursor(bool flag=true)
    {
     if( Change(shape.hide_cursor,flag) ) redraw();
    }

   void alert(bool on=true)
    {
     if( Change(shape.alert,on) ) redraw();
    }

   StrLen getText() const { return Range(shape.text_buf.ptr,shape.len); }

   PtrLen<char> getBuf() { return shape.text_buf; }

   void setTextLen(ulen len)
    {
     shape.cursor=false;

     if( shape.drag ) endDrag();

     shape.len=Min(len,shape.text_buf.len);
     shape.xoff=0;
     shape.pos=0;
     shape.select_off=0;
     shape.select_len=0;

     shape.setMax();

     redraw();
    }

   bool setText(StrLen text) // false on truncation
    {
     bool ret=true;

     auto out=getBuf();

     if( text.len>out.len )
       {
        text.len=out.len;
        ret=false;
       }

     text.copyTo(out.ptr);

     setTextLen(text.len);

     return ret;
    }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     PrintBuf out(getBuf());

     Printf(out,format,tt...);

     out.guardOverflow();

     setTextLen( out.close().len );
    }

   bool insText(const char *ptr,ulen len) // false on truncation
    {
     delSelectedRange();

     ulen free=shape.text_buf.len-shape.len;
     bool ret=true;

     if( len>free )
       {
        len=free;
        ret=false;
       }

     char *base=shape.text_buf.ptr;

     Range(ptr,len).copyTo(base+shape.len);

     RotateCharRange(base,shape.len,shape.pos,len);

     shape.len+=len;
     shape.pos+=len;

     shape.cursor=true;

     shape.setMax();

     Replace_min(shape.xoff,shape.xoffMax);

     shape.showCursor();

     redraw();

     return ret;
    }

   bool insText(StrLen str) // false on truncation
    {
     return insText(str.ptr,str.len);
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());

     shape.setMax();
    }

   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base

   virtual void open()
    {
     shape.focus=false;
     shape.cursor=false;
     shape.drag=false;
     shape.mouse_pos=false;

     shape.xoff=0;
     shape.pos=0;
     shape.select_off=0;
     shape.select_len=0;
    }

   virtual void close()
    {
     defer_tick.stop();
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return shape.enable?FocusOk:NoFocus;
    }

   virtual void gainFocus()
    {
     if( Change(shape.focus,true) )
       {
        if( shape.enable ) tickStart();

        redraw();
       }
    }

   virtual void looseFocus()
    {
     if( Change(shape.focus,false) )
       {
        if( shape.enable ) tickStop();

        redraw();
       }
    }

   // mouse

   virtual void looseCapture()
    {
     shape.drag=false;
    }

   virtual MouseShape getMouseShape(Point,KeyMod kmod) const
    {
     if( !shape.enable ) return Mouse_Arrow;

     if( ( shape.xoffMax>0 || shape.xoff>0 ) && (kmod&KeyMod_Ctrl) ) return Mouse_SizeLeftRight;

     return Mouse_IBeem;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     if( shape.enable )
       {
        switch( vkey )
          {
           case VKey_Left :
            {
             if( kmod&KeyMod_Ctrl )
               {
                addXOff(-1);
               }
             else
               {
                keyLeft(kmod&KeyMod_Shift);
               }
            }
           break;

           case VKey_Right :
            {
             if( kmod&KeyMod_Ctrl )
               {
                addXOff(+1);
               }
             else
               {
                keyRight(kmod&KeyMod_Shift);
               }
            }
           break;

           case VKey_Delete :
            {
             if( shape.select_len )
               {
                if( kmod&KeyMod_Shift )
                  cut();
                else
                  delSelection();
               }
             else
               {
                if( !(kmod&KeyMod_Shift) )
                  {
                   if( shape.pos<shape.len )
                     {
                      delChar();
                     }
                  }
               }
            }
           break;

           case VKey_BackSpace :
            {
             if( shape.select_len )
               {
                delSelection();
               }
             else
               {
                if( shape.pos )
                  {
                   shape.pos--;

                   delChar();
                  }
               }
            }
           break;

           default:
            {
             keyOther(vkey,kmod);
            }
          }
       }
     else
       {
        switch( vkey )
          {
           case VKey_Left :
            {
             if( kmod&KeyMod_Ctrl ) addXOff(-1);
            }
           break;

           case VKey_Right :
            {
             if( kmod&KeyMod_Ctrl ) addXOff(+1);
            }
           break;
          }
       }
    }

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( shape.enable )
       {
        switch( vkey )
          {
           case VKey_Left :
            {
             if( kmod&KeyMod_Ctrl )
               {
                addXOff(-CountToCoordinate(repeat));
               }
             else
               {
                keyLeft(kmod&KeyMod_Shift,repeat);
               }
            }
           break;

           case VKey_Right :
            {
             if( kmod&KeyMod_Ctrl )
               {
                addXOff(CountToCoordinate(repeat));
               }
             else
               {
                keyRight(kmod&KeyMod_Shift,repeat);
               }
            }
           break;

           case VKey_Delete :
            {
             if( shape.select_len )
               {
                if( kmod&KeyMod_Shift )
                  cut();
                else
                  delSelection();
               }
             else
               {
                if( !(kmod&KeyMod_Shift) )
                  {
                   if( shape.pos<shape.len )
                     {
                      delChar(repeat);
                     }
                  }
               }
            }
           break;

           case VKey_BackSpace :
            {
             if( shape.select_len )
               {
                delSelection();
               }
             else
               {
                CapDown(repeat,shape.pos);

                if( repeat )
                  {
                   shape.pos-=repeat;

                   delChar(repeat);
                  }
               }
            }
           break;

           default:
            {
             keyOther(vkey,kmod);
            }
          }
       }
     else
       {
        switch( vkey )
          {
           case VKey_Left :
            {
             if( kmod&KeyMod_Ctrl ) addXOff(-CountToCoordinate(repeat));
            }
           break;

           case VKey_Right :
            {
             if( kmod&KeyMod_Ctrl ) addXOff(CountToCoordinate(repeat));
            }
           break;
          }
       }
    }

   void react_Char(char ch)
    {
     if( shape.enable && CharIsPrintable(ch) )
       {
        delSelectedRange();

        insChar(ch);

        finishChange();
       }
    }

   void react_LeftClick(Point point,MouseKey mkey)
    {
     if( !shape.enable ) return;

     if( mkey&MouseKey_Ctrl )
       {
        startDrag(point);
       }
     else
       {
        posCursor(point);
       }
    }

   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.drag )
       {
        endDrag(point);
       }
     else
       {
        if( shape.enable ) posCursorEnd(point); else posCursorEnd();
       }
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.drag )
       {
        if( mkey&MouseKey_Left )
          {
           dragTo(point);
          }
        else
          {
           endDrag();
          }
       }
     else if( mkey&MouseKey_Left )
       {
        if( shape.enable ) posCursor(point); else posCursorEnd();
       }
     else
       {
        posCursorEnd();
       }
    }

   void react_Leave()
    {
     posCursorEnd();
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta)
    {
     if( mkey&MouseKey_Ctrl )
       {
        addXOff(delta);
       }
     else if( shape.enable )
       {
        if( delta<0 )
          {
           keyLeft(mkey&MouseKey_Shift,IntAbs(delta));
          }
        else
          {
           keyRight(mkey&MouseKey_Shift,IntAbs(delta));
          }
       }
    }

   // signals

   Signal<> entered;
   Signal<> changed;
 };

/* type LineEditWindow */

using LineEditWindow = LineEditWindowOf<LineEditShape> ;

} // namespace Video
} // namespace CCore

#endif

