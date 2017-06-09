/* LangDataMap.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied CondLangLR1
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_lang_LangDataMap_h
#define CCore_inc_lang_LangDataMap_h

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace CCore {
namespace Lang {

/* TypeDef */

#include <CCore/inc/lang/LangData.TypeDef.gen.h>

/* classes */

class DataMap;

/* class DataMap */

class DataMap : NoCopy
 {
   void *mem;

   TypeDef::Lang lang;

  private:

   static StrLen Pretext();

   template <class T>
   static bool Checkin(T *ptr,PtrLen<T> range);

   template <class T>
   static bool Checkin_null(T *ptr,PtrLen<T> range);

   void sanity_atoms();
   void sanity_synts();
   void sanity_lang();
   void sanity_rules();
   void sanity_top_rules();
   void sanity_states();
   void sanity_finals();

   void load(StrLen file_name,PrintBase &eout);

  public:

   explicit DataMap(StrLen file_name);

   DataMap(StrLen file_name,PrintBase &eout);

   ~DataMap();

   const TypeDef::Lang & getLang() const { return lang; }

   void sanity();

   // generator support

   void atoms(FuncArgType<ulen,StrLen> func) const // func(1-based atom index,StrLen name)
    {
     for(const TypeDef::Atom &atom : lang.atoms.getRange() )
       {
        func(atom.index+1,atom.name.getStr());
       }
    }

   class ArgList
    {
      PtrLen<const TypeDef::Rule::Arg> args;

     public:

      explicit ArgList(const TypeDef::Rule &rule) : args(rule.args.getRange()) {}

      template <FuncArgType<bool,StrLen> Func>
      void operator () (Func func) const // func(bool is_atom,StrLen name)
       {
        for(TypeDef::Rule::Arg arg : args )
          {
           struct SplitArg
            {
             Func func;

             void operator () (TypeDef::Synt *synt)
              {
               func(false,synt->name.getStr());
              }

             void operator () (TypeDef::Atom *atom)
              {
               func(true,atom->name.getStr());
              }
            };

           arg.getPtr().apply(SplitArg{func});
          }
       }
    };

   class RuleList
    {
      PtrLen<const DDL::MapPtr<TypeDef::Rule> > rules;

     public:

      explicit RuleList(const TypeDef::Synt &synt) : rules(synt.rules.getRange()) {}

      void operator () (FuncArgType<StrLen,ArgList> func) const // func(StrLen rule_name,ArgList arg_list)
       {
        for(const TypeDef::Rule *rule : rules )
          {
           func(rule->name.getStr(),ArgList(*rule));
          }
       }
    };

   void synts(FuncArgType<StrLen,RuleList> func) const // func(StrLen name,RuleList rule_list)
    {
     for(const TypeDef::Synt &synt : lang.synts.getRange() )
       {
        func(synt.name.getStr(),RuleList(synt));
       }
    }

   void rules(FuncArgType<ulen,StrLen,StrLen,ulen> func) const // func(1-based rule index,StrLen synt_name,StrLen rule_name,1-based element index)
    {
     for(const TypeDef::Rule &rule : lang.rules.getRange() )
       {
        auto synt_name=rule.result->synt->name.getStr();
        auto rule_name=rule.name.getStr();

        func(rule.index+1,synt_name,rule_name,rule.result->element->index+1);
       }
    }

   class ActionList
    {
      PtrLen<const TypeDef::Final::Action> actions;

     public:

      explicit ActionList(const TypeDef::Final &final) : actions(final.actions.getRange()) {}

      void operator () (FuncArgType<ulen,ulen> func) const // func(1-based atom index OR 0,1-based rule index OR 0)
       {
        for(const TypeDef::Final::Action &action : actions )
          {
           TypeDef::AtomIndex atom=0;

           if( action.atom ) atom=action.atom->index+1;

           TypeDef::RuleIndex rule=0;

           if( action.rule ) rule=action.rule->index+1;

           func(atom,rule);
          }
       }
    };

   void finals(FuncArgType<ulen,ActionList> func) const// func(0-based final index,ActionList action_list)
    {
     for(const TypeDef::Final &final : lang.finals.getRange() )
       {
        func(final.index,ActionList(final));
       }
    }

   class TransList
    {
      PtrLen<const TypeDef::State::Transition> transitions;

     public:

      explicit TransList(const TypeDef::State &state) : transitions(state.transitions.getRange()) {}

      bool operator + () const { return transitions.len; }

      bool operator ! () const { return !transitions.len; }

      void operator () (FuncArgType<ulen,ulen> func) const // func(1-based element index,0-based state index)
       {
        for(const TypeDef::State::Transition &t : transitions )
          {
           func(t.element->index+1,t.state->index);
          }
       }
    };

   ulen getStatesCount() const { return lang.states.len; }

   void states(FuncArgType<ulen,ulen,TransList> func) const// func(0-based state index,0-based final index,TransList trans_list)
    {
     for(const TypeDef::State &state : lang.states.getRange() )
       {
        func(state.index,state.final->index,TransList(state));
       }
    }
 };

} // namespace Lang
} // namespace CCore

#endif

