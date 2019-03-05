/* BookLab.book.cpp */
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

/* namespace BookAdapter */

namespace BookAdapter {

template <class T>
struct Adapter
 {
  const T &data;

  explicit Adapter(const T &obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,data);
   }
 };

template <>
struct Adapter<Index>
 {
  Index data;

  explicit Adapter(Index obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Printf(out,"ANONYM#;",data.index);
   }
 };

template <OneOfTypes<StrLen,Coord,Strength,ulen> T>
struct Adapter<T>
 {
  T data;

  explicit Adapter(T obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,data);
   }
 };

template <>
struct Adapter<bool>
 {
  bool data;

  explicit Adapter(bool obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,DDLBool(data));
   }
 };

template <>
struct Adapter<Effect>
 {
  Effect data;

  explicit Adapter(Effect obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,(uint8)data);
   }
 };

template <>
struct Adapter<Align>
 {
  Align data;

  explicit Adapter(Align obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,(uint8)data);
   }
 };

template <>
struct Adapter<VColor>
 {
  VColor data;

  explicit Adapter(VColor obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    if( data==NoColor )
      Putobj(out,"NoColor"_c);
    else
      Printf(out,"0#.h;",(uint32)data);
   }
 };

template <>
struct Adapter<Point>
 {
  Point data;

  explicit Adapter(Point obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",data.x,data.y);
   }
 };

template <>
struct Adapter<Ratio>
 {
  Ratio data;

  explicit Adapter(Ratio obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",data.a,data.b);
   }
 };

} // namespace BookAdapter

/* class Book::BookContext */

template <class T>
concept bool NameType = OneOfTypes<T,StrLen,Index> ;

class Book::BookContext : NextIndex
 {
   PrintBase &out;

   struct Rec
    {
     Index index;
     AnyPtr<Font,Format,SingleLine,DoubleLine,Page,Scope,Bitmap,Collapse,TextList,
            Border,Cell,Table,Link,FixedText,OneLine,MultiLine,Text> ptr;
    };

   CompactList2<Rec> list;

  private:

   template <class ... TT>
   static void AdaptPrintf(PrintBase &out,const char *format,const TT & ... tt)
    {
     Printf(out,format,BookAdapter::Adapter<TT>(tt)...);
    }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     AdaptPrintf(out,format,tt...);
    }

   void putstr(StrLen text)
    {
     Putobj(out,text);
    }

   template <class T>
   struct OptDef
    {
     OptDataBase<T> data;
     StrLen def;

     OptDef(OptDataBase<T> data_,StrLen def_) : data(data_),def(def_) {}

     void print(PrinterType &out) const
      {
       if( data.def )
         {
          Putobj(out,def);
         }
       else
         {
          AdaptPrintf(out,"#;",data.data);
         }
      }
    };

   static bool IsAbs(StrLen name) { return +name && *name=='#' ; }

   template <class ... TT>
   struct Named
    {
     BookContext *ctx;
     NamedPtr<TT...> ptr;
     StrLen def;

     Named(BookContext *ctx_,NamedPtr<TT...> ptr_,StrLen def_="null"_c) : ctx(ctx_),ptr(ptr_),def(def_) {}

     void print(PrinterType &out) const
      {
       if( ptr.hasName() )
         {
          StrLen name=Range(ptr.name);

          if( IsAbs(name) )
            {
             AdaptPrintf(out,"& ##Doc#;",name);
            }
          else
            {
             AdaptPrintf(out,"& #;",name);
            }
         }
       else if( ptr.hasObj() )
         {
          Index index=ctx->getIndex();

          AdaptPrintf(out,"& #;",index);

          ctx->addAnonym(index,ptr.ptr.getPtr());
         }
       else
         {
          Putobj(out,def);
         }
      }
    };

  private:

   void printStart(NamedPtr<Page> ptr)
    {
     if( ptr.hasName() )
       {
        StrLen name=Range(ptr.name);

        if( IsAbs(name) )
          {
           printf("& ##Doc#;",name);
          }
        else
          {
           printf("& ##Doc###;",name);
          }
       }
     else if( ptr.hasObj() )
       {
        Index index=getIndex();

        printf("& ##Doc###;",index);

        addAnonym(index,ptr.ptr.getPtr());
       }
     else
       {
        putstr("null"_c);
       }
    }

   template <class T>
   void print(StrLen name,const OptDataBase<T> &data)
    {
     if( !data.def )
       {
        printf(" , .#; = #;",name,data.data);
       }
    }

  private:

   template <class T>
   void addAnonym(Index index,T *ptr)
    {
     list.insLast(Rec{index,ptr});
    }

   template <class ... TT>
   void addAnonym(Index index,AnyPtr<TT...> ptr)
    {
     ptr.apply( [&] (auto *ptr) { addAnonym(index,ptr); } );
    }

   template <class ... TT>
   void printAnonym(Index index,AnyPtr<TT...> ptr)
    {
     ptr.apply( [&] (auto *ptr) { elem(index,ptr); } );
    }

   void printAnonym()
    {
     while( Rec *rec=list.getFirst() )
       {
        printAnonym(rec->index,rec->ptr);

        list.delFirst();
       }
    }

  private:

   Collector<Page *> links;

   struct PageName
    {
     String name;
     Page *page;
    };

   Collector<PageName> pages;

   ulen addLink(Page *page)
    {
     ulen ret=links.getLen();

     links.append_copy(page);

     return ret;
    }

   struct ScopeCursor
    {
      Scope *ptr;

     private:

      void set(IntAnyObjPtr<Scope,Doc> scope)
       {
        if( +scope )
          ptr=scope.getPtr().castPtr<Scope>();
        else
          ptr=0;
       }

     public:

      explicit ScopeCursor(IntAnyObjPtr<Scope,Doc> scope) { set(scope); }

      Scope * operator + () const { return ptr; }

      String * operator * () const { return &ptr->name; }

      void operator ++ () { set(ptr->scope); }
    };

   static String MakeName(IntAnyObjPtr<Scope,Doc> scope,NameType page_name)
    {
     ScopeCursor cur(scope);

     ulen count=0;

     for(String *name : ForLoop(cur) )
       {
        Used(name);

        count++;
       }

     TempArray<String *,10> temp(count);

     auto rev=RangeReverse(temp);

     for(String *name : ForLoop(cur) )
       {
        *rev=name;

        ++rev;
       }

     PrintString out;

     Putobj(out,"#Doc"_c);

     for(String *name : temp )
       {
        Printf(out,"###;",*name);
       }

     AdaptPrintf(out,"###;",page_name);

     return out.close();
    }

   void addPage(NameType name,Page *page)
    {
     pages.append_copy({MakeName(page->scope,name),page});
    }

   void printLink(ulen ind,Page *page,PtrLen<PageName> page_list)
    {
     ulen index=page->index;

     if( index<page_list.len )
       printf("Page * link#; = & #; ;\n\n",ind,page_list[index].name);
     else
       putstr("Page * link#; = null ;\n\n");
    }

   void printLinks()
    {
     auto link_list=links.flat();
     auto page_list=pages.flat();

     for(Page *page : link_list ) page->index=MaxULen;

     for(ulen ind=0; ind<page_list.len ;ind++) page_list[ind].page->index=ind;

     for(ulen ind=0; ind<link_list.len ;ind++) printLink(ind,link_list[ind],page_list);
    }

  private:

   void elem(Defaults &defs)
    {
     if( !defs.inner.def )
       {
        printf("Point DefaultInner = #; ;\n\n",defs.inner.data);
       }

     if( !defs.outer.def )
       {
        printf("Point DefaultOuter = #; ;\n\n",defs.outer.data);
       }

     if( !defs.bulletSpace.def )
       {
        printf("Coord DefaultBulletSpace = #; ;\n\n",defs.bulletSpace.data);
       }

     if( !defs.itemSpace.def )
       {
        printf("Coord DefaultItemSpace = #; ;\n\n",defs.itemSpace.data);
       }


     if( +defs.collapseFormat )
       {
        elem("DefaultCollapseFormat"_c,defs.collapseFormat.getPtr());
       }

     if( +defs.bulletFormat )
       {
        elem("DefaultBulletFormat"_c,defs.bulletFormat.getPtr());
       }

     if( +defs.border )
       {
        elem("DefaultBorder"_c,defs.border.getPtr());
       }

     if( +defs.textFormat )
       {
        elem("DefaultFormat"_c,defs.textFormat.getPtr());
       }

     if( +defs.fixedFormat )
       {
        elem("DefaultFixedFormat"_c,defs.fixedFormat.getPtr());
       }

     if( +defs.placement )
       {
        defs.placement.getPtr().apply( [&] (auto *ptr) { elem("DefaultPlacement"_c,ptr); } );
       }

     printAnonym();
    }

   void elem(ElementList &list)
    {
     for(Element &obj : ForIntList(list) )
       {
        elem_null(obj.ptr);
       }
    }

   template <class ... TT>
   void elem_null(IntAnyObjPtr<TT...> ptr)
    {
     if( +ptr )
       {
        ptr.getPtr().apply( [&] (auto *ptr) { elem(ptr); } );
       }
    }

   template <class T>
   void elem(T *ptr)
    {
     StrLen name=Range(ptr->name);

     elem(name,ptr);

     printAnonym();
    }

   void elem(Section *ptr)
    {
     elem(ptr->list);
    }

   void elem(Include *ptr)
    {
     printf("include <#;>\n\n",ptr->file_name);
    }

   void elem(Extern *) {}

   void elem(NameType name,Font *ptr)
    {
     printf("Font #; = { #; , #; , #; , #; , #; } ;\n\n",name,
                                                         DDLPrintableString(ptr->face),
                                                         ptr->size,
                                                         ptr->bold.get(),
                                                         ptr->italic.get(),
                                                         ptr->strength.get());
    }

   void elem(NameType name,Format *ptr)
    {
     printf("Format #; = { #; , #; , #; , #; } ;\n\n",name,
                                                      Named(this,ptr->font),
                                                      ptr->back.get(),
                                                      ptr->fore.get(),
                                                      ptr->effect.get());
    }

   void elem(NameType name,SingleLine *ptr)
    {
     printf("SingleLine #; = { #; , #; } ;\n\n",name,
                                                ptr->width.get(),
                                                ptr->line.get());
    }

   void elem(NameType name,DoubleLine *ptr)
    {
     printf("DoubleLine #; = { #; , #; , #; } ;\n\n",name,
                                                     ptr->width.get(),
                                                     ptr->gray.get(),
                                                     ptr->snow.get());
    }

   void elem(NameType name,Page *ptr)
    {
     printf("Page #; = { #; ,\n",name,
                                 DDLPrintableString(ptr->title));

     elem(ptr->list);

     printf(", #; , #; , #; , #; , #; } ;\n\n",ptr->back.get(),
                                               ptr->fore.get(),
                                               Named(this,ptr->up),
                                               Named(this,ptr->prev),
                                               Named(this,ptr->next));

     addPage(name,ptr);
    }

   void elem(NameType name,Scope *ptr)
    {
     printf("scope #; {\n\n",name);

     elem(ptr->defs);
     elem(ptr->list);

     putstr("}\n\n"_c);
    }

   void elem(NameType name,Bitmap *ptr)
    {
     printf("Bitmap #; = { #; } ;\n\n",name,
                                       DDLPrintableString(ptr->file_name));
    }

   void elem(NameType name,Collapse *ptr)
    {
     printf("Collapse #; = { #; ,\n",name,
                                     DDLPrintableString(ptr->title));

     elem(ptr->list);

     printf(", #; , #; , #; } ;\n\n",Named(this,ptr->format,"&DefaultCollapseFormat"_c),
                                     ptr->openlist,
                                     ptr->hide.get());
    }

   void elem(NameType name,TextList *ptr)
    {
     printf("TextList #; = {\n",name);

     elem(ptr->list);

     printf(", #; , #; , #; } ;\n\n",Named(this,ptr->format,"&DefaultBulletFormat"_c),
                                     OptDef(ptr->bullet_space,"DefaultBulletSpace"_c),
                                     OptDef(ptr->item_space,"DefaultItemSpace"_c));
    }

   void elem(NameType name,Border *ptr)
    {
     printf("Border #; = { #; , #; , #; } ;\n\n",name,
                                                 ptr->space.get(),
                                                 ptr->width.get(),
                                                 ptr->line.get());
    }

   void elem(NameType name,Cell *ptr)
    {
     printf("Cell #; = {\n",name);

     elem(ptr->list);

     printf(", #; , #; } ;\n\n",ptr->span_x.get(),ptr->span_y.get());
    }

   void elem(NameType name,Table *ptr)
    {
     printf("Table #; = { ",name);

     auto width=Range(ptr->table.width);

     elem(width);

     putstr(" , ");

     elem(Range(ptr->table.cells),width.len);

     printf(", #; , #; };\n\n",Named(this,ptr->border,"&DefaultBorder"_c),
                               ptr->hard.get());
    }

   void elem(NameType name,Link *ptr)
    {
     printf("Link #; = { ",name);

     if( +ptr->page )
       {
        ulen ind=addLink(ptr->page.getPtr());

        printf("##link#;",ind);
       }
     else
       {
        putstr("null"_c);
       }

     putstr(" , "_c);

     elem(Range(ptr->index_list));

     putstr(" } ;\n\n"_c);
    }

   void elem(NameType name,FixedText *ptr)
    {
     printf("FixedText #; = {\n",name);

     elemFixed(Range(ptr->list));

     printf(", #; } ;\n\n",Named(this,ptr->format,"&DefaultFixedFormat"_c));
    }

   void elem(NameType name,OneLine *ptr)
    {
     printf("OneLine #; = { #; } ;\n\n",name,
                                        ptr->align.get());
    }

   void elem(NameType name,MultiLine *ptr)
    {
     printf("MultiLine #; = { #; , #; } ;\n\n",name,
                                               ptr->line_space.get(),
                                               ptr->first_line_space.get());
    }

   void elem(NameType name,Text *ptr)
    {
     printf("Text #; = {\n",name);

     elemText(Range(ptr->list));

     printf(", #; , #; } ;\n\n",Named(this,ptr->format,"&DefaultFormat"_c),
                                Named(this,ptr->placement,"&DefaultPlacement"_c));
    }

   void elem(FrameList &list)
    {
     putstr("{\n"_c);

     bool first=true;

     for(Frame &frame : ForIntList(list) )
       {
        if( !Change(first,false) ) putstr(","_c);

        printf("{ #; , #; , #; , #; , #; }\n",Named(this,frame.body),
                                              Named(this,frame.line),
                                              OptDef(frame.inner,"DefaultInner"_c),
                                              OptDef(frame.outer,"DefaultOuter"_c),
                                              frame.col.get());
       }

     putstr("}\n"_c);
    }

   void elem(ItemList &list)
    {
     putstr("{\n"_c);

     bool first=true;

     for(Item &item : ForIntList(list) )
       {
        if( !Change(first,false) ) putstr(","_c);

        printf("{ #; ,\n",DDLPrintableString(item.bullet));

        elem(item.list);

        putstr("}\n");
       }

     putstr("}\n"_c);
    }

   void elem(PtrLen<Span> list)
    {
     putstr("{\n"_c);

     bool first=true;

     for(Span &span : list )
       {
        if( !Change(first,false) ) putstr(","_c);

        printf("{ #; , #; , #; }\n",DDLPrintableString(span.body),
                                    Named(this,span.format),
                                    Named(this,span.ref));
       }

     putstr("}\n"_c);
    }

   void elemFixed(PtrLen<TextLine> list)
    {
     putstr("{\n"_c);

     bool first=true;

     for(TextLine &line : list )
       {
        if( !Change(first,false) ) putstr(","_c);

        elem(Range(line.list));
       }

     putstr("}\n"_c);
    }

   void elemText(PtrLen<TextLine> list)
    {
     putstr("{\n"_c);

     bool first=true;

     for(TextLine &line : list )
       {
        for(Span &span : line.list )
          {
           if( !Change(first,false) ) putstr(","_c);

           printf("{ #; , #; , #; }\n",DDLPrintableString(span.body),
                                       Named(this,span.format),
                                       Named(this,span.ref));
          }
       }

     putstr("}\n"_c);
    }

   template <OneOfTypes<const ulen,Coord> T>
   void elem(PtrLen<T> list)
    {
     putstr("{ "_c);

     bool first=true;

     for(T obj : list )
       {
        if( !Change(first,false) ) putstr(" , "_c);

        printf("#;",obj);
       }

     putstr(" }"_c);
    }

   void elem(PtrLen<NamedPtr<Cell> > row)
    {
     putstr("{ "_c);

     bool first=true;

     for(auto &obj : row )
       {
        if( !Change(first,false) ) putstr(" , "_c);

        printf("#;",Named(this,obj));
       }

     putstr(" }\n"_c);
    }

   void elem(PtrLen<NamedPtr<Cell> > list,ulen nx)
    {
     if( !nx )
       {
        putstr("{}\n"_c);

        return;
       }

     putstr("{\n"_c);

     bool first=true;

     while( +list )
       {
        auto row=list.takeup(nx);

        if( !Change(first,false) ) putstr(","_c);

        elem(row);
       }

     putstr("}\n"_c);
    }

  public:

   explicit BookContext(PrintBase &out_) : out(out_) {}

   void print(Doc *doc)
    {
     putstr("include <pretext:/Book1.ddl>\n\n"_c);

     printf("Book Data = { .title = #; , .start = ",DDLPrintableString(doc->title));

     printStart(doc->start);

     print("back",doc->back);

     print("fore",doc->fore);

     putstr(" } ;\n\n"_c);

     putstr("scope Doc {\n\n"_c);

     elem(doc->defs);
     elem(doc->list);

     putstr("\n}\n\n"_c);

     printLinks();
    }

   void printEmpty()
    {
     putstr("include <pretext:/Book1.ddl>\n\n"_c);

     putstr("Book Data = { 'Empty book' , null } ;\n\n"_c);
    }
 };

/* class Book */

ErrorText Book::book(StrLen file_name,PtrLen<char> ebuf) const
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     if( !linked )
       {
        Printf(Exception,"App::BookLab::Book::book(...) : not linked");
       }

     PrintFile out(file_name);
     BookContext ctx(out);

     if( +doc )
       ctx.print(doc.getPtr());
     else
       ctx.printEmpty();

     report.guard();

     return Success;
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",file_name);

     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

