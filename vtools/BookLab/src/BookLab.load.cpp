/* BookLab.load.cpp */
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

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Exception.h>

namespace App {
namespace BookLab {

#include "BookLab.TypeDef.gen.h"
#include "BookLab.TypeSet.gen.h"

/* struct Book::LoadType<T> */

template <>
struct Book::LoadType<TypeDef::OneLine> : Meta::DefType<OneLine> {};

template <>
struct Book::LoadType<TypeDef::MultiLine> : Meta::DefType<MultiLine> {};

#if 0

template <>
struct Book::LoadType<TypeDef::> : Meta::DefType<> {};

#endif

/* class Book::LoadContext */

class Book::LoadContext : NoCopy
 {
   ObjectDomain &domain;

   unsigned level = 100 ;

  private:

   template <OneOfTypes<VColor,Coord,Effect,Align,bool,int> T,class S>
   static void Cast(T &ret,S obj)
    {
     ret=T(obj);
    }

   template <class S>
   static void Cast(Point &ret,S obj)
    {
     Cast(ret.x,obj.x);
     Cast(ret.y,obj.y);
    }

   template <class S>
   static void Cast(Ratio &ret,S obj)
    {
     Cast(ret.a,obj.a);
     Cast(ret.b,obj.b);
    }

   template <class T,auto Def,class S>
   static void Cast(OptData<T,Def> &ret,const S &obj)
    {
     Cast(ret.data,obj.data);

     ret.def=obj.def;
    }

  private:

   void init(Page *ret,const TypeDef::Page *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     ret->title=String(ptr->title);
     Cast(ret->back,ptr->back);
     Cast(ret->fore,ptr->fore);

     cast(ret->up,ptr->up);
     cast(ret->prev,ptr->prev);
     cast(ret->next,ptr->next);

     cast(ret->list,ptr->list);
    }

   void init(SingleLine *ret,const TypeDef::SingleLine *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->width,ptr->width);
     Cast(ret->line,ptr->line);
    }

   void init(DoubleLine *ret,const TypeDef::DoubleLine *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->width,ptr->width);
     Cast(ret->gray,ptr->gray);
     Cast(ret->snow,ptr->snow);
    }

   void init(Format *ret,const TypeDef::Format *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->back,ptr->back);
     Cast(ret->fore,ptr->fore);
     Cast(ret->effect,ptr->effect);

     cast(ret->font,ptr->font);
    }

   void init(Border *ret,const TypeDef::Border *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->space,ptr->space);
     Cast(ret->width,ptr->width);
     Cast(ret->line,ptr->line);
    }

   void init(OneLine *ret,const TypeDef::OneLine *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->align,ptr->align);
    }

   void init(MultiLine *ret,const TypeDef::MultiLine *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     Cast(ret->line_space,ptr->line_space);
     Cast(ret->first_line_space,ptr->first_line_space);
    }

   void init(Font *ret,const TypeDef::Font *ptr)
    {
     ret->name=String(ptr->name);
     ret->open=ptr->open;

     ret->face=String(ptr->face);

     Cast(ret->size,ptr->size);
     Cast(ret->bold,ptr->bold);
     Cast(ret->italic,ptr->italic);
     Cast(ret->strength,ptr->strength);
    }

   template <class T,class S>
   void create(IntObjPtr<T> &ret,const S &ptr)
    {
     if( +ptr )
       {
        LockUse lock(level);

        ret.create(domain);

        init(ret.getPtr(),ptr.getPtr());
       }
    }

   template <class S,class ... TT>
   void createPtr(IntAnyObjPtr<TT...> &ret,const S *ptr)
    {
     using T=typename LoadType<S>::Ret;

     if( +ptr )
       {
        LockUse lock(level);

        ExtObjPtr<T> temp(domain);

        ret=temp;

        init(temp.getPtr(),ptr);
       }
    }

   template <class S,class ... TT>
   void create(IntAnyObjPtr<TT...> &ret,const S &ptr)
    {
     auto anyptr=ptr.getPtr();

     anyptr.apply( [&] (auto *objptr) { createPtr(ret,objptr); } );
    }

  private:

   template <class T,class S>
   void cast(NamedPtr<T> &ret,const S &obj)
    {
     ret.name=String(obj.name);

     create(ret.ptr,obj.ptr);
    }

   void cast(FrameList &ret,const TypeDef::FrameList &obj) // TODO
    {
     Used(ret);
     Used(obj);
    }

   void cast(ElementList &ret,PtrLen<TypeDef::Element> list) // TODO
    {
     Used(ret);
     Used(list);
    }

   void cast(Defaults &ret,const TypeDef::Defaults &obj)
    {
     Cast(ret.inner,obj.inner);
     Cast(ret.outer,obj.outer);
     Cast(ret.bulletSpace,obj.bulletSpace);
     Cast(ret.itemSpace,obj.itemSpace);

     create(ret.singleLine,obj.singleLine);
     create(ret.doubleLine,obj.doubleLine);
     create(ret.collapseFormat,obj.collapseFormat);
     create(ret.bulletFormat,obj.bulletFormat);
     create(ret.border,obj.border);
     create(ret.textFormat,obj.textFormat);
     create(ret.fixedFormat,obj.fixedFormat);
     create(ret.placement,obj.placement);
    }

  public:

   explicit LoadContext(ObjectDomain &domain_) : domain(domain_) {}

   ExtObjPtr<Doc> process(const TypeDef::Doc *doc)
    {
     ExtObjPtr<Doc> ret(domain,domain);

     ret->title=String(doc->title);
     Cast(ret->back,doc->back);
     Cast(ret->fore,doc->fore);

     cast(ret->start,doc->start);
     cast(ret->defs,doc->defs);
     cast(ret->list,doc->list);

     return ret;
    }
 };

/* class Book */

StrLen Book::Pretext()
 {
  return

#include "BookLab.Pretext.gen.h"

  ""_c;
 }

ErrorText Book::load(StrLen file_name,PtrLen<char> ebuf)
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     DDL::FileEngine<FileName,FileToMem> engine(eout);

     auto result=engine.process(file_name,Pretext());

     if( !result )
       {
        return eout.close();
       }

     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     if( TypeDef::Doc *doc_=map.findConst<TypeDef::Doc>("Data"_c) )
       {
        LoadContext ctx(domain);

        doc=ctx.process(doc_);

        linked=false;
       }

     return Success;
    }
  catch(CatchType)
    {
     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

