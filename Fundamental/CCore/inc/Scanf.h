/* Scanf.h */
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

#ifndef CCore_inc_Scanf_h
#define CCore_inc_Scanf_h

#include <CCore/inc/scanf/ScanBase.h>
#include <CCore/inc/scanf/ScanProxy.h>
#include <CCore/inc/DetectProxy.h>
#include <CCore/inc/Tuple.h>

namespace CCore {

/* word EndOfScan */

enum EndOfScanType { EndOfScan };

template <>
struct ScanProxy<EndOfScanType>
 {
  struct ProxyType
   {
    explicit ProxyType(EndOfScanType &) {}

    void scan(ScannerType &inp)
     {
      if( +inp ) inp.fail();
     }
   };
 };

/* classes */

template <class T> struct ScanOptAdapter;

template <class T> struct ScanAdapter;

struct ScanfDevBase;

template <class S> class ScanfDev;

template <class S> class ScanobjDev;

template <class OptType,class T> struct BindScanOpt;

template <class T,class ProxySet> struct ScanProxySet;

/* struct ScanOptAdapter<T> */

template <class T> requires ( No_ProxyType<ScanProxy<T> > )
struct ScanOptAdapter<T>
 {
  // empty
 };

template <class T> requires ( Has_ProxyType<ScanProxy<T> > && No_OptType<ScanProxy<T> > )
struct ScanOptAdapter<T>
 {
  // empty
 };

template <class T> requires ( Has_ProxyType<ScanProxy<T> > && Has_OptType<ScanProxy<T> > )
struct ScanOptAdapter<T>
 {
  using ScanOptType = typename ScanProxy<T>::OptType ;
 };

/* concept ProxyScanType<Proxy> */

template <class Proxy>
concept bool ProxyScanType = requires(ScanBase &inp,Proxy obj)
 {
  obj.scan(inp);
 } ;

/* concept ProxyOptScanType<Proxy,Opt> */

template <class Proxy,class Opt>
concept bool ProxyOptScanType = requires(ScanBase &inp,Proxy obj,Opt opt)
 {
  obj.scan(inp,opt);
 } ;

/* struct ScanAdapter<T> */

template <class T> requires ( No_ProxyType<ScanProxy<T> > )
struct ScanAdapter<T>
 {
  // empty
 };

template <class T> requires ( Has_ProxyType<ScanProxy<T> > && No_OptType<ScanProxy<T> > )
struct ScanAdapter<T>
 {
  using ProxyType = typename ScanProxy<T>::ProxyType ;

  static void Scan(ScannerType &inp,const char *,const char *,T &t)
   {
    ProxyType proxy(t);

    proxy.scan(inp.scanRef());
   }

  static void Scan(ScannerType &inp,const AnyType &,T &t)
   {
    ProxyType proxy(t);

    proxy.scan(inp.scanRef());
   }

  static void Scan(ScannerType &inp,T &t) requires ( ProxyScanType<ProxyType> )
   {
    ProxyType proxy(t);

    proxy.scan(inp.scanRef());
   }
 };

template <class T> requires ( Has_ProxyType<ScanProxy<T> > && Has_OptType<ScanProxy<T> > )
struct ScanAdapter<T>
 {
  using ProxyType = typename ScanProxy<T>::ProxyType ;

  using OptType = typename ScanProxy<T>::OptType ;

  static void Scan(ScannerType &inp,const char *ptr,const char *lim,T &t)
   {
    OptType opt(ptr,lim);
    ProxyType proxy(t);

    proxy.scan(inp.scanRef(),opt);
   }

  static void Scan(ScannerType &inp,const OptType &opt,T &t)
   {
    ProxyType proxy(t);

    proxy.scan(inp.scanRef(),opt);
   }

  static void Scan(ScannerType &inp,T &t) requires ( ProxyOptScanType<ProxyType,OptType> )
   {
    OptType opt{};
    ProxyType proxy(t);

    proxy.scan(inp.scanRef(),opt);
   }
 };

/* concept ScanableType<T> */

template <class T>
concept bool ScanableType2 = requires(ScanBase &inp,T &t)
 {
  ScanAdapter<T>::Scan(inp,t);
 } ;

template <class T>
inline constexpr bool IsScanableType = ScanableType2<T> ;

template <class ... TT>
inline constexpr bool IsScanableType<Tuple<TT...> > = ( ... && IsScanableType< Meta::UnRef<TT> > ) ;

template <class T>
concept bool ScanableType = IsScanableType< Meta::UnRef<T> > ;

/* struct ScanfDevBase */

struct ScanfDevBase : NoCopy
 {
  static constexpr char OpenFormat  = '#' ;
  static constexpr char CloseFormat = ';' ;

  static bool NotFound(char cur,char ch) { return cur && cur!=ch ;  }

  static const char * Find(const char *format,char ch);

  struct OptStr
   {
    const char *ptr;
    const char *lim;

    OptStr(NothingType) : ptr(0),lim(0) {}

    OptStr(const char *ptr_,const char *lim_) : ptr(ptr_),lim(lim_) {}

    template <ScannerType S,class T>
    void scan(S &inp,T &t) const
     {
      if( !ptr )
        {
         inp.fail();
        }
      else
        {
         ScanAdapter<T>::Scan(inp,ptr,lim,t);
        }
     }

    template <ScannerType S>
    void scan(S &inp) const
     {
      if( !ptr )
        {
         // do nothing
        }
      else
        {
         inp.fail();
        }
     }
   };
 };

/* class ScanfDev<S> */

template <class S> requires ( ScannerType<Meta::UnRef<S> > )
class ScanfDev<S> : ScanfDevBase
 {
   S inp;
   const char *format;

  private:

   void match(char ch);

   void match(const char *ptr,ulen len);

   OptStr find();

   // expand

   template <class ... TT>
   void expand(Tuple<TT...> &tuple)
    {
     tuple.call( [this] (TT & ...tt) { ( (*this) >> ... >> tt ); } );
    }

   // operator >>

   template <class T>
   ScanfDev<S> & operator >> (T &t)
    {
     find().scan(inp,t);

     return *this;
    }

   template <class ... TT>
   ScanfDev<S> & operator >> (Tuple<TT...> &tuple)
    {
     expand(tuple);

     return *this;
    }

  public:

   template <class T>
   ScanfDev(T &&inp_,const char *format_) : inp(inp_),format(format_) {}

   ~ScanfDev() {}

   template <class ... TT>
   void operator () (TT & ... tt)
    {
     (void)( (*this) >> ... >> tt );

     if( *format ) find().scan(inp);
    }
 };

template <class S> requires ( ScannerType<Meta::UnRef<S> > )
void ScanfDev<S>::match(char ch)
 {
  if( ch==' ' )
    {
     SkipSpace(inp);
    }
  else
    {
     PassChars(inp,ch);
    }
 }

template <class S> requires ( ScannerType<Meta::UnRef<S> > )
void ScanfDev<S>::match(const char *ptr,ulen len)
 {
  for(char ch : Range(ptr,len) ) match(ch);
 }

template <class S> requires ( ScannerType<Meta::UnRef<S> > )
auto ScanfDev<S>::find() -> OptStr // ^aaaaaa##aaaaaaaaaaaa#opt;
 {
  for(;;)
    {
     const char *ptr=Find(format,OpenFormat);

     match(format,Dist(format,ptr));

     if( *ptr )                // ^##aaaaaaaaaaaa#opt;
       {
        ptr++;

        if( *ptr==OpenFormat ) // ^#aaaaaaaaaaaa#opt;
          {
           match(OpenFormat);

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

/* class ScanobjDev<S> */

template <class S> requires ( ScannerType<Meta::UnRef<S> > )
class ScanobjDev<S> : NoCopy
 {
   S inp;

  private:

   // expand

   template <class ... TT>
   void expand(Tuple<TT...> &tuple)
    {
     tuple.call( [this] (TT & ...tt) { ( (*this) >> ... >> tt ); } );
    }

   // operator >>

   template <class T>
   ScanobjDev<S> & operator >> (T &t)
    {
     ScanAdapter<T>::Scan(inp,t);

     return *this;
    }

   template <class ... TT>
   ScanobjDev<S> & operator >> (Tuple<TT...> &tuple)
    {
     expand(tuple);

     return *this;
    }

  public:

   template <class T>
   explicit ScanobjDev(T &&inp_) : inp(inp_) {}

   ~ScanobjDev() {}

   template <class ... TT>
   void operator () (TT & ... tt)
    {
     (void)( (*this) >> ... >> tt );
    }
 };

/* struct BindScanOpt<OptType,T> */

template <class OptType,class T>
struct BindScanOpt
 {
  const OptType &opt;
  T &t;

  BindScanOpt(const OptType &opt_,T &t_) : opt(opt_),t(t_) {}

  void scan(ScannerType &inp)
   {
    ScanAdapter<T>::Scan(inp,opt,t);
   }
 };

/* struct ScanProxySet<T,ProxySet> */

template <class T,class ProxySet>
struct ScanProxySet : ScanOptAdapter<ProxySet>
 {
  struct ProxyType
   {
    T &ret;

    explicit ProxyType(T &ret_) : ret(ret_) {}

    void scan(ScannerType &inp)
     {
      ProxySet set;

      Scanobj(inp,set);

      set.map(ret);
     }

    void scan(ScannerType &inp,const AnyType &opt)
     {
      ProxySet set;

      Scanobj(inp,BindScanOpt(opt,set));

      set.map(ret);
     }
   };
 };

/* Scanf() */

template <class S,ScanableType ... TT>
void Scanf(S &&inp,const char *format,TT && ... tt) CCORE_NOINLINE ;

template <class S,ScanableType ... TT>
void Scanf(S &&inp,const char *format,TT && ... tt)
 {
  ScanfDev<ScanInpType<Meta::UnConst<Meta::UnRef<S> > > > dev(inp,format);

  dev(tt...);
 }

/* Scanobj() */

template <class S,ScanableType ... TT>
void Scanobj(S &&inp,TT && ... tt) CCORE_NOINLINE ;

template <class S,ScanableType ... TT>
void Scanobj(S &&inp,TT && ... tt)
 {
  ScanobjDev<ScanInpType<Meta::UnConst<Meta::UnRef<S> > > > dev(inp);

  dev(tt...);
 }

} // namespace CCore

#endif


