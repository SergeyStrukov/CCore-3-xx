/**/

template <class T>
struct IncList
 {
  template <class S>
  IncList<T> operator - (IncList<S>) { return {}; }

  using Type = T ;
 };

/**/

template <int Ind>
struct PickTypeInd
 {
  template <class T>
  PickTypeInd<Ind-1> operator - (IncList<T>) { return {}; }
 };

template <>
struct PickTypeInd<1>
 {
  template <class T>
  IncList<T> operator - (IncList<T>) { return {}; }
 };

/**/

template <int Ind,class ... TT>
using PickType = typename decltype( ( PickTypeInd<Ind>() - ... - IncList<TT>() ) )::Type ;

/**/

template <int ... IList>
struct IntList
 {
  template <class T>
  IntList<IList...,1+sizeof ... (IList)> operator + (IncList<T>) { return {}; }
 };

/**/

template <class ... TT>
struct TupleFactory
 {
  template <int Ind>
  using Type = PickType<Ind,TT...> ;

  template <int Ind>
  struct Field
   {
    Type<Ind> field;
   };

  template <int ... IList>
  struct Tuple : Field<IList>...
   {
    template <int I>
    auto & ref() { return ((Field<I> *)this)->field; }
   };

  template <int ... IList>
  static constexpr Tuple<IList...> FromList(IntList<IList...>) { return {}; }

  using Ret = decltype( FromList( ( IntList<>() + ... + IncList<TT>() ) ) ) ;
 };

template <class ... TT>
using Tuple = typename TupleFactory<TT...>::Ret ;
