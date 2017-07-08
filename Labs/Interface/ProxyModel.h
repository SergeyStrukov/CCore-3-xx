/* ProxyModel.h */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Interface
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ProxyModel_h
#define ProxyModel_h

#include <CCore/inc/Tuple.h>

namespace CCore {

namespace Private_ProxyModel {

/* classes */

template <class ... TT> struct ProxyTable;

template <class Table,class T,auto Build> struct StaticProxyTable;

struct AnyCast;

struct AnyMove;

struct AnyMethod;

template <class ... TT> struct ProbeTypeList;

template <class T> struct ProxyTableOf;

template <class Anchor,template <class> class Model> class ProxyModelBase;

template <class Anchor,template <class> class Model> class ProxyModel;

/* type FunchorPtr<T> */

template <class T>
using FunchorPtr = T Funchor::* ;

/* struct ProxyTable<TT> */

template <class ... TT>
struct ProxyTable : Tuple< FunchorPtr<TT>... >
 {
  template <class ... SS>
  explicit ProxyTable(SS ... ss) : Tuple< FunchorPtr<TT>... >( static_cast< FunchorPtr<TT> >(ss)... ) {}
 };

/* struct StaticProxyTable<Table,T,auto Build> */

template <class Table,class T,auto Build>
struct StaticProxyTable
 {
  static const Table Object;
 };

template <class Table,class T,auto Build>
const Table StaticProxyTable<Table,T,Build>::Object = Build() ;

/* struct AnyCast */

struct AnyCast
 {
  void *ptr;

  template <class T>
  operator T & () const { return *static_cast<T *>(ptr); }
 };

/* struct AnyMove */

struct AnyMove
 {
  void *ptr;

  template <class T>
  operator T () const { return std::move(*static_cast<T *>(ptr)); }
 };

/* struct AnyMethod */

struct AnyMethod
 {
  template <int Ind,class ... TT>
  AnyCast & method(TT && ...) const { throw 0; }
 };

/* struct ProbeTypeList<TT> */

template <class ... TT>
struct ProbeTypeList
 {
  ProbeTypeList(TT ...) {}
 };

/* struct ProxyTableOf<T> */

template <class S,class ... TT>
struct ProxyTableOf<ProbeTypeList<TT S::* ...> >
 {
  using Ret = ProxyTable<TT...> ;
 };

/* class ProxyModelBase<Anchor,Model> */

template <class Anchor,template <class> class Model>
class ProxyModelBase
 {
   template <template <class ...> class Ret,class T>
   static auto Build()
    {
     return Model<AnyMethod>::template Fold<Ret,T>();
    }

   template <template <class ...> class Ret>
   static auto BuildSelf()
    {
     return Build<Ret,Model<AnyMethod> >();
    }

   template <class Ret,class T>
   static Ret BuildObj()
    {
     auto tuple=Build<Tuple,T>();

     return tuple.call( [] (auto ... tt) { return Ret(tt...); } );
    }

   using ModelProxyTable = typename ProxyTableOf<decltype( BuildSelf<ProbeTypeList>() )>::Ret ;

  private:

   Anchor *obj;
   const ModelProxyTable *table;

  public:

   ProxyModelBase() noexcept : obj(0),table(0) {}

   template <class T>
   ProxyModelBase(T &obj_)
    {
     obj=&obj_;
     table=&StaticProxyTable<ModelProxyTable,T,BuildObj<ModelProxyTable,T> >::Object;
    }

   auto operator + () const { return obj; }

   bool operator ! () const { return !obj; }

   template <int Ind,class ... TT>
   decltype(auto) method(TT && ... tt) const { return (obj->*table->template ref<Ind>())( std::forward<TT>(tt)... ); }
 };

/* class ProxyModel<Anchor,Model> */

template <class Anchor,template <class> class Model>
class ProxyModel : public Model<ProxyModelBase<Anchor,Model> >
 {
  public:

   ProxyModel() noexcept {}

   using Model<ProxyModelBase<Anchor,Model> >::Model;
 };

} // namespace Private_ProxyModel

/* types */

template <template <class> class Model>
using ProxyModel = Private_ProxyModel::ProxyModel<Funchor,Model> ;

template <template <class> class Model>
using ConstProxyModel = Private_ProxyModel::ProxyModel<const Funchor,Model> ;

/* RetMove() */

template <class T>
T RetMove(T obj) { return obj; }

Private_ProxyModel::AnyMove RetMove(Private_ProxyModel::AnyCast obj) { return Private_ProxyModel::AnyMove{obj.ptr}; }

} // namespace CCore

#endif


