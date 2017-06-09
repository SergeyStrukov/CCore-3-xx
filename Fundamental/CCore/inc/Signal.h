/* Signal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Signal_h
#define CCore_inc_Signal_h

#include <CCore/inc/List.h>
#include <CCore/inc/FunctorType.h>
#include <CCore/inc/DestroyGuard.h>

namespace CCore {

/* classes */

template <class ... TT> class Signal;

template <class S,class ... TT> class SignalConnector;

template <class I> class SignalInterface;

template <class I> class SignalInterfaceConnector;

/* class Signal<TT> */

template <class ... TT>
class Signal : NoCopy
 {
   DestroyGuard dg;

   struct Node : NoCopy
    {
     DLink<Node> link;
     Signal<TT...> *signal;

     void (Node::* call)(TT ... tt);

     explicit Node(void (Node::* call_)(TT ... tt)) : signal(0),call(call_) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   typename Algo::Top list;
   typename Algo::Cur cur;
   ulen count;

  private:

   void ins(Node *node)
    {
     list.ins(node);

     count++;
    }

   void del(Node *node)
    {
     if( node==cur.ptr )
       {
        list.del_and_move(cur);
       }
     else
       {
        list.del(node);
       }

     count--;
    }

  public:

   // constructors

   Signal() : cur(0),count(0) {}

   ~Signal();

   // props

   ulen getConnectedCount() const { return count; }

   // methods

   void assert(TT ... tt);

   // class ConnectorBase

   class ConnectorBase : Node
    {
      using Node::signal;

     public:

      // constructors

      template <IsDerivedFrom<ConnectorBase> S>
      explicit ConnectorBase(void (S::* call)(TT ... tt)) : Node(static_cast<void (Node::*)(TT ... tt)>(call)) {}

      ~ConnectorBase() {} // disconnect() must be called in the destructor of a derived class

      // props

      bool isConnected() const { return signal!=0; }

      // methods

      bool connect(Signal<TT...> &signal_)
       {
        if( signal ) return false;

        signal=&signal_;

        signal->ins(this);

        return true;
       }

      bool disconnect()
       {
        if( !signal ) return false;

        signal->del(this);

        signal=0;

        return true;
       }
    };
 };

template <class ... TT>
Signal<TT...>::~Signal()
 {
  dg.guard("Signal"_c);

  for(auto cur=list.start(); +cur ;++cur) cur->signal=0;
 }

template <class ... TT>
void Signal<TT...>::assert(TT ... tt)
 {
  DestroyGuard::Lock lock(dg);

  cur=list.start();

  while( +cur )
    {
     auto temp=cur.ptr;

     ++cur;

     try
       {
        (temp->*(temp->call))(tt...);
       }
     catch(...) {}
    }
 }

/* class SignalConnector<S,TT> */

template <class S,class ... TT>
class SignalConnector : public Signal<TT...>::ConnectorBase
 {
   S *obj;
   void (S::* method)(TT ... tt);

  private:

   void call(TT ... tt) { (obj->*method)(tt...); }

  public:

   // constructors

   SignalConnector(S *obj_,void (S::* method_)(TT ... tt))
    : Signal<TT...>::ConnectorBase(&SignalConnector<S,TT...>::call),
      obj(obj_),
      method(method_)
    {
    }

   SignalConnector(S *obj_,void (S::* method_)(TT ... tt),Signal<TT...> &signal)
    : SignalConnector(obj_,method_)
    {
     this->connect(signal);
    }

   ~SignalConnector()
    {
     this->disconnect();
    }
 };

/* class SignalInterface<I> */

template <class I>
class SignalInterface : NoCopy
 {
   DestroyGuard dg;

   struct Node : NoCopy
    {
     DLink<Node> link;
     SignalInterface<I> *signal;

     I *iptr;

     explicit Node(I *iptr_) : signal(0),iptr(iptr_) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   typename Algo::Top list;
   typename Algo::Cur cur;
   ulen count;

  private:

   void ins(Node *node)
    {
     list.ins(node);

     count++;
    }

   void del(Node *node)
    {
     if( node==cur.ptr )
       {
        list.del_and_move(cur);
       }
     else
       {
        list.del(node);
       }

     count--;
    }

  public:

   // constructors

   SignalInterface() : cur(0),count(0) {}

   ~SignalInterface();

   // props

   ulen getConnectedCount() const { return count; }

   // methods

   template <FuncInitArgType<I &> FuncInit>
   void assert(FuncInit func_init);

   // class ConnectorBase

   class ConnectorBase : Node
    {
      using Node::signal;

     public:

      // constructors

      explicit ConnectorBase(I *iptr) : Node(iptr) {}

      ~ConnectorBase() {} // disconnect() must be called in the destructor of a derived class

      // props

      bool isConnected() const { return signal!=0; }

      // methods

      bool connect(SignalInterface<I> &signal_)
       {
        if( signal ) return false;

        signal=&signal_;

        signal->ins(this);

        return true;
       }

      bool disconnect()
       {
        if( !signal ) return false;

        signal->del(this);

        signal=0;

        return true;
       }
    };
 };

template <class I>
SignalInterface<I>::~SignalInterface()
 {
  dg.guard("SignalInterface"_c);

  for(auto cur=list.start(); +cur ;++cur) cur->signal=0;
 }

template <class I>
template <FuncInitArgType<I &> FuncInit>
void SignalInterface<I>::assert(FuncInit func_init)
 {
  DestroyGuard::Lock lock(dg);

  FunctorTypeOf<FuncInit> func(func_init);

  cur=list.start();

  while( +cur )
    {
     I *temp=cur->iptr;

     ++cur;

     try
       {
        func(*temp);
       }
     catch(...) {}
    }
 }

/* class SignalInterfaceConnector<I> */

template <class I>
class SignalInterfaceConnector : public SignalInterface<I>::ConnectorBase
 {
  public:

   // constructors

   explicit SignalInterfaceConnector(I *obj) : SignalInterface<I>::ConnectorBase(obj) {}

   SignalInterfaceConnector(I *obj,SignalInterface<I> &signal)
    : SignalInterfaceConnector(obj)
    {
     this->connect(signal);
    }

   ~SignalInterfaceConnector()
    {
     this->disconnect();
    }
 };

} // namespace CCore

#endif


