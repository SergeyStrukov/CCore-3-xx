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

struct RedFinal1;

struct RedFinal2;

struct RedFinal3;

template <class T> class RefFinalList;

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

   PtrLen<const Lang::TypeDef::Final> getFinals() const { return finals; }

   ulen getAtomCount() const { return atom_count; }

   ulen getElementCount() const { return element_count; }
 };

/* class BottomStateMachine */

class BottomStateMachine : public StateMachine
 {
   DynArray<ulen> map;

  private:

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

  private:

   static void SetIf(ulen &dst,ulen ind)
    {
     if( dst==MaxULen ) dst=ind;
    }

   static void Set(DynArray<Trans> &trans,PtrLen<const Trans> top,const ulen maptop[])
    {
     auto tr=trans.extend_copy(top);

     for(auto &t : tr ) t.sindex=maptop[t.sindex];
    }

   void build(PtrLen<const State> top,PtrLen<const ulen> values,PtrLen<const ulen> groups,ulen group_count)
    {
     // map

     map.extend_copy(groups);

     auto st=states.extend_default(group_count);

     // section

     DynArray<ulen> section(DoFill(group_count),MaxULen);

     auto sect=Range(section);

     for(ulen i=0; i<groups.len ;i++)
       {
        ulen j=groups[i];

        SetIf(sect[j],i);
       }

     // states

     for(ulen i=0; i<st.len ;i++)
       {
        State &s=st[i];
        ulen j=sect[i];

        s.sindex=i;
        s.value=values[j];

        Set(s.trans,Range(top[j].trans),groups.ptr);
       }
    }

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

     Printf(Con,"final group count = #;\n\n",group_count);

     // final

     if( ulen g0=next_groups[0] )
       {
        for(ulen &g : next_groups )
          {
           if( g==0 ) g=g0;
           else if( g==g0 ) g=0;
          }
       }

     build(states,Range(new_value),next_groups,group_count);
    }

   ~BottomStateMachine() {}

   ulen mapTop(ulen top_sindex) const { return map[top_sindex]; }
 };

/* struct RedFinal1 */

struct RedFinal1 : CmpComparable<RedFinal1>
 {
  struct RedAction : CmpComparable<RedAction>
   {
    ulen a1index;
    ulen r1index;

    RedAction(ulen a1index_,ulen r1index_) : a1index(a1index_),r1index(r1index_) {}

    // cmp objects

    CmpResult objCmp(const RedAction &obj) const
     {
      return AlphaCmp(a1index,obj.a1index,r1index,obj.r1index);
     }
   };

  DynArray<RedAction> actions;
  ulen index = MaxULen ;

  explicit RedFinal1(const Lang::TypeDef::Final &final)
   {
    for(auto action : final.actions.getRange() )
      {
       if( +action.atom && !action.rule ) continue;

       ulen a1index = +action.atom ? action.atom->index : 0 ;
       ulen r1index = +action.rule ? action.rule->index : 0 ;

       actions.append_fill(a1index,r1index);
      }

    Sort(Range(actions));
   }

  // cmp objects

  CmpResult objCmp(const RedFinal1 &obj) const
   {
    return RangeCmp(Range(actions),Range(obj.actions));
   }
 };

/* struct RedFinal2 */

struct RedFinal2
 {
  DynArray<ulen> actions;
  ulen index = MaxULen ;

  explicit RedFinal2(const Lang::TypeDef::Final &final)
   {
    DynArray<ulen> temp;

    for(auto action : final.actions.getRange() )
      {
       if( !action.rule ) continue;

       ulen rindex = action.rule->index ;

       temp.append_fill(rindex);
      }

    Algon::SortThenApplyUnique(Range(temp), [&] (ulen rindex) { actions.append_copy(rindex); } );

    if( ulen len=actions.getLen() ; len>1 ) Printf(Con,"Multiple #;\n",len);
   }

  // cmp objects

  CmpResult objCmp(const RedFinal2 &obj) const
   {
    return RangeCmp(Range(actions),Range(obj.actions));
   }
 };

/* struct RedFinal3 */

struct RedFinal3
 {
  bool has_rule = false ;
  ulen index = MaxULen ;

  explicit RedFinal3(const Lang::TypeDef::Final &final)
   {
    for(auto action : final.actions.getRange() )
      {
       if( !action.rule ) continue;

       has_rule=true;

       break;
      }
   }

  // cmp objects

  CmpResult objCmp(const RedFinal3 &obj) const
   {
    return Cmp(has_rule,obj.has_rule);
   }
 };

/* class RefFinalList<T> */

template <class T>
class RefFinalList : NoCopy
 {
   DynArray<T> list;

   struct Rec : CmpComparable<Rec>
    {
     T *ptr;

     // cmp objects

     CmpResult objCmp(const Rec &obj) const
      {
       return Cmp(*ptr,*obj.ptr);
      }
    };

  public:

   explicit RefFinalList(PtrLen<const Lang::TypeDef::Final> finals)
    : list(DoCast(finals.len),finals.ptr)
    {
     auto r=Range(list);

     DynArray<Rec> temp(DoRaw(r.len));

     auto dst=temp.getPtr();

     for(; +r ;++r,++dst) dst->ptr=r.ptr;

     ulen index=0;

     Algon::SortThenApplyUniqueRange(Range(temp), [&] (PtrLen<Rec> list) { for(auto rec : list ) rec.ptr->index=index; index++; } );

     Printf(Con,"red final count = #;\n\n",index);
    }

   ~RefFinalList() {}

   ulen map(ulen findex) const { return list[findex].index; }

 };

/* CheckShift() */

void CheckShift(Lang::TypeDef::Final final,PtrLen<const Trans> trans,ulen atom_count)
 {
  for(auto action : final.actions.getRange() )
    {
     if( !action.atom || +action.rule ) continue;

     ulen aindex=action.atom->index;

     if( !trans )
       {
        Printf(Con,"CheckShift failed #; : #; null trans\n",final.index,aindex);

        return;
       }

     if( trans->eindex!=aindex )
       {
        Printf(Con,"CheckShift failed #; : #; != #;\n",final.index,aindex,trans->eindex);

        return;
       }

     ++trans;
    }

  if( +trans && trans->eindex<atom_count )
    {
     Printf(Con,"CheckShift failed #; : extra trans\n",final.index);
    }
 }

void CheckShift(const TopStateMachine &top,const BottomStateMachine &bottom)
 {
  auto states=top.getStates();
  auto finals=top.getFinals();
  auto bottom_states=bottom.getStates();

  for(ulen i=0; i<states.len ;i++)
    CheckShift(finals[states[i].value],Range(bottom_states[bottom.mapTop(i)].trans),top.getAtomCount());
 }

/* Main() */

void Main(StrLen file_name)
 {
  Lang::DataMap data(file_name);

  data.sanity();

  auto &lang=data.getLang();

  Printf(Con,"state count = #;\n",lang.states.len);
  Printf(Con,"final count = #;\n\n",lang.finals.len);

  TopStateMachine top(lang);

  Printf(Con,"--- Bottom ---\n\n");

  BottomStateMachine bottom(top, [] (ulen) { return 0; } );

  CheckShift(top,bottom);

  Printf(Con,"--- Bottom1 ---\n\n");

  RefFinalList<RedFinal1> redlist1(top.getFinals());

  BottomStateMachine bottom1(top, [&,states=top.getStates()] (ulen sindex) { return redlist1.map(states[sindex].value); } );

  Printf(Con,"--- Bottom2 ---\n\n");

  RefFinalList<RedFinal2> redlist2(top.getFinals());

  BottomStateMachine bottom2(top, [&,states=top.getStates()] (ulen sindex) { return redlist2.map(states[sindex].value); } );

  Printf(Con,"--- Bottom3 ---\n\n");

  RefFinalList<RedFinal3> redlist3(top.getFinals());

  BottomStateMachine bottom3(top, [&,states=top.getStates()] (ulen sindex) { return redlist3.map(states[sindex].value); } );
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

