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

/* class Book::SaveContext */

class Book::SaveContext : NoCopy
 {
   PrintBase &out;

   unsigned next_index = 1 ;

   using ObjPtr = AnyPtr<Font,Format,SingleLine,DoubleLine,Page,Scope,Section,Bitmap,Collapse,TextList,Table,Text,FixedText,
                         Border,OneLine,MultiLine> ;

   struct Rec
    {
     unsigned index;
     ObjPtr objptr;
    };

   CompactList2<Rec> list;

  private:

   unsigned getIndex()
    {
     unsigned ret=next_index;

     if( !ret )
       {
        Printf(Exception,"App::BookLab::Book::SaveContext::getIndex() : too many objects");
       }

     next_index++;

     return ret;
    }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     Printf(out,format,tt...);
    }

   void queue(unsigned index,ObjPtr objptr)
    {
     list.insLast(Rec{index,objptr});
    }

   void printAny(unsigned index,ObjPtr objptr)
    {
     objptr.apply( [&] (auto *ptr) { print(index,ptr); } );
    }

   void printQueue()
    {
     while( +list )
       {
        Rec rec=*list.getFirst();

        printAny(rec.index,rec.objptr);

        list.delFirst();
       }
    }

  private:

   struct PrintOptColor
    {
     VColor data;
     bool def;

     explicit PrintOptColor(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , #; }",DDLBool(def),(uint32)data);
      }
    };

   struct PrintOptPoint
    {
     Point data;
     bool def;

     explicit PrintOptPoint(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , { #; , #; } }",DDLBool(def),data.x,data.y);
      }
    };

   struct PrintOptCoord
    {
     Coord data;
     bool def;

     explicit PrintOptCoord(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , #; }",DDLBool(def),data);
      }
    };

   struct PrintOptRatio
    {
     Ratio data;
     bool def;

     explicit PrintOptRatio(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , { #; , #; } }",DDLBool(def),data.a,data.b);
      }
    };

   struct PrintOptEffect
    {
     Effect data;
     bool def;

     explicit PrintOptEffect(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , #; }",DDLBool(def),(uint8)data);
      }
    };

   struct PrintOptBool
    {
     bool data;
     bool def;

     explicit PrintOptBool(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , #; }",DDLBool(def),DDLBool(data));
      }
    };

   struct PrintOptInt
    {
     int data;
     bool def;

     explicit PrintOptInt(const auto &obj) : data(obj.data),def(obj.def) {}

     void print(PrinterType &out) const
      {
       Printf(out,"{ #; , #; }",DDLBool(def),data);
      }
    };

   void printPtr(auto *ptr)
    {
     if( ptr )
       {
        unsigned index=getIndex();

        printf("& o#;",index);

        queue(index,ptr);
       }
     else
       {
        printf("null");
       }
    }

   void printAnyPtr(AnyPtr<OneLine,MultiLine> objptr)
    {
     if( +objptr )
       objptr.apply( [&] (auto *ptr) { printPtr(ptr); } );
     else
       printf("null");
    }

   void print(const NamedPtr<auto> &ref)
    {
     if( ref.hasName() )
       {
        printf("{ #; , null }",ref.name);
       }
     else if( ref.hasObj() )
       {
        unsigned index=getIndex();

        printf("{ null , & o#; }",index);

        queue(index,ref.ptr.getPtr());
       }
     else
       {
        printf("{ null , null }");
       }
    }

   void print(const Defaults &defs)
    {
     printf("{ #; , #; , #; , #; , ",PrintOptPoint(defs.inner)
                                    ,PrintOptPoint(defs.outer)
                                    ,PrintOptCoord(defs.bulletSpace)
                                    ,PrintOptCoord(defs.itemSpace));

     printPtr(SafePtr(defs.singleLine));

     printf(" , ");

     printPtr(SafePtr(defs.doubleLine));

     printf(" , ");

     printPtr(SafePtr(defs.collapseFormat));

     printf(" , ");

     printPtr(SafePtr(defs.bulletFormat));

     printf(" , ");

     printPtr(SafePtr(defs.border));

     printf(" , ");

     printPtr(SafePtr(defs.textFormat));

     printf(" , ");

     printPtr(SafePtr(defs.fixedFormat));

     printf(" , ");

     printAnyPtr(defs.placement.getPtr());

     printf(" }");
    }

   void print(const ElementList &list)
    {
     printf("{\n");

     bool flag=false;

     for(Element *ptr=SafePtr(list.beg); ptr ;ptr=SafePtr(ptr->next))
       {
        ObjPtr objptr=CastAnyPtr<ObjPtr>(ptr->ptr.getPtr());

        if( +objptr )
          {
           unsigned index=getIndex();

           if( Change(flag,true) )
             printf("& o#;",index);
           else
             printf(",\n& o#;",index);

           queue(index,objptr);
          }
       }

     printf("\n}\n");
    }

  private:

   void print(unsigned index,Font *ptr)
    {
     printf("Font o#; = { #; , #; , ",index,DDLPrintableString(ptr->name),DDLBool(ptr->open));

     printf("#; , #; , #; , #; , #; };\n\n",DDLPrintableString(ptr->face)
                                           ,ptr->size
                                           ,PrintOptBool(ptr->bold)
                                           ,PrintOptBool(ptr->italic)
                                           ,PrintOptInt(ptr->strength));
    }

   void print(unsigned index,Format *ptr)
    {
     printf("Format o#; = { #; , #; , ",index,DDLPrintableString(ptr->name),DDLBool(ptr->open));

     print(ptr->font);

     printf(" , #; , #; , #; };\n\n",PrintOptColor(ptr->back),PrintOptColor(ptr->fore),PrintOptEffect(ptr->effect));
    }

   void print(unsigned index,SingleLine *ptr)
    {
     printf("SingleLine o#; = { #; , #; , ",index,DDLPrintableString(ptr->name),DDLBool(ptr->open));

     printf("#; , #; };\n\n",PrintOptRatio(ptr->width),PrintOptColor(ptr->line));
    }

   void print(unsigned index,DoubleLine *ptr)
    {
     printf("DoubleLine o#; = { #; , #; , ",index,DDLPrintableString(ptr->name),DDLBool(ptr->open));

     printf("#; , #; , #; };\n\n",PrintOptRatio(ptr->width),PrintOptColor(ptr->gray),PrintOptColor(ptr->snow));
    }

   // TODO

   void print(unsigned index,Page *ptr)
    {
     Used(ptr);

     printf("Page o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Scope *ptr)
    {
     Used(ptr);

     printf("Scope o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Section *ptr)
    {
     Used(ptr);

     printf("Section o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Bitmap *ptr)
    {
     Used(ptr);

     printf("Bitmap o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Collapse *ptr)
    {
     Used(ptr);

     printf("Collapse o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,TextList *ptr)
    {
     Used(ptr);

     printf("TextList o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Table *ptr)
    {
     Used(ptr);

     printf("Table o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Text *ptr)
    {
     Used(ptr);

     printf("Text o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,FixedText *ptr)
    {
     Used(ptr);

     printf("FixedText o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Border *ptr)
    {
     Used(ptr);

     printf("Border o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,OneLine *ptr)
    {
     Used(ptr);

     printf("OneLine o#; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,MultiLine *ptr)
    {
     Used(ptr);

     printf("MultiLine o#; = { ",index);

     printf(" };\n\n");
    }

  public:

   explicit SaveContext(PrintBase &out_) : out(out_) {}

   void print(Doc *doc)
    {
     printf("Doc Data = { #; , #; , #; , ",DDLPrintableString(doc->title)
                                          ,PrintOptColor(doc->back)
                                          ,PrintOptColor(doc->fore));

     print(doc->start);

     printf(" , ");

     print(doc->defs);

     printf(" ,\n\n");

     print(doc->list);

     printf("\n};\n\n");

     printQueue();
    }

   void printEmpty()
    {
     // do nothing
    }
 };

/* class Book::BookContext */

class Book::BookContext : NoCopy
 {
   PrintBase &out;

   unsigned next_index = 1 ;

  private:

   unsigned getIndex() { return next_index++; }

   void printStart(const NamedPtr<Page> &page) // TODO
    {
     if( page.isResolved() )
       {
        Printf(out,"& Doc###;",page.name);
       }
     else
       {
        unsigned index=getIndex();

        Putobj(out,"& Doc##ANONYM#;"_c,index);

        // TODO
       }
    }

   void print(StrLen name,OptData<VColor,DefNoColor> data)
    {
     if( !data.def )
       {
        Printf(out," , .#; = #;",name,(uint32)data.data);
       }
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

     Putobj(out,"\n}\n\n"_c);
    }

   void printEmpty()
    {
     Putobj(out,"include <pretext:/Book1.ddl>\n\n"_c);

     Putobj(out,"Book Data = { 'Empty book' , null } ;\n\n"_c);
    }
 };

/* class Book */

void Book::startDoc()
 {
  if( !doc )
    {
     doc.create(domain,domain);
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

ErrorText Book::load(StrLen file_name,PtrLen<char> ebuf) // TODO
 {
  Used(file_name);

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

ErrorText Book::save(StrLen file_name,PtrLen<char> ebuf) const
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     PrintFile out(file_name);
     SaveContext ctx(out);

     if( +doc )
       ctx.print(doc.getPtr());
     else
       ctx.printEmpty();

     return Success;
    }
  catch(CatchType)
    {
     return eout.close();
    }
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

ErrorText Book::book(StrLen file_name,PtrLen<char> ebuf) const
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     PrintFile out(file_name);
     BookContext ctx(out);

     if( +doc )
       ctx.print(doc.getPtr());
     else
       ctx.printEmpty();

     return Success;
    }
  catch(CatchType)
    {
     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App
