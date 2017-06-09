/* Forget.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_Forget_h
#define CCore_inc_crypton_Forget_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Crypton {

/* functions */

template <class T>
void PrepareForget(T &obj) noexcept
 {
  obj=T();
 }

template <class T,ulen Len>
void PrepareForget(T (&obj)[Len]) noexcept
 {
  for(ulen i=0; i<Len ;i++) PrepareForget(obj[i]);
 }

template <class T>
void Forget(T &obj) noexcept
 {
  PrepareForget(obj);

  OptimizeBarrier(&obj,sizeof obj);
 }

template <class T>
void ForgetRange(PtrLen<T> data) noexcept
 {
  data.set_null();

  OptimizeBarrier(data.ptr,data.len*sizeof (T));
 }

} // namespace Crypton
} // namespace CCore

#endif


