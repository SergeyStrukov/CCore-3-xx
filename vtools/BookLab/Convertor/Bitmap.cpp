/* Bitmap.cpp */
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

#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>

using namespace Gdiplus;

#include "Bitmap.h"

namespace App {

/* internal */

class Startup
 {
   GdiplusStartupInput gdiplusStartupInput;

   ULONG_PTR gdiplusToken;

  public:

   Startup()
    {
     GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);
    }

   ~Startup()
    {
     GdiplusShutdown(gdiplusToken);
    }
 };

static Startup StartupObj;

/*  */

void test(const wchar_t *file_name)
 {
  Bitmap *bitmap=Bitmap::FromFile(file_name);

  delete bitmap;
 }

} // namespace App


