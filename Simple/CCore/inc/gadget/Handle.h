/* Handle.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_Handle_h
#define CCore_inc_gadget_Handle_h

namespace CCore {

/* classes */

union Handle;

/* union Handle */

union Handle
 {
  using FuncPtr = void (*)() ;

  int sid;
  unsigned uid;
  void *ptr;
  FuncPtr func_ptr;

  // constructors

  Handle() noexcept {}

  Handle(int sid_) { sid=sid_; }

  Handle(unsigned uid_) { uid=uid_; }

  Handle(void *ptr_) { ptr=ptr_; }

  Handle(FuncPtr func_ptr_) { func_ptr=func_ptr_; }
 };

} // namespace CCore

#endif


