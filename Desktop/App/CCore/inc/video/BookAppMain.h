/* BookAppMain.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_BookAppMain_h
#define CCore_inc_video_BookAppMain_h

#include <CCore/inc/video/AppMain.h>
#include <CCore/inc/video/BookFrame.h>

namespace CCore {
namespace Video {

/* classes */

template <class AppProp> struct BookAppParam;

template <class AppProp> class BookApplication;

/* struct BookAppParam<AppProp> */

template <class AppProp>
struct BookAppParam
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;

  UserPreference user_pref;
  AppPreference<AppProp> app_pref;
  BookPreference book_pref;

  const WindowReportConfig &report_cfg;
  const ExceptionWindow::ConfigType &exception_cfg;
  const DragFrame::ConfigType &frame_cfg;

  using ClientWindow = typename AppProp::ClientWindow ;

  typename ClientWindow::ConfigType client_cfg;

  BookAppParam() noexcept
   : report_cfg(user_pref.getSmartConfig()),
     exception_cfg(user_pref.getSmartConfig()),
     frame_cfg(user_pref.getSmartConfig()),
     client_cfg(user_pref,app_pref,book_pref)
   {
   }

  void sync()
   {
    user_pref.sync();
    app_pref.sync();
    book_pref.sync();
   }
 };

/* class BookApplication<AppProp> */

template <class AppProp>
class BookApplication : public ApplicationOf<AppProp,BookAppParam<AppProp> >
 {
  protected:

   ConfigEditorFrame book_frame;

  private:

   void bookPref(Point base)
    {
     if( book_frame.isDead() )
       {
        book_frame.create(this->main_frame.getFrame(),base,this->param.user_pref.get().title_BookPref);
       }
    }

   SignalConnector<BookApplication,Point> connector_bookPref;

   void bookUpdated()
    {
     this->param.user_pref.updated.assert();
    }

   void bookSave()
    {
     this->param.book_pref.update();
    }

   SignalConnector<BookApplication> connector_book_updated;
   SignalConnector<BookApplication> connector_book_save;

  public:

   using Opt = typename AppProp::Opt ;

   BookApplication(WindowReportBase &report,BookAppParam<AppProp> &param,CmdDisplay cmd_display,const Opt &opt)
    : ApplicationOf<AppProp,BookAppParam<AppProp> >(report,param,cmd_display,opt),

      book_frame(param.desktop,param.user_pref.getSmartConfig(),false),

      connector_bookPref(this,&BookApplication::bookPref,this->client.doBookPref),

      connector_book_updated(this,&BookApplication::bookUpdated,book_frame.updated),
      connector_book_save(this,&BookApplication::bookSave,book_frame.doSave)
    {
     book_frame.bindConfig(this->param.book_pref);
     book_frame.connectUpdate(this->param.user_pref.updated);
    }
 };

/* BookAppMain() */

template <class AppProp>
int BookAppMain(CmdDisplay cmd_display,int argc,const char *argv[])
 {
  return AppMainOf<AppProp,BookAppParam<AppProp>,BookApplication<AppProp> >(cmd_display,argc,argv);
 }

} // namespace Video
} // namespace CCore

#endif

