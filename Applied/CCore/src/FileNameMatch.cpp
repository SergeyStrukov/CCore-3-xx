/* FileNameMatch.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/FileNameMatch.h>

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/NodeAllocator.h>
#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class FileNameFilter::State */

class FileNameFilter::State : public CmpComparable<State>
 {
   using Filter = PtrLen<const Char> ;

   Filter filter;
   DynArray<ulen> list;

  private:

   static bool IsFinal(Filter s)
    {
     for(Char ch : s ) if( ch!='*' ) return false;

     return true;
    }

   // all suffixes

   void suffixes(FuncArgType<Filter> func) const
    {
     Filter f=filter;

     list.apply( [f,func] (ulen len) { return func(f.suffix(len)); } );
    }

   // follow states

   static ulen Normalize(PtrLen<ulen> list)
    {
     IncrSort(list, [] (ulen a,ulen b) { return a>b; } );

     ulen *out=list.ptr;

     Algon::ApplyUniqueRange(list, [&out] (PtrLen<ulen> r) { *(out++)=(*r); } );

     return list.len-Dist(list.ptr,out);
    }

   void complete()
    {
     ulen delta=Normalize(Range(list));

     list.shrink(delta);

     list.shrink_extra();
    }

   void add(Filter s)
    {
     for(; +s ;++s)
       {
        switch( *s )
          {
           case '*' :
            {
             list.append_copy(s.len);
            }
           break;

           case '?' :
            {
             list.append_copy(s.len-1);
            }
           return;

           default: return;
          }
       }
    }

   explicit State(const State *obj)
    : filter(obj->filter),
      list(DoReserve,2*filter.len)
    {
     obj->suffixes( [this] (Filter s) { add(s); } );

     complete();
    }

   void add(Filter s,Char ch_)
    {
     for(; +s ;++s)
       {
        switch( Char ch=*s )
          {
           case '*' :
            {
             list.append_copy(s.len);
            }
           break;

           case '?' :
            {
             list.append_copy(s.len-1);
            }
           return;

           default:
            {
             if( ch==ch_ ) list.append_copy(s.len-1);
            }
           return;
          }
       }
    }

   State(const State *obj,Char ch)
    : filter(obj->filter),
      list(DoReserve,2*filter.len)
    {
     obj->suffixes( [this,ch] (Filter s) { add(s,ch); } );

     complete();
    }

  public:

   explicit State(Filter filter_)
    : filter(filter_),
      list(DoReserve,1)
    {
     list.append_copy(filter_.len);
    }

   ~State()
    {
    }

   // std move

   State(State &&obj) = default ;

   State & operator = (State &&obj) = default ;

   // methods

   bool isFinal() const
    {
     bool ret=false;

     suffixes( [&ret] (Filter s) -> bool
                      {
                       if( IsFinal(s) )
                         {
                          ret=true;

                          return false;
                         }

                       return true;

                      } );

     return ret;
    }

   void follow(Char buf[],FuncArgType<Char,State &> char_func,FuncArgType<State &> other_func) const // buf.len == filter.len
    {
     bool other=false;

     Char *temp=buf;

     suffixes( [&other,&temp] (Filter s)
                              {
                               if( +s )
                                 {
                                  Char ch=*s;

                                  if( ch=='*' || ch=='?' )
                                    {
                                     if( ch=='*' )
                                       {
                                        for(++s; +s && *s=='*' ;++s);

                                        if( +s )
                                          {
                                           Char ch=*s;

                                           if( ch!='?' ) *(temp++)=ch;
                                          }
                                       }

                                     other=true;
                                    }
                                  else
                                    {
                                     *(temp++)=ch;
                                    }
                                 }

                              } );

     Algon::SortThenApplyUnique(Range(buf,temp), [this,char_func] (Char ch)
                                                                  {
                                                                   State state(this,ch);

                                                                   char_func(ch,state);

                                                                  } );

     if( other )
       {
        State state(this);

        other_func(state);
       }
    }

   // cmp objects

   CmpResult objCmp(const State &obj) const
    {
     return RangeCmpOf(list,obj.list);
    }
 };

/* struct FileNameFilter::StateArrow */

struct FileNameFilter::StateArrow
 {
  Char ch;
  FullState *state;

  StateArrow(Char ch_,FullState *state_) : ch(ch_),state(state_) {}
 };

/* class FileNameFilter::FullState */

class FileNameFilter::FullState : NoCopy
 {
  private:

   State state;

   // ext

   ulen index = 0 ;
   DynArray<StateArrow> arrows;
   FullState *other = 0 ;

  public:

   explicit FullState(State &state_) : state(std::move(state_)) {}

   ~FullState() {}

   // get

   const State & getState() const { return state; }

   ulen getIndex() const { return index; }

   const FullState * getOther() const { return other; }

   PtrLen<const StateArrow> getArrows() const { return Range(arrows); }

   // set

   void setIndex(ulen index_) { index=index_; }

   void setOther(FullState *other_) { other=other_; }

   void addArrow(Char ch,FullState *state) { arrows.append_fill(ch,state); }

   // Cmp()

   friend CmpResult Cmp(const State *a,const FullState &b) { return Cmp(*a,b.getState()); }
 };

/* class FileNameFilter::StateMap */

class FileNameFilter::StateMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     RBTreeLink<Node,FullState> link;

     explicit Node(State &state) : link(state) {}
    };

   using Algo = RBTreeLink<Node,FullState>::Algo<&Node::link,const State *,NoCopyKey> ;

   ulen max_states;

   Algo::Root root;

   NodePoolAllocator<Node> allocator;

  private:

   void destroy(Node *node)
    {
     if( node )
       {
        destroy(Algo::Link(node).lo);
        destroy(Algo::Link(node).hi);

        allocator.free_nonnull(node);
       }
    }

  public:

   explicit StateMap(ulen max_states_)
    : max_states(max_states_)
    {
    }

   ~StateMap()
    {
     destroy(root.root);
    }

   struct Result
    {
     FullState *obj;
     bool new_flag;

     Result(FullState *obj_,bool new_flag_) : obj(obj_),new_flag(new_flag_) {}

     operator FullState * () const { return obj; }
    };

   Result find_or_add(State &obj)
    {
     typename Algo::PrepareIns prepare(root,&obj);

     if( Node *node=prepare.found ) return Result(&Algo::Link(node).key,false);

     if( allocator.getCount()>=max_states )
       {
        Printf(Exception,"CCore::FileNameFilter::StateMap::find_or_add(...) : too many states");
       }

     Node *node=allocator.alloc(obj);

     prepare.complete(node);

     return Result(&Algo::Link(node).key,true);
    }
 };

/* class FileNameFilter::IndState::Arrow */

FileNameFilter::IndState::Arrow::Arrow(const StateArrow &obj)
 {
  ch=obj.ch;
  index=obj.state->getIndex();
 }

/* class FileNameFilter::IndState */

FileNameFilter::IndState::IndState(const FullState *state)
 {
  if( const FullState *other=state->getOther() ) other_index=other->getIndex();

  arrows.extend_cast(state->getArrows());

  is_final=state->getState().isFinal();
 }

 // methods

ulen FileNameFilter::IndState::next(Char ch) const
 {
  for(Arrow arr : arrows ) if( arr.ch==ch ) return arr.index;

  return other_index;
 }

/* class FileNameFilter */

void FileNameFilter::build(StrLen filter_,ulen max_states)
 {
  StateMap map(max_states);
  DynArray<FullState *> list;

#ifdef CCORE_UTF8

  DynArray<Char> buf(DoReserve,filter_.len);

  while( +filter_ )
    {
     Unicode ch=CutUtf8_unicode(filter_);

     if( ch==Unicode(-1) ) GuardUtf8Broken("CCore::FileNameFilter::build(...)");

     buf.append_copy(ch);
    }

  auto filter=Range(buf);

#else

  StrLen filter=filter_;

#endif

  {
   State first(filter);

   list.append_copy(map.find_or_add(first));
  }

  TempArray<Char,1024> temp(filter.len);

  for(ulen index=0; index<list.getLen() ;index++)
    {
     FullState *state=list[index];

     state->setIndex(index);

     auto char_func = [&map,&list,state] (Char ch,State &next_state)
                                         {
                                          auto result=map.find_or_add(next_state);

                                          if( result.new_flag ) list.append_copy(result);

                                          state->addArrow(ch,result);
                                         } ;

     auto other_func = [&map,&list,state] (State &next_state)
                                          {
                                           auto result=map.find_or_add(next_state);

                                           if( result.new_flag ) list.append_copy(result);

                                           state->setOther(result);
                                          } ;

     state->getState().follow(temp.getPtr(),char_func,other_func);
    }

  states.extend_cast(Range_const(list));
 }

FileNameFilter::FileNameFilter() noexcept
 {
 }

FileNameFilter::FileNameFilter(StrLen filter,ulen max_states)
 {
  build(filter,max_states);
 }

FileNameFilter::~FileNameFilter()
 {
 }

void FileNameFilter::reset()
 {
  states.erase();
 }

void FileNameFilter::reset(StrLen filter,ulen max_states)
 {
  states.erase();

  build(filter,max_states);
 }

bool FileNameFilter::operator () (StrLen file) const
 {
  if( !states.getLen() ) return false;

  auto *ptr=states.getPtr();

  ulen index=0;

  while( +file )
    {
     Char ch=CutChar(file);

     ulen next=ptr[index].next(ch);

     if( next==MaxULen ) return false;

     index=next;
    }

  return ptr[index].isFinal();
 }

} // namespace CCore

