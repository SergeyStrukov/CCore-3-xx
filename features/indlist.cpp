template <int Ind,class T>
struct IndType
 {
 };

template <class ... TT>
struct TypeList
 {
  template <int Ind,class T>
  TypeList<TT...,IndType<(sizeof ... (TT))+Ind,T> > operator + (IndType<Ind,T>) { return {}; }
 };

template <class ... TT>
using IndList = decltype( ( TypeList<>{} + ... + IndType<1,TT>{} ) ) ;
