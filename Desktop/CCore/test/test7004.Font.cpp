/* test7004.Font.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/test/wintest.h>

#include <CCore/inc/video/CommonDrawArt.h>
#include <CCore/inc/video/FreeTypeFont.h>

namespace App {

namespace Private_7004 {

/* class ClientWindow */

class ClientWindow : public SubWindow
 {
  public:

   struct ConfigType
    {
     RefVal<VColor> back  = Silver ;
     RefVal<VColor> field =  White ;
     RefVal<VColor> text  =  Black ;

     RefVal<Font> font = GetFont() ;

     ConfigType() {}

     static Font GetFont()
      {
       static SystemFontDirs dirs;

       FreeTypeFont font(dirs.getList()[0],"ariali.ttf");

       font.setSize(30);

       return font;
      }
    };

  private:

   const ConfigType &cfg;

   char text[TextBufLen];
   ulen len = 0 ;

   Pane pane[4][4];

   Point base;

  public:

   ClientWindow(SubWindowHost &host,const ConfigType &cfg_)
    : SubWindow(host),
      cfg(cfg_)
    {
    }

   virtual ~ClientWindow()
    {
    }

   // drawing

   virtual void layout()
    {
     Point size=getSize();

     Coord dx=Div(4,21)*size.x;
     Coord dy=Div(4,21)*size.y;

     Coord x0=dx/4;
     Coord y0=dy/4;

     Coord delta_x=dx+x0;
     Coord delta_y=dy+y0;

     if( dx>0 && dy>0 )
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Pane(x0+i*delta_x,y0+j*delta_y,dx,dy);
            }
       }
     else
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Empty;
            }
       }
    }

   virtual void draw(DrawBuf buf,bool drag_active) const
    {
     Used(drag_active);

     CommonDrawArt art(buf);

     art.erase(+cfg.back);

     AlignX align_x[4]={AlignX_Left,AlignX_Center,AlignX_Right,AlignX_Given};
     AlignY align_y[4]={AlignY_Top,AlignY_Center,AlignY_Bottom,AlignY_Given};

     for(int i=0; i<4 ;i++)
       for(int j=0; j<4 ;j++)
         {
          art.block(pane[i][j],+cfg.field);

          TextPlace place(align_x[i],align_y[j]);

          place.x=base.x;
          place.y=base.y;

          cfg.font->text(buf,pane[i][j],place,StrLen(text,len),+cfg.text);
         }
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Char(char ch)
    {
     if( ch=='\b' )
       {
        if( len ) len--;
       }
     else
       {
        if( len<DimOf(text) ) text[len++]=ch;
       }

     redraw();
    }

   void react_LeftClick(Point point,MouseKey)
    {
     base=point-pane[3][3].getBase();

     redraw();
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Left )
       {
        base=point-pane[3][3].getBase();

        redraw();
       }
    }
 };

} // namespace Private_7004

using namespace Private_7004;

/* TestMain() */

template <>
int TestMain<7004>(CmdDisplay cmd_display)
 {
  return ClientApplication<ClientWindow>::Main(cmd_display,"Test7004"_def);
 }

} // namespace App





