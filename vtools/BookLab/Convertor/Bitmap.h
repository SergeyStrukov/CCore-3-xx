/* Bitmap.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_Bitmap_h
#define App_Bitmap_h

namespace App {

/* classes */

struct BitmapProc;

/* struct BitmapProc */

struct BitmapProc
 {
  virtual void operator () (const void *buf,int dx,int dy,int dline) =0 ;

  static bool Proc(const wchar_t *file_name,BitmapProc &proc);

  void open(const wchar_t *file_name) { Proc(file_name,*this); }

  void open(const char *file_name,size_t len);
 };

} // namespace App

#endif

