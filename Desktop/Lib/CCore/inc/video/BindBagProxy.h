/* BindBagProxy.h */
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

#ifndef CCore_inc_video_BindBagProxy_h
#define CCore_inc_video_BindBagProxy_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* BindBagProxy() */

template <class Cfg,class Bag,class Proxy>
auto BindBagProxy(Cfg &cfg,const Bag &bag,Proxy proxy) -> decltype( cfg.bind(bag,proxy) )
 {
  cfg.bind(bag,proxy);
 }

template <class Cfg,class Bag,class Proxy>
auto BindBagProxy(Cfg &cfg,const Bag &bag,Proxy proxy) -> decltype( cfg.bind(bag) )
 {
  Used(proxy);

  cfg.bind(bag);
 }

} // namespace Video
} // namespace CCore

#endif

