/* test6008.X11.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/FrameBuf.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>

namespace App {

namespace Private_6008 {

/* using */

using namespace Video;

/* struct PrintXStatus */

struct PrintXStatus
 {
  Display *display;
  Status status;

  PrintXStatus(Display *display_,Status status_) : display(display_),status(status_) {}

  template <class P>
  void print(P &out) const
   {
    char temp[TextBufLen];

    XGetErrorText(display,status,temp,TextBufLen);

    Putobj(out,temp);
   }
 };

/* class WindowBuf */

class WindowBuf : NoCopy
 {
   void *mem = 0 ;
   Point size;
   XImage image;

  public:

   WindowBuf()
    {
    }

   ~WindowBuf()
    {
     if( mem )
       {
        MemFree(mem);
       }
    }

   Point getSize() const { return size; }

   void * getMem() const { return mem; }

   ColorPlane getPlane() const { return ColorPlane(mem,size.x,size.y,size.x*4u); }

   void setSize(Point new_size)
    {
     // destroy

     if( mem )
       {
        MemFree(mem);

        mem=0;
        size=Null;
       }

     // create

     mem=MemAlloc(ulen(new_size.y)*ulen(new_size.x)*4u);

     image.width=new_size.x;
     image.height=new_size.y;

     image.xoffset=0;
     image.format=ZPixmap;
     image.data=(char *)mem;

     image.byte_order=LSBFirst; // ?
     image.bitmap_unit=32;
     image.bitmap_bit_order=LSBFirst; // ?

     image.bitmap_pad=32;
     image.depth=24;
     image.bytes_per_line=ulen(new_size.x)*4u;
     image.bits_per_pixel=32;

     image.red_mask=0xFF0000;
     image.green_mask=0xFF00;
     image.blue_mask=0xFF;

     if( XInitImage(&image) )
       {
        size=new_size;
       }
     else
       {
        MemFree(mem);

        mem=0;

        Printf(Exception,"setSize() : image init");
       }
    }

   void draw(Display *display,Window window,GC gc,Pane pane)
    {
     if( !mem ) return;

     pane=Inf(pane,Pane(Null,size));

     if( !pane ) return;

     XPutImage(display,window,gc,&image,pane.x,pane.y,pane.x,pane.y,pane.dx,pane.dy);
    }
 };

/* class TestWindow */

class TestWindow : NoCopy
 {
   Display *display;
   int screen;

   GC gc;

   Window window;

   bool run_flag = false ;

   enum State
    {
     State_Normal,
     State_Moving,
     State_Sizeing
    };

   State state = State_Normal ;
   int base_x;
   int base_y;
   int origin_x;
   int origin_y;

   WindowBuf buf;

  private:

   // move

   void replace(int dx,int dy)
    {
     XMoveWindow(display,window,origin_x+dx,origin_y+dy);
    }

   void startMove(int x,int y)
    {
     if( state==State_Normal )
       {
        state=State_Moving;
        base_x=x;
        base_y=y;

        XWindowAttributes attr;

        XGetWindowAttributes(display,window,&attr);

        origin_x=attr.x;
        origin_y=attr.y;
       }
    }

   void nextMove(int x,int y)
    {
     if( state==State_Moving )
       {
        replace(x-base_x,y-base_y);
       }
    }

   void stopMove(int x,int y)
    {
     if( state==State_Moving )
       {
        state=State_Normal;

        replace(x-base_x,y-base_y);
       }
    }

   void stopMove()
    {
     if( state==State_Moving )
       {
        state=State_Normal;
       }
    }

   void prepare(FrameBuf<RawColor32> buf)
    {
     buf.test();
    }

  private:

   static int ErrorHandler(Display *display,XErrorEvent *err)
    {
     Printf(Con,"X11Fault> #;\n",PrintXStatus(display,err->error_code));

     return 0;
    }

   static int IOErrorHandler(Display *)
    {
     Printf(Con,"X11IOFault>\n");

     return 0;
    }

   void destroy()
    {
     XDestroyWindow(display,window);
    }

   void handle(XEvent &event)
    {
     switch( event.type )
       {
        // user input

        case KeyPress :
         {
          Printf(Con,"-> KeyPress\n");
         }
        break;

        case KeyRelease :
         {
          Printf(Con,"-> KeyRelease\n");
         }
        break;

        case ButtonPress :
         {
          XButtonEvent &data=event.xbutton;

          Printf(Con,"-> ButtonPress #; #; #; #.h;\n",data.x_root,data.y_root,data.button,data.state);

          XSetInputFocus(display,window,RevertToPointerRoot,CurrentTime);

          if( data.button==Button3 ) destroy();

          // move

          if( data.button==Button1 )
            {
             startMove(data.x_root,data.y_root);
            }
         }
        break;

        case ButtonRelease :
         {
          XButtonEvent &data=event.xbutton;

          Printf(Con,"-> ButtonRelease #; #; #; #;\n",data.x_root,data.y_root,data.button,data.state);

          if( data.button==Button1 )
            {
             stopMove(data.x_root,data.y_root);
            }
         }
        break;

        case MotionNotify :
         {
          XMotionEvent &data=event.xmotion;

          Used(data);

          //Printf(Con,"-> MotionNotify #; #; #;\n",data.x_root,data.y_root,data.state);

          if( data.state&Button1Mask )
            {
             nextMove(data.x_root,data.y_root);
            }
         }
        break;

        case EnterNotify :
         {
          Printf(Con,"-> EnterNotify\n");
         }
        break;

        case LeaveNotify :
         {
          XLeaveWindowEvent &data=event.xcrossing;

          Printf(Con,"-> LeaveNotify #;\n",data.mode);

          stopMove();
         }
        break;

        case FocusIn :
         {
          Printf(Con,"-> FocusIn\n");
         }
        break;

        case FocusOut :
         {
          Printf(Con,"-> FocusOut\n");
         }
        break;

        // draw

        case Expose :
         {
          XExposeEvent &data=event.xexpose;

          Pane pane{(Coord)data.x,(Coord)data.y,(Coord)data.width,(Coord)data.height};

          Printf(Con,"-> Expose #;\n",pane);

          buf.draw(display,window,gc,pane);
         }
        break;

        // state change

        case MapNotify :
         {
          Printf(Con,"-> MapNotify\n");
         }
        break;

        case UnmapNotify :
         {
          Printf(Con,"-> UnmapNotify\n");
         }
        break;

        case CreateNotify :
         {
          Printf(Con,"-> CreateNotify\n");
         }
        break;

        case DestroyNotify :
         {
          Printf(Con,"-> DestroyNotify\n");

          run_flag=false;
         }
        break;

        case PropertyNotify :
         {
          Printf(Con,"-> PropertyNotify\n");
         }

        case ReparentNotify :
         {
          Printf(Con,"-> ReparentNotify\n");
         }
        break;

        case ConfigureNotify :
         {
          XConfigureEvent &data=event.xconfigure;

          Printf(Con,"-> ConfigureNotify #; #; #; #;\n",data.x,data.y,data.width,data.height);
         }
        break;

        case VisibilityNotify :
         {
          Printf(Con,"-> VisibilityNotify\n");
         }
        break;

        default:
         {
          Printf(Con,"-> Event #;\n",event.type);
         }
       }
    }

  public:

   TestWindow()
    {
     display=XOpenDisplay(0);

     if( !display )
       {
        Printf(Exception,"no display");
       }

     XSetErrorHandler(ErrorHandler);
     XSetIOErrorHandler(IOErrorHandler);

     screen=DefaultScreen(display);
    }

   ~TestWindow()
    {
     XCloseDisplay(display);
    }

   void prop()
    {
     Window root=RootWindow(display,screen);

     Atom atom=XInternAtom(display,"_NET_WORKAREA",True);

     if( atom==None )
       {
        Printf(Con,"no atom\n");

        return;
       }

     long off=0;
     long len=4;

     Atom atom_type;

     int format;

     unsigned long ret_len;
     unsigned long rest_len;
     unsigned char *data;

     XGetWindowProperty(display,root,atom,off,len,False,AnyPropertyType,&atom_type,&format,&ret_len,&rest_len,&data);

     if( format )
       {
        Printf(Con,"format = #; len = #; rest = #;\n",format,ret_len,rest_len);

        if( format==32 && ret_len==4 && rest_len==0 )
          {
           unsigned long *data32=(unsigned long *)data;

           Printf(Con,"#; #; #; #;\n",data32[0],data32[1],data32[2],data32[3]);
          }

        XFree(data);
       }
     else
       {
        Printf(Con,"no prop\n");
       }
    }

   void create()
    {
     Window root=RootWindow(display,screen);

     XSetWindowAttributes attr{};

     attr.event_mask=ExposureMask|
                     FocusChangeMask|
                     StructureNotifyMask|

                     KeyPressMask|
                     KeyReleaseMask|
                     ButtonPressMask|
                     ButtonReleaseMask|
                     PointerMotionMask|

                     LeaveWindowMask

                     ;

     attr.background_pixel=BlackPixel(display,screen);

     attr.cursor=XCreateFontCursor(display,XC_crosshair);

     attr.override_redirect=True;

     buf.setSize({300,150});

     prepare(buf.getPlane());

     window=XCreateWindow(display,root,200,100,300,150,0,CopyFromParent,InputOutput,CopyFromParent,CWEventMask|CWCursor|CWBackPixel|CWOverrideRedirect,&attr);

     if( window==None )
       {
        Printf(Exception,"no window");
       }

     XGCValues gcv;

     gc=XCreateGC(display,window,0,&gcv);

     if( gc==None )
       {
        XDestroyWindow(display,window);

        Printf(Exception,"no GC");
       }

     XMapWindow(display,window);
    }

   void loop()
    {
     for(run_flag=true; run_flag ;)
       {
        XEvent event;

        XNextEvent(display,&event);

        if( event.xany.window==window ) handle(event);
       }
    }
 };

} // namespace Private_6008

using namespace Private_6008;

/* Testit<6008> */

template<>
const char *const Testit<6008>::Name="Test6008 X11";

template<>
bool Testit<6008>::Main()
 {
  TestWindow test;

  test.prop();

  test.create();

  test.loop();

  return true;
 }

} // namespace App

