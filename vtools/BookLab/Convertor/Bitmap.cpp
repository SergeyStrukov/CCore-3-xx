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

namespace GdiplusPrivate {

/* classes */

struct NoCopyType;

class Startup;

class BitMap;

class ZStr;

class WStr;

/* struct NoCopyType */

struct NoCopyType
 {
  NoCopyType() = default ;

  NoCopyType(const NoCopyType &) = delete ;

  NoCopyType & operator = (const NoCopyType &) = delete ;
 };

/* type NoCopy */

using NoCopy = NoCopyType ;

/* class Startup */

class Startup : NoCopy
 {
   GdiplusStartupInput gdiplusStartupInput;

   ULONG_PTR gdiplusToken;

  private:

   static Startup Object;

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

Startup Startup::Object;

/* class BitMap */

class BitMap : NoCopy
 {
   Bitmap *bitmap;

  public:

   explicit BitMap(const wchar_t *file_name)
    {
     bitmap=Bitmap::FromFile(file_name);
    }

   ~BitMap()
    {
     delete bitmap;
    }

   bool operator ! () const { return !bitmap; }

   class Bits : NoCopy
    {
      Bitmap *bitmap;
      BitmapData data;
      Status status;

     public:

      explicit Bits(const BitMap &bmp)
       : bitmap(bmp.bitmap)
       {
        if( !bitmap )
          {
           status=InvalidParameter;

           return;
          }

        auto dx=bitmap->GetWidth();
        auto dy=bitmap->GetHeight();

        Rect rect{0,0,(INT)dx,(INT)dy};

        status=bitmap->LockBits(&rect,ImageLockModeRead,PixelFormat32bppARGB,&data);
       }

      ~Bits()
       {
        if( status==Ok ) bitmap->UnlockBits(&data);
       }

      bool operator ! () const { return status!=Ok; }

      void apply(BitmapProc &proc)
       {
        if( !*this ) return;

        void *buf=data.Scan0;

        int dx=data.Width;
        int dy=data.Height;
        int dline=data.Stride;

        proc(buf,dx,dy,dline);
       }
    };
 };

/* class ZStr */

class ZStr : NoCopy
 {
   char *str;

  public:

   ZStr(const char *text,size_t len)
    {
     str=new char[len+1];

     memcpy(str,text,len);

     str[len]=0;
    }

   ~ZStr()
    {
     delete str;
    }

   operator const char * () const { return str; }
 };

/* class WStr */

class WStr : NoCopy
 {
   wchar_t *wstr;

  public:

   explicit WStr(const char *str)
    {
     size_t len=mbstowcs(0,str,0);

     wstr=new wchar_t[len+1];

     mbstowcs(wstr,str,len+1);
    }

   ~WStr()
    {
     delete wstr;
    }

   operator const wchar_t * () const { return wstr; }
 };

} // namespace GdiplusPrivate

/* struct BitmapProc */

using namespace GdiplusPrivate;

bool BitmapProc::Proc(const wchar_t *file_name,BitmapProc &proc)
 {
  BitMap bmp(file_name);

  if( !bmp ) return false;

  BitMap::Bits lock(bmp);

  if( !lock ) return false;

  lock.apply(proc);

  return true;
 }

void BitmapProc::open(const char *file_name,size_t len)
 {
  ZStr zstr(file_name,len);
  WStr wstr(zstr);

  open(wstr);
 }

} // namespace App


