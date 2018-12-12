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

/* class Book::BookContext */

class Book::BookContext : NextIndex
 {
   PrintBase &out;

   bool indoc = true ;

  private:

   unsigned getIndex() { return NextIndex::getIndex().index; }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     Printf(out,format,tt...);
    }

   static bool IsAbs(StrLen name) { return +name && *name=='#' ; }

   template <class T>
   void addAnonym(unsigned index,T *ptr) // TODO
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
          unsigned index=ctx->getIndex();

          Printf(out,"& Anonym##o#;",index);

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
        unsigned index=getIndex();

        printf("& Anonym##o#;",index);

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
        Printf(out," , .#; = #;",name,(uint32)data.data);
       }
    }

  private:

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

   void elem(Format *ptr)
    {
     printf("Format #; = { #; , #; , #; , #; } ;\n\n",ptr->name,
                                                     Named(this,ptr->scope,ptr->font),
                                                     ptr->back.get(),
                                                     ptr->fore.get(),
                                                     ptr->effect.get());
    }

   void elem(SingleLine *ptr)
    {
    }

   void elem(DoubleLine *ptr)
    {
    }

   void elem(Page *ptr)
    {
    }

   void elem(Scope *ptr) // TODO
    {
     printf("scope #; {\n\n",ptr->name);

     elem(ptr->list);

     printf("}\n\n");
    }

   void elem(Section *ptr)
    {
     elem(ptr->list);
    }

   void elem(Bitmap *ptr)
    {
    }

   void elem(Collapse *ptr)
    {
    }

   void elem(TextList *ptr)
    {
    }

   void elem(Border *ptr)
    {
    }

   void elem(Cell *ptr)
    {
    }

   void elem(Table *ptr)
    {
    }

   void elem(Link *ptr)
    {
    }

   void elem(FixedText *ptr)
    {
    }

   void elem(OneLine *ptr)
    {
    }

   void elem(MultiLine *ptr)
    {
    }

   void elem(Text *ptr)
    {
    }

  public:

   explicit BookContext(PrintBase &out_) : out(out_) {}

   void print(Doc *doc) // TODO
    {
     Putobj(out,"include <pretext:/Book1.ddl>\n\n"_c);

     Printf(out,"Book Data = { .title = #; , .start = ",DDLPrintableString(doc->title));

     printStart(doc->start);

     print("back",doc->back);

     print("fore",doc->fore);

     Putobj(out," } ;\n\n"_c);

     Putobj(out,"scope Doc {\n\n"_c);

     // TODO

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

