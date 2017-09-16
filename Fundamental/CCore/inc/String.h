/* String.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_String_h
#define CCore_inc_String_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Printf.h>
#include <CCore/inc/Symbol.h>

namespace CCore {

/* classes */

class String;

class PrintString;

struct StrLenCast;

template <unsigned Count> class StringSumBuilder;

/* class String */

class String
 {
   AtomicRefArray<char> data;

  private:

#ifdef CCORE_UTF8

   class CharBuilder;

#endif

   String(void *mem,ulen maxlen,std::initializer_list<char> il) noexcept : data(mem,maxlen,il) {}

    // mem is aligned , maxlen > 0 , il.size() <= maxlen , static object !

  public:

   String() noexcept {}

   String(NothingType) noexcept {}

   String(StrLen str) : data(DoCopy(str.len),str.ptr) {}

#ifdef CCORE_UTF8

   String(PtrLen<const Char> str);

#endif

   String(DoBuildType,BuilderType<char> builder) : data(DoBuild,builder) {}

   ~String() {}

   // methods

   PtrLen<char> modify() { return data.modify(); }

   // range access

   const char * getPtr() const { return data.getPtr(); }

   const char * getPtr_const() const { return data.getPtr(); }

   ulen getLen() const { return data.getLen(); }

   // print object

   using PrintOptType = StrPrintOpt ;

   void print(PrinterType &obj,PrintOptType opt) const
    {
     StrPrint proxy(Range(*this));

     proxy.print(obj,opt);
    }

   // swap/move objects

   void objSwap(String &obj)
    {
     Swap(data,obj.data);
    }

   explicit String(ToMoveCtor<String> obj)
    : data(ToMoveCtor(obj->data))
    {
    }

   // static string

   template <char ... CC> class StaticObject;
 };

/* String::StaticObject<CC> */

template <char ... CC>
class String::StaticObject
 {
   static constexpr ulen Len = Max<ulen>(sizeof ... (CC),1) ;

   Meta::AlignedStorage< AtomicRefArray<char>::StaticMemLen<Len> > storage;
   String str;

  private:

   StaticObject()
    : str(&storage,Len,{CC...})
    {
    }

  public:

   operator const String & () const { return str; }

   static StaticObject Object;
 };

template <char ... CC>
String::StaticObject<CC...> String::StaticObject<CC...>::Object CCORE_INITPRI_3 ;

/* class PrintString */

class PrintString : public PrintBase
 {
   ulen max_len;
   ulen frame_len;

   Collector<char> data;
   PtrLen<char> buf;

  private:

   virtual PtrLen<char> do_provide(ulen hint_len);

   virtual void do_flush(char *ptr,ulen len);

  public:

   static constexpr ulen DefaultFrameLen = 1_KByte ;

   explicit PrintString(ulen max_len=MaxULen,ulen frame_len=DefaultFrameLen);

   ~PrintString() { cleanup(); }

   String close();

   void cleanup();
 };

/* struct StrLenCast */

struct StrLenCast
 {
  template <ConstTypeRangeableType<char> T>
  static StrLen Cast(const T &t) { return Range_const(t); }

  static StrLen Cast(StrLen t) { return t; }

  static StrLen Cast(const char *t) { return t; }
 };

/* concept StrLenCastableType<T> */

template <class T> // ref extended
concept bool StrLenCastableType = requires(Meta::ToConst<T> &obj)
 {
  StrLenCast::Cast(obj);
 } ;

/* class StringSumBuilder<unsigned Count> */

template <unsigned Count>
class StringSumBuilder : StrLenCast
 {
   StrLen list[Count];
   ulen len;

  private:

   ulen countLen() const
    {
     ulen ret=0;

     for(StrLen str : list ) ret=LenAdd(ret,str.len);

     return ret;
    }

  public:

   template <class ... TT>
   explicit StringSumBuilder(const TT & ... tt) requires ( ... && StrLenCastableType<TT> )
    : list{ Cast(tt) ... }
    {
     len=countLen();
    }

   ulen getLen() const { return len; }

   PtrLen<char> operator () (Place<void> place)
    {
     PtrLen<char> ret(place,len);

     PtrLen<char> out=ret;

     for(StrLen str : list ) (out+=str.len).copy(str.ptr);

     return ret;
    }
 };

template <>
class StringSumBuilder<0>
 {
  public:

   StringSumBuilder() {}

   ulen getLen() const { return 0; }

   PtrLen<char> operator () (Place<void> place) { return PtrLen<char>(place,0); }
 };

/* functions */

template <PrintableType ... TT>
String Stringf(const char *format,const TT & ... tt)
 {
  PrintString out;

  Printf(out,format,tt...);

  return out.close();
 }

template <PrintableType ... TT>
String StringCat(const TT & ... tt)
 {
  PrintString out;

  Putobj(out,tt...);

  return out.close();
 }

template <StrLenCastableType ... TT>
String StringSum(const TT & ... tt)
 {
  return String(DoBuild,StringSumBuilder<sizeof ... (TT)>(tt...));
 }

String operator + (const String &a,const StrLenCastableType &t) { return StringSum(a,t); }

} // namespace CCore

#endif


