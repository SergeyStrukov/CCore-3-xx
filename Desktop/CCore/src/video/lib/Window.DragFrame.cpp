/* Window.DragFrame.cpp */
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

//#include <CCore/inc/video/lib/Window.DragFrame.h>

#include <utility>

namespace CCore {
namespace Video {

namespace Bomb {

template <class Func,class R,class ... AA>
concept bool FuncType = requires(Func func,AA && ... aa) { { func( std::forward<AA>(aa)... ) } -> R ; } ;

template <class Func,class T>
T Replace_gen(Func func,T &obj) requires ( FuncType<Func,T,T> ) { T ret(obj); obj=func(ret); return ret; }

class Test
 {
  void method() {}
 };

void test(Test &test)
 {
  test.method();
 }

} // namespace Bomb

} // namespace Video
} // namespace CCore

