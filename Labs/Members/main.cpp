/* main.cpp */

#include <CCore/inc/Print.h>

using namespace CCore;

template <class IList,class ... TT> struct ConstTupleFactory;

template <class ... TT,int ... IList>
struct ConstTupleFactory<Meta::IndexListBox<IList...>,TT...>
 {
  template <int Ind,class T>
  struct Field
   {
    T field;

    explicit constexpr Field(const T &t) : field(t) {}
   };

  template <int I,class T>
  static constexpr const Field<I,T> * Cast(const Field<I,T> *ptr) { return ptr; }

  struct Tuple : Field<IList,TT>...
   {
    explicit constexpr Tuple(const TT & ... tt) : Field<IList,TT>(tt)... {}

    template <int I>
    constexpr auto get() const { return Cast<I>(this)->field; }

    template <class Func>
    constexpr auto call(Func func) const { return func( get<IList>()... ); }
   };
 };

template <class ... TT>
struct MemberList
 {
  using ListType = typename ConstTupleFactory< Meta::IndexList<1,TT...> ,TT...>::Tuple ;

  ListType list;

  constexpr MemberList(TT ... tt) : list(tt...) {}

  decltype(auto) operator () (auto *ptr,auto func) const
   {
    return list.call( [&] (auto ... mm) { return func( (ptr->*mm)... ); } );
   }

  template <class Func>
  struct Apply
   {
    Func &func;

    template <class S,class ... SS>
    constexpr decltype(auto) operator () (SS S::* ...)
     {
      return func.template operator() <SS...> ();
     }
   };

  template <class Func>
  constexpr decltype(auto) operator () (Func func) const
   {
    return list.call( Apply<Func>{func} );
   }
 };

struct Test1
 {
  int a;
  int b[10];
  long c;

  // way1

  decltype(auto) members(auto func) const
   {
    return func(a,b,c);
   }

  decltype(auto) members(auto func)
   {
    return func(a,b,c);
   }

  // way2

  friend decltype(auto) Members(OneOfTypes<Test1,const Test1> *ptr,auto func)
   {
    return func(ptr->a,ptr->b,ptr->c);
   }

  // way3

  static constexpr auto Members()
   {
    using This = Test1 ;

    return MemberList( &This::a , &This::b , &This::c );
   }
 };

struct Test2
 {
  double a;
  Test1 b;

  friend decltype(auto) Members(OneOfTypes<Test2,const Test2> *ptr,auto func)
   {
    return func(ptr->a,ptr->b);
   }
 };

struct SumSizeof
 {
  template <class ... TT>
  ulen operator () (TT & ... tt)
   {
    return ( ... + sizeof tt );
   }
 };

struct SumSizeof1
 {
  template <class ... TT>
  constexpr ulen operator () ()
   {
    return ( ... + sizeof (TT) );
   }
 };

/* main() */

inline constexpr ulen Len = Test1::Members()( SumSizeof1() );

int main()
 {
  Test1 test1;
  Test2 test2;

  Printf(Con,"sum sizeof = #;\n",test1.members( SumSizeof() ));

  Printf(Con,"sum sizeof = #;\n",Test1::Members()( &test1 , SumSizeof() ));

  Printf(Con,"sum sizeof = #;\n",Len);

  Printf(Con,"sum sizeof = #;\n",Members( &test2 , SumSizeof() ));

  return 0;
 }
