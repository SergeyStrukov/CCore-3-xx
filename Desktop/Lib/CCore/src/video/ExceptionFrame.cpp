/* ExceptionFrame.cpp */
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

#include <CCore/inc/video/ExceptionFrame.h>

#include <CCore/inc/FeedBuf.h>
#include <CCore/inc/Symbol.h>

namespace CCore {
namespace Video {

/* class ExceptionBuf */

Info ExceptionBuf::prepare()
 {
  StrLen text=Range(buf);

  text.len-=out.len;

  if( overflow ) text=TrimText(text);

  InfoBuilder builder;

  while( +text )
    {
     StrLen line=CutLine(text);

     if( +line || +text ) builder.add(line);
    }

  if( overflow ) builder.add("..."_c);

  return builder.complete();
 }

ExceptionBuf::ExceptionBuf(FrameWindow *parent_,const RefVal<String> &title_,const MessageFrame::ConfigType &cfg,ulen buf_len)
 : buf(buf_len),
   parent(parent_),
   title(title_),
   frame(parent_->getDesktop(),cfg)
 {
 }

ExceptionBuf::ExceptionBuf(FrameWindow *parent,const ConfigType &cfg,ulen buf_len)
 : ExceptionBuf(parent,cfg.title,cfg.frame_cfg.get(),buf_len)
 {
 }

ExceptionBuf::~ExceptionBuf()
 {
 }

void ExceptionBuf::print(StrLen str)
 {
  overflow = Feedup(out,str) || overflow ;
 }

void ExceptionBuf::show() noexcept
 {
  SilentReportException report;

  try
    {
     if( frame.isAlive() ) frame.destroy();

     frame.setInfo(prepare());

     frame.create(parent,+title);
    }
  catch(...)
    {
    }
 }

/* class ExceptionFrame */

void ExceptionFrame::print(StrLen str)
 {
  buf.print(str);
 }

ExceptionFrame::ExceptionFrame(ExceptionBuf &buf_)
 : buf(buf_)
 {
  buf.start();
 }

ExceptionFrame::~ExceptionFrame()
 {
  if( !(*this) ) buf.show();
 }

} // namespace Video
} // namespace CCore

