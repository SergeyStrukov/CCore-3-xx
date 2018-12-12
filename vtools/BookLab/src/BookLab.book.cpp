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
    Printf(out,"Anonym##o#;",data.index);
   }
 };

template <OneOfTypes<StrLen,Coord,Strength> T>
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

class Book::BookContext : NextIndex
 {
   PrintBase &out;

   bool indoc = true ;

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

   static bool IsAbs(StrLen name) { return +name && *name=='#' ; }

   template <class T>
   void addAnonym(Index index,T *ptr) // TODO
    {
     Used(index);
     Used(ptr);
    }

   struct PrintScope
    {
     IntAnyObjPtr<Scope,Doc> scope;

     void print(PrinterType &out) const // TODO
      {
       Used(out);
      }
    };

   template <class T>
   struct Named
    {
     BookContext *ctx;
     IntAnyObjPtr<Scope,Doc> scope;
     NamedPtr<T> ptr;

     Named(BookContext *ctx_,IntAnyObjPtr<Scope,Doc> scope_,NamedPtr<T> ptr_) : ctx(ctx_),scope(scope_),ptr(ptr_) {}

     void print(PrinterType &out) const
      {
       if( ptr.hasName() )
         {
          StrLen name=Range(ptr.name);

          if( IsAbs(name) )
            {
             Printf(out,"& ##Doc#;",name);
            }
          else
            {
             if( ctx->indoc )
               {
                Printf(out,"& #;",name);
               }
             else
               {
                Printf(out,"& #;###;",PrintScope{scope},name);
               }
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
          Putobj(out,"null"_c);
         }
      }
    };

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

        printf("& #;",index);

        addAnonym(index,ptr.ptr.getPtr());
       }
     else
       {
        printf("null");
       }
    }

   void print(StrLen name,const OptData<VColor,DefNoColor> &data)
    {
     if( !data.def )
       {
        printf(" , .#; = #;",name,data.data);
       }
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


     if( +defs.singleLine )
       {
        elem("DefaultSingleLine"_c,defs.singleLine.getPtr());
       }

     if( +defs.doubleLine )
       {
        elem("DefalutDoubleLine"_c,defs.doubleLine.getPtr());
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
     if( +ptr ) ptr.getPtr().apply( [&] (auto *ptr) { elem(ptr); } );
    }

   void elem(Font *ptr)
    {
     printf("Font #; = { #; , #; , #; , #; , #; } ;\n\n",ptr->name,
                                                         DDLPrintableString(ptr->face),
                                                         ptr->size,
                                                         ptr->bold.get(),
                                                         ptr->italic.get(),
                                                         ptr->strength.get());
    }

   void elem(StrLen name,Format *ptr)
    {
     printf("Format #; = { #; , #; , #; , #; } ;\n\n",name,
                                                      Named(this,ptr->scope,ptr->font),
                                                      ptr->back.get(),
                                                      ptr->fore.get(),
                                                      ptr->effect.get());
    }

   void elem(Format *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(StrLen name,SingleLine *ptr)
    {
     printf("SingleLine #; = { #; , #; } ;\n\n",name,
                                                ptr->width.get(),
                                                ptr->line.get());
    }

   void elem(SingleLine *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(StrLen name,DoubleLine *ptr)
    {
     printf("DoubleLine #; = { #; , #; , #; } ;\n\n",name,
                                                     ptr->width.get(),
                                                     ptr->gray.get(),
                                                     ptr->snow.get());
    }

   void elem(DoubleLine *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(Page *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(Scope *ptr)
    {
     printf("scope #; {\n\n",ptr->name);

     elem(ptr->defs);
     elem(ptr->list);

     printf("}\n\n");
    }

   void elem(Section *ptr)
    {
     elem(ptr->list);
    }

   void elem(Bitmap *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(Collapse *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(TextList *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(StrLen name,Border *ptr)
    {
     printf("Border #; = { #; , #; , #; } ;\n\n",name,
                                                 ptr->space.get(),
                                                 ptr->width.get(),
                                                 ptr->line.get());
    }

   void elem(Border *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(Cell *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(Table *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(Link *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(FixedText *ptr) // TODO
    {
     Used(ptr);
    }

   void elem(StrLen name,OneLine *ptr)
    {
     printf("OneLine #; = { #; } ;\n\n",name,
                                        ptr->align.get());
    }

   void elem(OneLine *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(StrLen name,MultiLine *ptr)
    {
     printf("MultiLine #; = { #; , #; } ;\n\n",name,
                                               ptr->line_space.get(),
                                               ptr->first_line_space.get());
    }

   void elem(MultiLine *ptr)
    {
     elem(Range(ptr->name),ptr);
    }

   void elem(Text *ptr) // TODO
    {
     Used(ptr);
    }

  public:

   explicit BookContext(PrintBase &out_) : out(out_) {}

   void print(Doc *doc)
    {
     Putobj(out,"include <pretext:/Book1.ddl>\n\n"_c);

     printf("Book Data = { .title = #; , .start = ",DDLPrintableString(doc->title));

     printStart(doc->start);

     print("back",doc->back);

     print("fore",doc->fore);

     Putobj(out," } ;\n\n"_c);

     Putobj(out,"scope Doc {\n\n"_c);

     elem(doc->defs);
     elem(doc->list);

     Putobj(out,"\n}\n\n"_c);
    }

   void printEmpty()
    {
     Putobj(out,"include <pretext:/Book1.ddl>\n\n"_c);

     Putobj(out,"Book Data = { 'Empty book' , null } ;\n\n"_c);
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

