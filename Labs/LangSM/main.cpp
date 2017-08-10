/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/LangSM
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/lang/LangDataMap.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct Trans;

struct State;

class StateMachine;

class TopStateMachine;

class BottomStateMachine;

/* struct Trans */

struct Trans
 {
  ulen eindex;
  ulen sindex;
 };

/* struct State */

struct State
 {
  ulen sindex;
  ulen value;
  DynArray<Trans> trans;
 };

/* class StateMachine */

class StateMachine : NoCopy
 {
  protected:

   DynArray<State> states;

  public:

   explicit StateMachine() {}

   ~StateMachine() {}

   PtrLen<const State> getStates() const { return Range(states); }
 };

/* class TopStateMachine */

class TopStateMachine : public StateMachine
 {
  private:

   PtrLen<const Lang::TypeDef::Final> finals;

   ulen atom_count;
   ulen element_count;

  private:

   static void Set(Trans &obj,const Lang::TypeDef::State::Transition &t)
    {
     obj.eindex=t.element->index;
     obj.sindex=t.state->index;
    }

   static void Set(State &obj,ulen sindex,const Lang::TypeDef::State &s)
    {
     obj.sindex=sindex;
     obj.value=s.final->index;

     auto r=s.transitions.getRange();

     auto ptr=obj.trans.extend_raw(r.len).ptr;

     for(ulen i=0; i<r.len ;i++) Set(ptr[i],r[i]);
    }

  public:

   explicit TopStateMachine(const Lang::TypeDef::Lang &lang)
    {
     auto r=lang.states.getRange();

     auto base=states.extend_default(r.len).ptr;

     for(ulen i=0; i<r.len ;i++) Set(base[i],i,r[i]);

     finals=lang.finals.getRange();

     atom_count=lang.atoms.len;
     element_count=lang.elements.len;
    }

   ~TopStateMachine() {}

   PtrLen<const Lang::TypeDef::Final> getFinal() const { return finals; }

   ulen getAtomCount() const { return atom_count; }

   ulen getElementCount() const { return element_count; }
 };

/* class BottomStateMachine */

class BottomStateMachine : public StateMachine
 {
   struct Rec : CmpComparable<Rec>
    {
     const State *states;
     const ulen *groups;
     ulen ind;

     Rec(const State *states_,const ulen *groups_,ulen ind_) : states(states_),groups(groups_),ind(ind_) {}

     // cmp objects

     ulen getGroup() const { return groups[ind]; }

     PtrLen<const Trans> getTrans() const { return Range(states[ind].trans); }

     static CmpResult CmpTrans(const ulen *groups,Trans a,Trans b)
      {
       if( auto ret=Cmp(a.eindex,b.eindex) ) return ret;

       return Cmp(groups[a.sindex],groups[b.sindex]);
      }

     static CmpResult CmpTrans(const ulen *groups,PtrLen<const Trans> a,PtrLen<const Trans> b)
      {
       if( auto ret=Cmp(a.len,b.len) ) return ret;

       for(ulen i=0; i<a.len ;i++) if( auto ret=CmpTrans(groups,a[i],b[i]) ) return ret;

       return CmpEqual;
      }

     CmpResult objCmp(const Rec &obj) const
      {
       if( auto ret=Cmp(getGroup(),obj.getGroup()) ) return ret;

       return CmpTrans(groups,getTrans(),obj.getTrans());
      }
    };

  public:

   BottomStateMachine(const StateMachine &top,FuncType<ulen,ulen> func)
    {
     auto states=top.getStates();

     DynArray<ulen> new_value(states.len);

     for(ulen i=0; i<states.len ;i++) new_value[i]=func(states[i].value);

     // groups

     DynArray<ulen> buf_groups(DoCopy(states.len),new_value.getPtr());

     DynArray<ulen> buf_next(states.len);

     DynArray<ulen> buf_indexes(states.len);

     auto groups=Range(buf_groups);

     auto next_groups=Range(buf_next);

     auto indexes=Range(buf_indexes);

     // compress

     ulen group_count=0;

     for(;;)
       {
        for(ulen i=0; i<indexes.len ;i++) indexes[i]=i;

        auto by = [=] (ulen ind) { return Rec(states.ptr,groups.ptr,ind); } ;

        ulen g=0;

        auto func = [&] (PtrLen<ulen> list)
                        {
                         for(ulen ind : list ) next_groups[ind]=g;

                         g++;

                        } ;

        Algon::IncrSortThenApplyUniqueRangeBy(indexes,by,func);

        if( !Change(group_count,g) ) break;

        Printf(Con,"group count = #;\n",group_count);

        Swap(groups,next_groups);
       }

     Printf(Con,"final group count = #;\n",group_count);

     // final


    }

   ~BottomStateMachine() {}
 };

/* Main() */

void Main(StrLen file_name)
 {
  Lang::DataMap data(file_name);

  data.sanity();

  TopStateMachine top(data.getLang());

  BottomStateMachine bottom(top, [] (ulen) { return 0; } );
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     if( argc!=2 ) return 1;

     Main(argv[1]);

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

