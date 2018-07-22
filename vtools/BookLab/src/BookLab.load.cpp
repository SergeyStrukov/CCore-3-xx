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
struct Book::LoadType<TypeDef::Font> : Meta::DefType<Font> {};

template <>
struct Book::LoadType<TypeDef::Format> : Meta::DefType<Format> {};

template <>
struct Book::LoadType<TypeDef::SingleLine> : Meta::DefType<SingleLine> {};

template <>
struct Book::LoadType<TypeDef::DoubleLine> : Meta::DefType<DoubleLine> {};

template <>
struct Book::LoadType<TypeDef::Page> : Meta::DefType<Page> {};

template <>
struct Book::LoadType<TypeDef::Scope> : Meta::DefType<Scope> {};

template <>
struct Book::LoadType<TypeDef::Section> : Meta::DefType<Section> {};

template <>
struct Book::LoadType<TypeDef::Bitmap> : Meta::DefType<Bitmap> {};

template <>
struct Book::LoadType<TypeDef::Collapse> : Meta::DefType<Collapse> {};

template <>
struct Book::LoadType<TypeDef::TextList> : Meta::DefType<TextList> {};

template <>
struct Book::LoadType<TypeDef::Table> : Meta::DefType<Table> {};

template <>
struct Book::LoadType<TypeDef::Link> : Meta::DefType<Link> {};

template <>
struct Book::LoadType<TypeDef::FixedText> : Meta::DefType<FixedText> {};

template <>
struct Book::LoadType<TypeDef::OneLine> : Meta::DefType<OneLine> {};

template <>
struct Book::LoadType<TypeDef::MultiLine> : Meta::DefType<MultiLine> {};

template <>
struct Book::LoadType<TypeDef::Text> : Meta::DefType<Text> {};

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

   template <OneOfTypes<VColor,Coord,Effect,Align,bool,int,ulen,String> T,class S>
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

   template <class T,class S>
   static void Cast(DynArray<T> &ret,const S &obj)
    {
     auto r=obj.getRange();

     auto *out=ret.extend_default(r.len).ptr;

     for(ulen i : IndLim(r.len) ) Cast(out[i],r[i]);
    }

  private:

   void init(Font *ret,const TypeDef::Font *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->face,ptr->face);
     Cast(ret->size,ptr->size);
     Cast(ret->bold,ptr->bold);
     Cast(ret->italic,ptr->italic);
     Cast(ret->strength,ptr->strength);
    }

   void init(Format *ret,const TypeDef::Format *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->back,ptr->back);
     Cast(ret->fore,ptr->fore);
     Cast(ret->effect,ptr->effect);

     cast(ret->font,ptr->font);
    }

   void init(SingleLine *ret,const TypeDef::SingleLine *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->width,ptr->width);
     Cast(ret->line,ptr->line);
    }

   void init(DoubleLine *ret,const TypeDef::DoubleLine *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->width,ptr->width);
     Cast(ret->gray,ptr->gray);
     Cast(ret->snow,ptr->snow);
    }

   void init(Frame *ret,const TypeDef::Frame &obj)
    {
     Cast(ret->inner,obj.inner);
     Cast(ret->outer,obj.outer);
     Cast(ret->col,obj.col);

     cast(ret->line,obj.line);
     cast(ret->body,obj.body);
    }

   void init(Page *ret,const TypeDef::Page *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->title,ptr->title);
     Cast(ret->back,ptr->back);
     Cast(ret->fore,ptr->fore);

     Cast(ret->up.name,ptr->up.name);
     Cast(ret->prev.name,ptr->prev.name);
     Cast(ret->next.name,ptr->next.name);

     cast(ret->list,ptr->list);
    }

   void init(Element *ret,const TypeDef::Element &obj)
    {
     create(ret->ptr,obj);
    }

   void init(Scope *ret,const TypeDef::Scope *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     cast(ret->defs,ptr->defs);
     cast(ret->list,ptr->list);
    }

   void init(Section *ret,const TypeDef::Section *ptr)
    {
     Cast(ret->open,ptr->open);

     Cast(ret->comment,ptr->comment);

     cast(ret->list,ptr->list);
    }

   void init(Bitmap *ret,const TypeDef::Bitmap *ptr)
    {
     Cast(ret->name,ptr->name);

     Cast(ret->file_name,ptr->file_name);
    }

   void init(Collapse *ret,const TypeDef::Collapse *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->title,ptr->title);
     Cast(ret->openlist,ptr->openlist);
     Cast(ret->hide,ptr->hide);

     cast(ret->format,ptr->format);
     cast(ret->list,ptr->list);
    }

   void init(Item *ret,const TypeDef::Item &obj)
    {
     Cast(ret->bullet,obj.bullet);

     cast(ret->list,obj.list);
    }

   void init(TextList *ret,const TypeDef::TextList *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->bullet_space,ptr->bullet_space);
     Cast(ret->item_space,ptr->item_space);

     cast(ret->format,ptr->format);
     cast(ret->list,ptr->list);
    }

   void init(Border *ret,const TypeDef::Border *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->space,ptr->space);
     Cast(ret->width,ptr->width);
     Cast(ret->line,ptr->line);
    }

   void init(Cell *ret,const TypeDef::Cell *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->span_x,ptr->span_x);
     Cast(ret->span_y,ptr->span_y);

     cast(ret->list,ptr->list);
    }

   void init(Table *ret,const TypeDef::Table *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->hard,ptr->hard);
     Cast(ret->width,ptr->width);

     cast(ret->border,ptr->border);
     cast(ret->table,ptr->table);
    }

   void init(Link *ret,const TypeDef::Link *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->index_list,ptr->index_list);

     cast(ret->page,ptr->page);
    }

   void init(FixedText *ret,const TypeDef::FixedText *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     cast(ret->format,ptr->format);
     cast(ret->list,ptr->list);
    }

   void init(OneLine *ret,const TypeDef::OneLine *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->align,ptr->align);
    }

   void init(MultiLine *ret,const TypeDef::MultiLine *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     Cast(ret->line_space,ptr->line_space);
     Cast(ret->first_line_space,ptr->first_line_space);
    }

   void init(Text *ret,const TypeDef::Text *ptr)
    {
     Cast(ret->name,ptr->name);
     Cast(ret->open,ptr->open);

     cast(ret->placement,ptr->placement);
     cast(ret->format,ptr->format);
     cast(ret->list,ptr->list);
    }

  private:

   template <class T,class S>
   void create(IntObjPtr<T> &ret,const S &obj)
    {
     if( +obj )
       {
        LockUse lock(level);

        ret.create(domain);

        init(ret.getPtr(),obj.getPtr());
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
   void create(IntAnyObjPtr<TT...> &ret,const S &obj)
    {
     auto anyptr=obj.getPtr();

     anyptr.apply( [&] (auto *ptr) { createPtr(ret,ptr); } );
    }

  private:

   template <class T,class S>
   void cast(DynArray<T> &ret,const S &obj)
    {
     auto r=obj.getRange();

     auto *out=ret.extend_default(r.len).ptr;

     for(ulen i : IndLim(r.len) ) cast(out[i],r[i]);
    }

   template <class S,class ... TT>
   void cast(NamedPtr<TT...> &ret,const S &obj)
    {
     Cast(ret.name,obj.name);

     if( !Range(ret.name) ) create(ret.ptr,obj.ptr);
    }

   template <class List,class T>
   static void InsList(List &ret,T &elem)
    {
     if( !ret.end )
       {
        ret.beg=elem;
        ret.end=elem;
       }
     else
       {
        ret.end->next=elem;
        elem->prev=ret.end;

        ret.end=elem;
       }
    }

   void cast(FrameList &ret,const TypeDef::FrameList &obj)
    {
     LockUse lock(level);

     auto list=obj.list.getRange();

     for(ulen i : IndLim(list.len) )
       {
        ExtObjPtr<Frame> elem(domain);

        init(elem.getPtr(),list[i]);

        InsList(ret,elem);

        if( i==obj.cur ) ret.cur=elem;
       }
    }

   void cast(ItemList &ret,const TypeDef::ItemList &obj)
    {
     LockUse lock(level);

     auto list=obj.list.getRange();

     for(ulen i : IndLim(list.len) )
       {
        ExtObjPtr<Item> elem(domain);

        init(elem.getPtr(),list[i]);

        InsList(ret,elem);

        if( i==obj.cur ) ret.cur=elem;
       }
    }

   void cast(ElementList &ret,PtrLen<TypeDef::Element> list)
    {
     LockUse lock(level);

     for(const auto &obj : list )
       {
        ExtObjPtr<Element> elem(domain);

        init(elem.getPtr(),obj);

        InsList(ret,elem);
       }
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

   void cast(Span &ret,const TypeDef::Span &obj)
    {
     Cast(ret.body,obj.body);
     cast(ret.format,obj.format);
     cast(ret.ref,obj.ref);
    }

   void cast(TextLine &ret,const TypeDef::TextLine &obj)
    {
     cast(ret.list,obj);
    }

  public:

   explicit LoadContext(ObjectDomain &domain_) : domain(domain_) {}

   ExtObjPtr<Doc> process(const TypeDef::Doc *doc)
    {
     ExtObjPtr<Doc> ret(domain,domain);

     Cast(ret->title,doc->title);
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

        setScope();

        linked=false;
       }

     return Success;
    }
  catch(CatchType)
    {
     blank();

     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

