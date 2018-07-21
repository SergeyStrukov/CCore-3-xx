/* BookLab.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/BookLab.h>

#include <CCore/inc/CompactList.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>

#include <CCore/inc/video/PrintDDL.h>

namespace App {
namespace BookLab {

/* test() */

#if 0

template <class T>
void testOne(ObjectDomain *domain)
 {
  static_assert( Has_keepAlive<T> ,"has keepAlive");

  ExtObjPtr<T> test(domain);
 }

template <class ... TT>
void testList(ObjectDomain *domain)
 {
  ( testOne<TT>(domain) , ... );
 }

void test(ObjectDomain *domain)
 {
  testList<Font,Format,SingleLine,DoubleLine,Frame,FrameList,Page,Element,ElementList,Defaults,
           Scope,Section,Bitmap,Collapse,Item,ItemList,TextList,Border,Cell,Table,Link,Span,TextLine,
           FixedText,OneLine,MultiLine,Text>(domain);
 }

#endif

/* struct LastDefaults */

LastDefaults::LastDefaults(ObjectDomain &domain)
 {
  singleLine.create(domain);
  doubleLine.create(domain);
  collapseFormat.create(domain);
  bulletFormat.create(domain);
  border.create(domain);
  textFormat.create(domain);
  fixedFormat.create(domain);
  placement.create<MultiLine>(domain);
 }

/* struct Doc */

Doc::Doc(ObjectDomain &domain)
 : lastdefs(domain)
 {
 }

/* class NextIndex */

Index NextIndex::getIndex()
 {
  unsigned ret=next_index;

  if( !ret )
    {
     Printf(Exception,"App::BookLab::NextIndex::getIndex() : too many objects");
    }

  next_index++;

  return {ret};
 }

/* class Book::ScopeContext */

class Book::ScopeContext : NoCopy
 {
   unsigned level = 100 ;

  private:

   void subs(IntAnyObjPtr<Scope,Doc> scope,Page *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Scope *ptr)
    {
     set(scope,ptr->defs);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,Font *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Format *ptr)
    {
     set(scope,ptr->font);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,SingleLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc>,DoubleLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Section *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,Bitmap *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Collapse *ptr)
    {
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,TextList *ptr)
    {
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,Border *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Cell *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Table *ptr)
    {
     set(scope,ptr->border);

     for(NamedPtr<Cell> &obj : ptr->table ) set(scope,obj);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Text *ptr)
    {
     set(scope,ptr->placement);
     set(scope,ptr->format);

     for(Span &span : ptr->list ) set(scope,span);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,OneLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc>,MultiLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,FixedText *ptr)
    {
     set(scope,ptr->format);

     for(TextLine &line : ptr->list ) set(scope,line);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Link *ptr)
    {
     set(scope,ptr->page);
    }

  private:

   template <class T>
   void set(IntAnyObjPtr<Scope,Doc> scope,T *ptr)
    {
     LockUse lock(level);

     ptr->scope=scope;

     subs(scope,ptr);
    }

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *obj) { if( obj ) set(scope,obj); } );
    }

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,NamedPtr<TT...> &ptr)
    {
     if( ptr.isAnonym() ) set(scope,ptr.ptr.getPtr());
    }

   template <class T>
   void set(IntAnyObjPtr<Scope,Doc> scope,IntObjPtr<T> ptr)
    {
     if( +ptr ) set(scope,ptr.getPtr());
    }

   struct GetScopeFunc
    {
     IntAnyObjPtr<Scope,Doc> &ret;

     template <class T>
     void operator () (IntObjPtr<T>) {}

     void operator () (IntObjPtr<Scope> ptr) { ret=ptr; }
    };

   template <class ... TT>
   static IntAnyObjPtr<Scope,Doc> GetScope(IntAnyObjPtr<TT...> ptr)
    {
     IntAnyObjPtr<Scope,Doc> ret;

     ptr.apply( GetScopeFunc{ret} );

     return ret;
    }

   template <class ... TT>
   struct SetAnyFunc
    {
     ScopeContext *ctx;
     IntAnyObjPtr<Scope,Doc> scope;
     IntAnyObjPtr<TT...> ptr;

     SetAnyFunc(ScopeContext *ctx_,IntAnyObjPtr<Scope,Doc> scope_,IntAnyObjPtr<TT...> ptr_) : ctx(ctx_),scope(scope_),ptr(ptr_) {}

     void operator () (auto *obj) { if( obj ) ctx->set(scope,obj); }

     void operator () (Scope *obj) { if( obj ) ctx->set(GetScope(ptr),obj); }
    };

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,IntAnyObjPtr<TT...> ptr)
    {
     SetAnyFunc func(this,scope,ptr);

     ptr.getPtr().apply( func );
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Defaults &defs)
    {
     set(scope,defs.singleLine);
     set(scope,defs.doubleLine);
     set(scope,defs.collapseFormat);
     set(scope,defs.bulletFormat);
     set(scope,defs.border);
     set(scope,defs.textFormat);
     set(scope,defs.fixedFormat);
     set(scope,defs.placement);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,ElementList &list)
    {
     for(Element *ptr=SafePtr(list.beg); ptr ;ptr=SafePtr(ptr->next))
       {
        set(scope,ptr->ptr);
       }
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,FrameList &list)
    {
     for(Frame *ptr=SafePtr(list.beg); ptr ;ptr=SafePtr(ptr->next))
       {
        set(scope,ptr->line);
        set(scope,ptr->body);
       }
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,ItemList &list)
    {
     for(Item *ptr=SafePtr(list.beg); ptr ;ptr=SafePtr(ptr->next))
       {
        set(scope,ptr->list);
       }
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Span &span)
    {
     set(scope,span.format);
     set(scope,span.ref);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,TextLine &line)
    {
     for(Span &span : line.list ) set(scope,span);
    }

  public:

   ScopeContext() {}

   void set(IntObjPtr<Doc> ptr)
    {
     set(ptr,ptr->start);
     set(ptr,ptr->defs);
     set(ptr,ptr->list);
    }
 };

/* class Book */

void Book::setScope()
 {
  if( +doc )
    {
     ScopeContext ctx;

     ctx.set(doc);
    }
 }

Book::Book()
 {
 }

Book::~Book()
 {
 }

void Book::blank()
 {
  doc=Null;
  linked=true;

  domain.collect();
 }

ErrorText Book::link(PtrLen<char> ebuf) // TODO
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     Printf(Exception,"not implemented");

     return Success;
    }
  catch(CatchType)
    {
     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

