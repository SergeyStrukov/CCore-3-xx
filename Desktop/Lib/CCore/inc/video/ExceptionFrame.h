/* ExceptionFrame.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_ExceptionFrame_h
#define CCore_inc_video_ExceptionFrame_h

#include <CCore/inc/video/MessageFrame.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* classes */

class ExceptionBuf;

class ExceptionFrame;

/* class ExceptionBuf */

class ExceptionBuf : NoCopy
 {
  public:

   struct Config
    {
     RefVal<DefString> title = "Error"_def ;

     CtorRefVal<MessageFrame::AlertConfigType> frame_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       title.bind(bag.text_Error);

       frame_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   SimpleArray<char> buf;

   PtrLen<char> out;
   bool overflow = false ;

   // frame

   FrameWindow *parent;
   const RefVal<DefString> &title;

  private:

   Info prepare();

  public:

   MessageFrame frame;

   static constexpr ulen DefaultLen = 4_KByte ;

   ExceptionBuf(FrameWindow *parent,const RefVal<DefString> &title,const MessageFrame::ConfigType &cfg,ulen buf_len=DefaultLen);

   ExceptionBuf(FrameWindow *parent,const ConfigType &cfg,ulen buf_len=DefaultLen);

   ~ExceptionBuf();

   void start() { out=Range(buf); overflow=false; }

   void print(StrLen str);

   void show() noexcept;
 };

/* class ExceptionFrame */

class ExceptionFrame : public ReportException
 {
   ExceptionBuf &buf;

  private:

   virtual void print(StrLen str);

  public:

   explicit ExceptionFrame(ExceptionBuf &buf);

   ~ExceptionFrame();
 };

} // namespace Video
} // namespace CCore

#endif

