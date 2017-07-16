/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Folding
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Tuple.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

template <class ... MM>
struct MemberList
 {
  Tuple<MM...> tuple;

  MemberList(MM ... mm) : tuple(mm...) {}

  template <class T>
  void null(T *obj) const
   {
    tuple.call( [=] (auto ... mm) { ( ... , (obj->*mm=0) ); } );
   }

  template <class T>
  T add(const T &a,const T &b) const
   {
    return tuple.call( [=] (auto ... mm) -> T { return T( (a.*mm+b.*mm)... ); } );
   }
 };

/* struct PointBase<P> */

template <class P>
struct PointBase
 {
  void null()
   {
    P::template Fold<MemberList,P>().null( static_cast<P *>(this) );
   }

  friend P operator + (const P &a,const P &b)
   {
    return P::template Fold<MemberList,P>().add(a,b);
   }
 };

/* struct Point3D */

struct Point3D : PointBase<Point3D>
 {
  int x;
  int y;
  int z;

  Point3D() { null(); }

  Point3D(int x_,int y_,int z_) : x(x_),y(y_),z(z_) {}

  template <template <class ...> class Ret,class T>
  static auto Fold()
   {
    return Ret(&T::x,&T::y,&T::z);
   }
 };

/* Main() */

void Main()
 {
  Point3D point;

  point.null();

  Printf(Con,"( #; , #; , #; )\n",point.x,point.y,point.z);

  Point3D A(1,2,3),B(4,5,6);

  Point3D C=A+B;

  Printf(Con,"( #; , #; , #; )\n",C.x,C.y,C.z);
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

