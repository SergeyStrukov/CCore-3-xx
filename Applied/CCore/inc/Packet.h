/* Packet.h */
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

#ifndef CCore_inc_Packet_h
#define CCore_inc_Packet_h

#include <CCore/inc/Timer.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Move.h>

#include <CCore/inc/task/Atomic.h>

namespace CCore {

/* consts */

inline constexpr ulen MaxPacketExtLen = Align(256) ;

inline constexpr ulen MaxPacketCompleteFunctions = 8 ;

inline constexpr ulen DefaultPacketMaxDataLen = 1600 ;

enum PacketCancelState
 {
  Packet_NoCancelFunction,
  Packet_HasCancelFunction,
  Packet_Cancelled
 };

enum LenStatus
 {
  Len_ok,
  Len_too_short,
  Len_too_long
 };

/* functions */

void GuardLenSubTooShort(const char *name,ulen len,ulen delta);

inline ulen LenSub(const char *name,ulen len,ulen delta) // always > 0
 {
  if( len<=delta ) GuardLenSubTooShort(name,len,delta);

  return len-delta;
 }

/* classes */

struct PacketFormat;

class PacketBuf;

class PacketHeader;

template <class POD,class Box> struct PacketBoxCtor;

template <class POD,class ... TT> struct PacketExtType;

template <class Box> struct PacketDeepExtBox;

template <unsigned Index,class ... TT> requires ( Index > 0 && Index <= sizeof ... (TT) ) struct PacketDeepExt;

template <PODType POD,class ... TT> class Packet;

class PacketCanceller;

class PacketList;

/* types */

using TimeStamp = SecTimer::ValueType ;

using PacketFunction = Function<void (PacketHeader *)> ;

/* struct PacketFormat */

struct PacketFormat
 {
  ulen prefix;
  ulen max_data;
  ulen suffix;

   // prefix + suffix + max_data <= MaxULen

  PacketFormat() noexcept
   {
    prefix=0;
    max_data=0;
    suffix=0;
   }

  PacketFormat(NothingType) : PacketFormat() {}

  ulen getMaxTotalLen() const { return prefix+max_data+suffix; }

  PacketFormat addPrefix(ulen prefix_len) const;

  PacketFormat addSuffix(ulen suffix_len) const;

  PacketFormat addPrefixSuffix(ulen prefix_len,ulen suffix_len) const;

  ulen add(ulen len) const // return total_len;
   {
    ulen delta=prefix+suffix;

    return len+delta;
   }

  struct SubResult
   {
    ulen len;
    LenStatus status;

    SubResult(ulen len_,LenStatus status_) : len(len_),status(status_) {}

    bool isTooShort() const { return status==Len_too_short; }

    bool notFitFormat() const { return status!=Len_ok; }
   };

  SubResult sub(ulen total_len) const // return len;
   {
    ulen delta=prefix+suffix;

    if( total_len>=delta )
      {
       ulen len=total_len-delta;

       if( len<=max_data ) return SubResult(len,Len_ok);

       return SubResult(max_data,Len_too_long);
      }

    return SubResult(0,Len_too_short);
   }

  bool checkLen(ULenSat len,ulen max_total_len) const
   {
    ulen delta=prefix+suffix;

    return len<=max_data && len.value+delta<=max_total_len ;
   }

  bool check(ulen total_len) const
   {
    ulen delta=prefix+suffix;

    return total_len>=delta && total_len<=delta+max_data ;
   }

  template <class T>
  PtrLen<T> cut(PtrLen<T> range) const // assume check(range.len)
   {
    return range.inner(prefix,suffix);
   }

  template <class T>
  PtrLen<T> cutPrefix(PtrLen<T> range) const // assume check(range.len)
   {
    return range.prefix(prefix);
   }

  template <class T>
  PtrLen<T> cutSuffix(PtrLen<T> range) const // assume check(range.len)
   {
    return range.suffix(suffix);
   }

  template <class T>
  struct CutResult
   {
    PtrLen<T> range;
    LenStatus status;

    CutResult(PtrLen<T> range_,LenStatus status_) : range(range_),status(status_) {}

    bool operator ! () const { return status==Len_too_short; }
   };

  template <class T>
  CutResult<T> cutMax(PtrLen<T> range) const
   {
    ulen delta=prefix+suffix;

    if( range.len>=delta )
      {
       ulen len=range.len-delta;

       if( len<=max_data ) return CutResult<T>(range.part(prefix,len),Len_ok);

       return CutResult<T>(range.part(prefix,max_data),Len_too_long);
      }

    return CutResult<T>(Nothing,Len_too_short);
   }
 };

/* class PacketBuf */

class PacketBuf : NoCopy
 {
   void *data;
   ulen max_data_len;
   ulen data_len;

  private:

   static void GuardLenAbort();

   void guardLen(ulen data_len) const
    {
     if( data_len>max_data_len ) GuardLenAbort();
    }

  public:

   // constructors

   PacketBuf() noexcept
    {
     data=0;
     max_data_len=0;
     data_len=0;
    }

   explicit PacketBuf(ulen max_data_len);

   ~PacketBuf();

   // std move

   PacketBuf(PacketBuf &&obj) noexcept
    : data(Replace_null(obj.data)),
      max_data_len(Replace_null(obj.max_data_len)),
      data_len(Replace_null(obj.data_len))
    {
    }

   PacketBuf & operator = (PacketBuf &&obj) noexcept;

   // methods

   bool provide(ulen max_data_len);

   void detach();

   // data methods

   bool noSpace() const { return !max_data_len; }

   ulen getMaxRawLen() const { return max_data_len; }

   ulen getRawLen() const { return data_len; }

   void setRawLen(ulen data_len_) { guardLen(data_len_); data_len=data_len_; }

   Place<void> getRaw() { return PlaceAt(data); }
 };

/* const PacketDeepExtLen<TT> */

template <class ... TT>
inline constexpr ulen PacketDeepExtLen = ( ... + Align(sizeof (TT)) ) ;

/* class PacketHeader */

class PacketHeader : NoCopy
 {
   PacketBuf pbuf;

   TimeStamp time_stamp;

   Atomic cancel_state; // PacketCancelState
   PacketFunction cancel_function;
   void *cancel_arg;

   PacketFunction stack[MaxPacketCompleteFunctions];
   ulen stack_len;

   ulen ext_len;

   DLink<PacketHeader> link;
   bool in_list;

  private:

   static void PushCompleteFunctionAbort();

   static void PopCompleteFunctionAbort();

   static void PushExtAbort();

  private:

   using Algo = DLink<PacketHeader>::CircularAlgo<&PacketHeader::link> ;

   void initList();

   friend class PacketList;

  public:

   // constructors

   static constexpr ulen Delta() { return Align(sizeof (PacketHeader)); }

   static constexpr ulen AllocLen() { return Delta()+MaxPacketExtLen; }

   explicit PacketHeader(PacketFunction complete_function) noexcept;

   void recycle(PacketFunction complete_function);

   ~PacketHeader() {}

   // complete

   void pushCompleteFunction(PacketFunction complete_function)
    {
     if( stack_len>=MaxPacketCompleteFunctions ) PushCompleteFunctionAbort();

     stack[stack_len++]=complete_function;
    }

   PacketFunction popCompleteFunction()
    {
     if( stack_len==0 ) PopCompleteFunctionAbort();

     return Replace_null(stack[--stack_len]);
    }

   void complete() { popCompleteFunction()(this); }

   // cancel

   PacketCancelState setCancelFunction(PacketFunction cancel_function,void *cancel_arg=0);

   PacketCancelState clearCancelFunction();

   PacketCancelState getCancelFunction(PacketFunction &ret);

   void * getCancelArg() const { return cancel_arg; }

   // stamp

   TimeStamp getStamp() const { return time_stamp; }

   bool isOld(TimeStamp now,TimeStamp how_old) const { return now-time_stamp>how_old; }

   void stamp() { time_stamp=SecTimer::Get(); }

   // ext

   Place<void> getExtBase() { return PlaceAt(this)+Delta(); }

   template <class T,class ... SS>
   T * pushExt(SS && ... ss) requires ( NothrowDtorType<T> && ConstructibleType<T,SS...> )
    {
     static_assert( sizeof (T)<=MaxPacketExtLen ,"CCore::PacketHeader::pushExt<T>(...) : T is too large");

     auto place=getExtBase()+ext_len;

     if( ext_len>MaxPacketExtLen-Align(sizeof (T)) ) PushExtAbort();

     T *ret=new(place) T( std::forward<SS>(ss)... );

     ext_len+=Align(sizeof (T));

     return ret;
    }

   template <class T>
   T * getExt()
    {
     ulen off=ext_len-Align(sizeof (T));

     return getExtBase()+off;
    }

   template <class T,class ... TT>  // T, T1, T2, ... , Ttop
   T * getDeepExt()
    {
     ulen off=ext_len-PacketDeepExtLen<T,TT...>;

     return getExtBase()+off;
    }

   template <class T>
   void popExt()
    {
     ulen off=( ext_len-=Align(sizeof (T)) );

     T *ext=getExtBase()+off;

     ext->~T();
    }

   // data attach/detach

   bool provide(ulen max_data_len=DefaultPacketMaxDataLen);

   void detach();

   void attach(PacketBuf &pbuf);

   void detach(PacketBuf &pbuf);

   void detach(PacketHeader *dst);

   // raw data

   bool noSpace() const { return pbuf.noSpace(); }

   ulen getMaxRawLen() const { return pbuf.getMaxRawLen(); }

   ulen getRawLen() const { return pbuf.getRawLen(); }

   void setRawLen(ulen data_len) { pbuf.setRawLen(data_len); }

   Place<void> getRaw() { return pbuf.getRaw(); }
 };

/* struct PacketBoxCtor<POD,Box> */

template <class POD,class ... TT>
struct PacketBoxCtor<POD,Meta::TypeListBox<TT...> >
 {
  using Ret = Packet<POD,TT...> ;
 };

/* type PacketBox<POD,Box> */

template <class POD,class Box>
using PacketBox = typename PacketBoxCtor<POD,Box>::Ret ;

/* struct PacketExtType<POD,TT> */

template <class POD>
struct PacketExtType<POD>
 {
  using TopType = void ;

  using PopType = void ;
 };

#if 0

template <class POD,class T,class ... TT>
struct PacketExtType<POD,TT...,T>
 {
  using TopType = T ;

  using PopType = Packet<POD,TT...> ;
 };

#else

template <class POD,class ... TT>
struct PacketExtType
 {
  using Pop = Meta::PopTypeList<TT...> ;

  using TopType = typename Pop::Last ;

  using PopType = PacketBox<POD,typename Pop::Start> ;
 };

#endif

/* struct PacketDeepExtBox<Box> */

template <class T,class ... TT>
struct PacketDeepExtBox<Meta::TypeListBox<T,TT...> >
 {
  using GetType = T ;

  static T * Get(PacketHeader *packet) { return packet->getDeepExt<T,TT...>(); }
 };

/* struct PacketDeepExt<unsigned Index,TT> */

template <unsigned Index,class ... TT> requires ( Index > 0 && Index <= sizeof ... (TT) )
struct PacketDeepExt : PacketDeepExtBox<Meta::PartTypeList<Index-1,TT...> > {};

/* type PacketForgetExt<unsigned Index,POD,TT> */

template <unsigned Index,class POD,class ... TT> requires ( Index <= sizeof ... (TT) )
using PacketForgetExt = PacketBox<POD,Meta::PartTypeList<Index,TT...> > ;

/* class Packet<POD,TT> */

template <PODType POD,class ... TT> // T1, T2, ... , Ttop
class Packet
 {
   PacketHeader *packet;

  public:

   // constructors

   Packet() noexcept : packet(0) {}

   Packet(NothingType) : Packet() {}

   Packet(PacketHeader *packet_) : packet(packet_) {}

   // props

   PacketHeader * operator + () const { return packet; }

   bool operator ! () const { return !packet; }

   PacketHeader * getPtr() const { return packet; }

   // complete

   void pushCompleteFunction(PacketFunction complete_function) { packet->pushCompleteFunction(complete_function); }

   PacketFunction popCompleteFunction() { return packet->popCompleteFunction(); }

   void complete() { Replace_null(packet)->complete(); }

   // cancel

   PacketCancelState setCancelFunction(PacketFunction cancel_function,void *cancel_arg=0) { return packet->setCancelFunction(cancel_function,cancel_arg); }

   PacketCancelState clearCancelFunction() { return packet->clearCancelFunction(); }

   void * getCancelArg() { return packet->getCancelArg(); }

   // stamp

   TimeStamp getStamp() { return packet->getStamp(); }

   bool isOld(TimeStamp now,TimeStamp how_old) { return packet->isOld(now,how_old); }

   void stamp() { packet->stamp(); }

   // ext

   template <class T,class ... SS>
   Packet<POD,TT...,T> pushExt(SS && ... ss) requires ( NothrowDtorType<T> && ConstructibleType<T,SS...> )
    {
     PacketHeader *ret=Replace_null(packet);

     ret->pushExt<T>( std::forward<SS>(ss)... );

     return ret;
    }

   typename PacketExtType<POD,TT...>::TopType * getExt()
    {
     return packet->getExt<typename PacketExtType<POD,TT...>::TopType>();
    }

   typename PacketExtType<POD,TT...>::PopType popExt()
    {
     PacketHeader *ret=Replace_null(packet);

     ret->popExt<typename PacketExtType<POD,TT...>::TopType>();

     return ret;
    }

   template<unsigned Index>
   typename PacketDeepExt<Index,TT...>::GetType * getDeepExt()
    {
     return PacketDeepExt<Index,TT...>::Get(packet);
    }

   template<unsigned Index>
   PacketForgetExt<Index,POD,TT...> forgetExt()
    {
     return Replace_null(packet);
    }

   // data attach/detach

   bool provide(ulen max_data_len) { return packet->provide(max_data_len*sizeof (POD)); }

   bool provide() { return packet->provide(); }

   void detach() { packet->detach(); }

   void attach(PacketBuf &pbuf) { packet->attach(pbuf); }

   void detach(PacketBuf &pbuf) { packet->detach(pbuf); }

   void detach(PacketHeader *dst) { packet->detach(dst); }

   template <class ... SS>
   void detach(Packet<POD,SS...> dst) { packet->detach(dst.getPtr()); }

   // data

   bool noSpace() { return packet->noSpace(); }

   ulen getMaxDataLen() { return packet->getMaxRawLen()/sizeof (POD); }

   ulen getDataLen() { return packet->getRawLen()/sizeof (POD); }

   POD * getData() { return packet->getRaw(); }

   PtrLen<POD> getMaxRange() { return Range(getData(),getMaxDataLen()); }

   PtrLen<POD> getRange() { return Range(getData(),getDataLen()); }

   bool checkDataLen(ULenSat data_len)
    {
     return data_len<=getMaxDataLen();
    }

   PtrLen<POD> setDataLen(ULenSat data_len) // assume checkDataLen(data_len)
    {
     ulen raw_len=data_len.value*sizeof (POD);

     packet->setRawLen(raw_len);

     return Range(getData(),data_len.value);
    }

   // format

   PacketFormat::SubResult getMaxDataLen(PacketFormat format)
    {
     return format.sub(getMaxDataLen());
    }

   PacketFormat::SubResult getDataLen(PacketFormat format)
    {
     return format.sub(getDataLen());
    }

   PacketFormat::CutResult<POD> getMaxRange(PacketFormat format)
    {
     return format.cutMax(getMaxRange());
    }

   bool checkRange(PacketFormat format)
    {
     return format.check(getDataLen());
    }

   PtrLen<POD> getRange(PacketFormat format) // assume checkRange(format)
    {
     return format.cut(getRange());
    }

   PtrLen<POD> getPrefix(PacketFormat format) // assume checkRange(format)
    {
     return format.cutPrefix(getRange());
    }

   PtrLen<POD> getSuffix(PacketFormat format) // assume checkRange(format)
    {
     return format.cutSuffix(getRange());
    }

   bool checkDataLen(PacketFormat format,ULenSat data_len)
    {
     return format.checkLen(data_len,getMaxDataLen());
    }

   PtrLen<POD> setDataLen(PacketFormat format,ULenSat data_len) // assume checkDataLen(format,data_len)
    {
     setDataLen(format.add(data_len.value));

     return Range(getData()+format.prefix,data_len.value);
    }
 };

/* functions */

inline PacketHeader * GetPacketHeader(PacketHeader *packet) { return packet; }

template <class POD,class ... TT>
PacketHeader * GetPacketHeader(Packet<POD,TT...> packet) { return packet.getPtr(); }

template <class POD,class T>
void DropPacketExt(PacketHeader *packet_)
 {
  Packet<POD,T> packet=packet_;

  packet.popExt().complete();
 }

/* concept PacketType<P> */

template <class P>
concept bool PacketType = requires(P packet)
 {
  { GetPacketHeader(packet) } -> PacketHeader * ;
 } ;

/* class PacketCanceller */

class PacketCanceller : NoCopy
 {
   PacketHeader *packet;
   PacketFunction cancel_function;

  public:

   explicit PacketCanceller(PacketType packet_) : packet(GetPacketHeader(packet_)) {}

   bool getCancelFunction() { return packet->getCancelFunction(cancel_function)==Packet_HasCancelFunction; }

   void cancel() { cancel_function(packet); }
 };

/* class PacketList */

class PacketList : NoCopy
 {
   PacketHeader::Algo::Top list;
   ulen count;
   ulen total_len;

  private:

   void destroy();

   void post_ins(PacketHeader *packet);

   void post_del(PacketHeader *packet);

  public:

   // constructors

   PacketList() noexcept
    {
     count=0;
     total_len=0;
    }

   ~PacketList() { destroy(); }

   // std move

   PacketList(PacketList &&obj) noexcept
    : list(Replace_null(obj.list)),
      count(Replace_null(obj.count)),
      total_len(Replace_null(obj.total_len))
    {
    }

   PacketList & operator = (PacketList &&obj) noexcept
    {
     if( this!=&obj )
       {
        destroy();

        list=Replace_null(obj.list);
        count=Replace_null(obj.count);
        total_len=Replace_null(obj.total_len);
       }

     return *this;
    }

   // props

   ulen getCount() const { return count; }

   ulen getTotalLen() const { return total_len; }

   // put

   void put(PacketHeader *packet);

   void put_first(PacketHeader *packet);

   void put(PacketType packet) { put(GetPacketHeader(packet)); }

   void put_first(PacketType packet) { put_first(GetPacketHeader(packet)); }

   // get

   PacketHeader * get();

   PacketHeader * get_last();

   // del

   void del(PacketHeader *packet);

   void del(PacketType packet) { del(GetPacketHeader(packet)); }

   // methods

   void complete();

   void moveOld(TimeStamp how_old,PacketList &dest);

   // swap/move object

   void objSwap(PacketList &obj)
    {
     Swap(list,obj.list);
     Swap(count,obj.count);
     Swap(total_len,obj.total_len);
    }

   explicit PacketList(ToMoveCtor<PacketList> obj)
    : list(obj->list),
      count(Replace_null(obj->count)),
      total_len(obj->total_len)
    {
    }
 };

} // namespace CCore

#endif


