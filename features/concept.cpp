template <class T>
struct PrintableTupleTypeCtor
 {
  enum RetType { Ret = false };
 };

template <class T>
concept bool PrintableType = (bool)PrintableTupleTypeCtor<T>::Ret || requires(PrintBase &out,const T &t)
 {
  PrintAdapter<T>::Print(out,t);
 } ;

template <PrintableType ... TT>
struct PrintableTupleTypeCtor<Tuple<TT...> >
 {
  enum RetType { Ret = true };
 };

