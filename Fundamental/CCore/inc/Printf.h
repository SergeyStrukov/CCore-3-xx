/* Printf.h */
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

#ifndef CCore_inc_Printf_h
#define CCore_inc_Printf_h

#include <CCore/inc/printf/PrintProxy.h>
#include <CCore/inc/printf/PrintBase.h>
#include <CCore/inc/DetectProxy.h>
#include <CCore/inc/Tuple.h>

namespace CCore {

/* GetTextDesc() */

inline StrLen GetTextDesc(bool value) { return value?"true"_c:"false"_c; }

inline int GetTextDesc(int value) { return value; }

inline unsigned GetTextDesc(unsigned value) { return value; }

inline long GetTextDesc(long value) { return value; }

inline unsigned long GetTextDesc(unsigned long value) { return value; }

inline long long GetTextDesc(long long value) { return value; }

inline unsigned long long GetTextDesc(unsigned long long value) { return value; }

/* classes */

template <class T> struct PrintOptAdapter;

template <class T> struct PrintAdapter;

struct PrintfDevBase;

template <class P> class PrintfDev;

template <class P> class PutobjDev;

template <class OptType,class T> struct BindOpt;

/* struct PrintOptAdapter<T> */

template <class T>
using TextDescType = Meta::UnConst<Meta::UnRef<decltype( GetTextDesc( Meta::TypeBox<const T &>::Get() ) )> >;

template <class T> requires ( No_ProxyType<PrintProxy<T> > )
struct PrintOptAdapter<T> : PrintOptAdapter< TextDescType<T> >
 {
 };

template <class T> requires ( Has_ProxyType<PrintProxy<T> > && No_OptType<PrintProxy<T> > )
struct PrintOptAdapter<T>
 {
  // empty
 };

template <class T> requires ( Has_ProxyType<PrintProxy<T> > && Has_OptType<PrintProxy<T> > )
struct PrintOptAdapter<T>
 {
  using PrintOptType = typename PrintProxy<T>::OptType ;
 };

/* concept ProxyPrintType<Proxy> */

template <class Proxy>
concept bool ProxyPrintType = requires(PrintBase &out,Proxy &obj)
 {
  obj.print(out);
 } ;

/* concept ProxyOptPrintType<Proxy,Opt> */

template <class Proxy,class Opt>
concept bool ProxyOptPrintType = requires(PrintBase &out,Proxy &obj,Opt &opt)
 {
  obj.print(out,opt);
 } ;

/* struct PrintAdapter<T> */

template <class T> requires ( No_ProxyType<PrintProxy<T> > )
struct PrintAdapter<T>
 {
  template <PrinterType P,class S>
  static void PrintDesc(P &out,const char *ptr,const char *lim,S s)
   {
    PrintAdapter<S>::Print(out,ptr,lim,s);
   }

  template <PrinterType P,class OptType,class S>
  static void PrintDesc(P &out,const OptType &opt,S s)
   {
    PrintAdapter<S>::Print(out,opt,s);
   }

  template <PrinterType P,class S>
  static auto PrintDesc(P &out,S s) -> decltype( PrintAdapter<S>::Print(out,s) )
   {
    PrintAdapter<S>::Print(out,s);
   }


  static void Print(PrinterType &out,const char *ptr,const char *lim,const T &t)
   {
    PrintDesc(out,ptr,lim,GetTextDesc(t));
   }

  static void Print(PrinterType &out,const AnyType &opt,const T &t)
   {
    PrintDesc(out,opt,GetTextDesc(t));
   }

  static auto Print(PrinterType &out,const T &t) -> decltype( PrintDesc(out,GetTextDesc(t)) )
   {
    PrintDesc(out,GetTextDesc(t));
   }
 };

template <class T> requires ( Has_ProxyType<PrintProxy<T> > && No_OptType<PrintProxy<T> > )
struct PrintAdapter<T>
 {
  using ProxyType = typename PrintProxy<T>::ProxyType ;

  static void Print(PrinterType &out,const char *,const char *,const T &t)
   {
    ProxyType proxy(t);

    proxy.print(out.printRef());
   }

  static void Print(PrinterType &out,const AnyType &,const T &t)
   {
    ProxyType proxy(t);

    proxy.print(out.printRef());
   }

  static void Print(PrinterType &out,const T &t) requires ( ProxyPrintType<ProxyType> )
   {
    ProxyType proxy(t);

    proxy.print(out.printRef());
   }
 };

template <class T> requires ( Has_ProxyType<PrintProxy<T> > && Has_OptType<PrintProxy<T> > )
struct PrintAdapter<T>
 {
  using ProxyType = typename PrintProxy<T>::ProxyType ;

  using OptType = typename PrintProxy<T>::OptType ;

  static void Print(PrinterType &out,const char *ptr,const char *lim,const T &t)
   {
    OptType opt(ptr,lim);
    ProxyType proxy(t);

    proxy.print(out.printRef(),opt);
   }

  static void Print(PrinterType &out,const OptType &opt,const T &t)
   {
    ProxyType proxy(t);

    proxy.print(out.printRef(),opt);
   }

  static void Print(PrinterType &out,const T &t) requires ( ProxyOptPrintType<ProxyType,OptType> )
   {
    OptType opt{};
    ProxyType proxy(t);

    proxy.print(out.printRef(),opt);
   }
 };

/* concept PrintableType<T> */

template <class T>
concept bool PrintableType2 = requires(PrintBase &out,const T &t)
 {
  PrintAdapter<T>::Print(out,t);
 } ;

template <class T>
inline constexpr bool IsPrintableType = PrintableType2<T> ;

template <class ... TT>
inline constexpr bool IsPrintableType<Tuple<TT...> > = ( ... && IsPrintableType< Meta::UnConst<Meta::UnRef<TT> > > ) ;

template <class T>
concept bool PrintableType = IsPrintableType< Meta::UnConst<Meta::UnRef<T> > > ;

/* struct PrintfDevBase */

struct PrintfDevBase : NoCopy
 {
  static constexpr char OpenFormat  = '#' ;
  static constexpr char CloseFormat = ';' ;

  static bool NotFound(char cur,char ch) { return cur && cur!=ch ; }

  static const char * Find(const char *format,char ch);

  struct OptStr
   {
    const char *ptr;
    const char *lim;

    OptStr(NothingType) : ptr(0),lim(0) {}

    OptStr(const char *ptr_,const char *lim_) : ptr(ptr_),lim(lim_) {}

    template <PrinterType P,class T>
    void print(P &out,const T &t) const
     {
      if( !ptr )
        {
         // print nothing
        }
      else
        {
         PrintAdapter<T>::Print(out,ptr,lim,t);
        }
     }
   };
 };

/* class PrintfDev<P> */

template <class P> requires ( PrinterType<Meta::UnRef<P> > )
class PrintfDev<P> : PrintfDevBase
 {
   P out;
   const char *format;

  private:

   OptStr find();

   // expand

   template <class ... TT>
   void expand(const Tuple<TT...> &tuple)
    {
     tuple.call( [this] (const TT & ...tt) { ( (*this) += ... += tt ); } );
    }

   // operator +=

   template <class T>
   PrintfDev<P> & operator += (const T &t)
    {
     find().print(out,t);

     return *this;
    }

   template <class ... TT>
   PrintfDev<P> & operator += (const Tuple<TT...> &tuple)
    {
     expand(tuple);

     return *this;
    }

  public:

   template <class S>
   PrintfDev(S &&out_,const char *format_) : out(out_),format(format_) {}

   ~PrintfDev() noexcept(false) {}

   template <class ... TT>
   void operator () (const TT & ... tt)
    {
     (void)( (*this) += ... += tt );

     while( *format ) find();
    }
 };

template <class P> requires ( PrinterType<Meta::UnRef<P> > )
auto PrintfDev<P>::find() -> OptStr // ^aaaaaa##aaaaaaaaaaaa#opt;
 {
  for(;;)
    {
     const char *ptr=Find(format,OpenFormat);

     out.put(format,Dist(format,ptr));

     if( *ptr )                // ^##aaaaaaaaaaaa#opt;
       {
        ptr++;

        if( *ptr==OpenFormat ) // ^#aaaaaaaaaaaa#opt;
          {
           out.put(OpenFormat);

           format=ptr+1;

           // continue;
          }
        else                   // ^opt;
          {
           const char *lim=Find(ptr,CloseFormat);

           if( *lim )
             {
              format=lim+1;

              return OptStr(ptr,lim);
             }
           else // no ;
             {
              format=ptr;

              return OptStr(ptr,ptr);
             }
          }
       }
     else // ^end-of-str
       {
        format=ptr;

        return Nothing;
       }
    }
 }

/* class PrintfDev<void> */

template <>
class PrintfDev<void>
 {
  public:

   template <class S>
   PrintfDev(S &&,const char *) {}

   template <class ... TT>
   void operator () (const TT & ...) {}
 };

/* class PutobjDev<P> */

template <class P> requires ( PrinterType<Meta::UnRef<P> > )
class PutobjDev<P> : NoCopy
 {
   P out;

  private:

   // expand

   template <class ... TT>
   void expand(const Tuple<TT...> &tuple)
    {
     tuple.call( [this] (const TT & ...tt) { ( (*this) += ... += tt ); } );
    }

   // operator +=

   template <class T>
   PutobjDev<P> & operator += (const T &t)
    {
     PrintAdapter<T>::Print(out,t);

     return *this;
    }

   template <class ... TT>
   PutobjDev<P> & operator += (const Tuple<TT...> &tuple)
    {
     expand(tuple);

     return *this;
    }

   // operator <<

   PutobjDev<P> & operator << (char ch)
    {
     out.put(ch);

     return *this;
    }

  public:

   template <class S>
   explicit PutobjDev(S &&out_) : out(out_) {}

   ~PutobjDev() noexcept(false) {}

   template <class ... TT>
   void operator () (const TT & ... tt)
    {
     (void)( (*this) += ... += tt );
    }

   // put

   template <class ... CC>
   void put(CC ... cc)
    {
     (void)( (*this) << ... << cc );
    }
 };

/* class PutobjDev<void> */

template <>
class PutobjDev<void>
 {
   // operator <<

   PutobjDev<void> & operator << (char)
    {
     return *this;
    }

  public:

   template <class S>
   explicit PutobjDev(S &&) {}

   template <class ... TT>
   void operator () (const TT & ...) {}

   // put

   template <class ... CC>
   void put(CC ... cc)
    {
     (void)( (*this) << ... << cc );
    }
 };

/* struct BindOpt<OptType,T> */

template <class OptType,class T>
struct BindOpt
 {
  const OptType &opt;
  const T &t;

  BindOpt(const OptType &opt_,const T &t_) : opt(opt_),t(t_) {}

  void print(PrinterType &out) const
   {
    PrintAdapter<T>::Print(out,opt,t);
   }
 };

/* Printf() */

template <class P,PrintableType ... TT>
void Printf(P &&out,const char *format,const TT & ... tt) CCORE_NOINLINE ;

template <class P,PrintableType ... TT>
void Printf(P &&out,const char *format,const TT & ... tt)
 {
  PrintfDev<PrintOutType<Meta::UnConst<Meta::UnRef<P> > > > dev(out,format);

  dev(tt...);
 }

/* Putobj() */

template <class P,PrintableType ... TT>
void Putobj(P &&out,const TT & ... tt) CCORE_NOINLINE ;

template <class P,PrintableType ... TT>
void Putobj(P &&out,const TT & ... tt)
 {
  PutobjDev<PrintOutType<Meta::UnConst<Meta::UnRef<P> > > > dev(out);

  dev(tt...);
 }

/* Putch() */

template <class P,class ... CC>
void Putch(P &&out,CC ... cc) CCORE_NOINLINE ;

template <class P,class ... CC>
void Putch(P &&out,CC ... cc)
 {
  PutobjDev<PrintOutType<Meta::UnConst<Meta::UnRef<P> > > > dev(out);

  dev.put(cc...);
 }

/* struct PrintProxy<MSec> */

template <>
struct PrintProxy<MSec>
 {
  struct ProxyType
   {
    unsigned time_msec;

    explicit ProxyType(MSec time) : time_msec(+time) {}

    void print(PrinterType &out) const
     {
      if( time_msec<1000 )
        {
         Printf(out,"#; msec",time_msec);
        }
      else if( time_msec<60*1000 )
        {
         unsigned t=time_msec/1000;

         Printf(out,"#;.#; sec",t,time_msec%1000);
        }
      else
        {
         unsigned t=time_msec/1000;

         Printf(out,"#; min #;.#; sec",t/60,t%60,time_msec%1000);
        }
     }
   };
 };

} // namespace CCore

#endif



