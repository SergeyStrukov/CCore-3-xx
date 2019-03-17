/* main.cpp */

#include <CCore/inc/Print.h>

using namespace CCore;

/* struct ConstTupleFactory<TT> */

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
    constexpr decltype(auto) get() const { return Cast<I>(this)->field; }

    template <class Func>
    constexpr decltype(auto) call(Func func) const { return func( get<IList>()... ); }
   };
 };

/* struct ConstTuple<TT> */

template <class ... TT>
using ConstTupleAlias = typename ConstTupleFactory< Meta::IndexList<1,TT...> ,TT...>::Tuple ;

template <class ... TT>
struct ConstTuple : ConstTupleAlias<TT...>
 {
  using ConstTupleAlias<TT...>::ConstTupleAlias;
 };

template <class ... TT>
ConstTuple(const TT & ... tt) -> ConstTuple<TT...> ;

/* struct MemberList<MM> */

template <class ... MM>
struct MemberList
 {
  ConstTuple<MM...> list;

  constexpr MemberList(const MM & ... mm) : list(mm...) {}

  decltype(auto) operator () (auto *ptr,auto func) const
   {
    return list.call( [&] (auto ... mm) { return func( (ptr->*mm)... ); } );
   }

  void per(auto *ptr,auto func) const
   {
    operator () (ptr, [&] (auto & ... x) { ( ... , func(x) ); } );
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

/* MembersOf<T>() */

template <class T>
constexpr auto MembersOf()
 {
  return T::template Fold<MemberList,T>();
 }

/* const Members<T> */

template <class T>
inline constexpr auto Members = MembersOf<T>() ;

/* test */

/* struct Test1 */

struct Test1
 {
  int a;
  int b[10];
  double c;

  template <template <class ...> class Ret,class T>
  static constexpr auto Fold()
   {
    return Ret(&T::a,&T::b,&T::c);
   }
 };

void SetNull(int &a)
 {
  Printf(Con,"int\n");

  a=0;
 }

void SetNull(double &a)
 {
  Printf(Con,"double\n");

  a=0;
 }

void SetNull(int (&a)[10])
 {
  Printf(Con,"int [10]\n");

  for(int &x : a ) x=0;
 }

struct SumSizeof
 {
  template <class ... TT>
  constexpr ulen operator () ()
   {
    return ( ... + sizeof (TT) );
   }
 };

/* main() */

int main()
 {
  constexpr auto members=Members<Test1>;

  Test1 obj1{};

  members(&obj1, [] (auto & ... x) { ( ... , SetNull(x) ); } );

  members.per(&obj1, [] (auto &x) { SetNull(x); } );

  ulen len1=members(&obj1, [] (auto & ... x) { return ( ... + sizeof x ); } );

  Printf(Con,"sum sizeof = #;\n",len1);

  constexpr ulen len2=Members<Test1>(SumSizeof());

  Printf(Con,"sum sizeof = #;\n",len2);

  return 0;
 }
