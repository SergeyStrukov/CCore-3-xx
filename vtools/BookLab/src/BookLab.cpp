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

/* namespace SaveAdapter */

namespace SaveAdapter {

template <class T> struct Adapter;

template <>
struct Adapter<String>
 {
  DDLPrintableString data;

  explicit Adapter(const String &obj) : data(obj) {}

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
struct Adapter<Coord>
 {
  Coord data;

  explicit Adapter(Coord obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Putobj(out,data);
   }
 };

template <>
struct Adapter<unsigned>
 {
  unsigned data;

  explicit Adapter(unsigned obj) : data(obj) {}

  void print(PrinterType &out) const
   {
    Printf(out,"o#;",data);
   }
 };

template <auto Def>
struct Adapter<OptData<bool,Def> >
 {
  bool data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",DDLBool(def),DDLBool(data));
   }
 };

template <auto Def>
struct Adapter<OptData<Effect,Def> >
 {
  Effect data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",DDLBool(def),(uint8)data);
   }
 };

template <auto Def>
struct Adapter<OptData<Align,Def> >
 {
  Align data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",DDLBool(def),(uint8)data);
   }
 };

template <auto Def>
struct Adapter<OptData<VColor,Def> >
 {
  VColor data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",DDLBool(def),(uint32)data);
   }
 };

template <auto Def>
struct Adapter<OptData<Point,Def> >
 {
  Point data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , { #; , #; } }",DDLBool(def),data.x,data.y);
   }
 };

template <auto Def>
struct Adapter<OptData<Ratio,Def> >
 {
  Ratio data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , { #; , #; } }",DDLBool(def),data.a,data.b);
   }
 };

template <OneOfTypes<Coord,int> T,auto Def>
struct Adapter<OptData<T,Def> >
 {
  Coord data;
  bool def;

  explicit Adapter(const auto &obj) : data(obj.data),def(obj.def) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{ #; , #; }",DDLBool(def),data);
   }
 };

template <class T>
auto Adapt(const T &obj) { return Adapter<T>(obj); }

template <class Ctx,class T>
struct Adapter<BindCtx<Ctx,NamedPtr<T> > >
 {
  const BindCtx<Ctx,NamedPtr<T> > &bind;

  explicit Adapter(const BindCtx<Ctx,NamedPtr<T> > &bind_) : bind(bind_) {}

  void print(PrinterType &out) const
   {
    auto &ref=bind.obj;

    if( ref.hasName() )
      {
       Printf(out,"{ #; , null }",Adapt(ref.name));
      }
    else if( ref.hasObj() )
      {
       unsigned index=bind.ctx->getIndex();

       Printf(out,"{ null , & #; }",Adapt(index));

       bind.ctx->queue(index,ref.ptr.getPtr());
      }
    else
      {
       Printf(out,"{ null , null }");
      }
   }
 };

template <class Ctx>
struct Adapter<BindCtx<Ctx,ElementList> >
 {
  const BindCtx<Ctx,ElementList> &bind;

  explicit Adapter(const BindCtx<Ctx,ElementList> &bind_) : bind(bind_) {}

  void print(PrinterType &out) const
   {
    Printf(out,"{\n");

    bool flag=false;

    for(Element *ptr=SafePtr(bind.obj.beg); ptr ;ptr=SafePtr(ptr->next))
      {
       auto objptr=ptr->ptr.getPtr();

       if( +objptr )
         {
          unsigned index=bind.ctx->getIndex();

          if( Change(flag,true) )
            Printf(out,"& #;",Adapt(index));
          else
            Printf(out,",\n& #;",Adapt(index));

          bind.ctx->queueCast(index,objptr);
         }
      }

    Printf(out,"\n}\n");
   }
 };

template <class Ctx>
struct Adapter<BindCtx<Ctx,Defaults> >
 {
  const BindCtx<Ctx,Defaults> &bind;

  explicit Adapter(const BindCtx<Ctx,Defaults> &bind_) : bind(bind_) {}

  void printPtr(PrinterType &out,auto *ptr) const
   {
    if( ptr )
      {
       unsigned index=bind.ctx->getIndex();

       Printf(out,"& #;",Adapt(index));

       bind.ctx->queue(index,ptr);
      }
    else
      {
       Printf(out,"null");
      }
   }

  void printAnyPtr(PrinterType &out,AnyPtr<OneLine,MultiLine> objptr) const
   {
    if( +objptr )
      objptr.apply( [&] (auto *ptr) { printPtr(out,ptr); } );
    else
      Printf(out,"null");
   }

  void print(PrinterType &out) const
   {
    auto &defs=bind.obj;

    Printf(out,"{ #; , #; , #; , #; , ",Adapt(defs.inner)
                                       ,Adapt(defs.outer)
                                       ,Adapt(defs.bulletSpace)
                                       ,Adapt(defs.itemSpace));

    printPtr(out,SafePtr(defs.singleLine));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.doubleLine));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.collapseFormat));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.bulletFormat));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.border));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.textFormat));

    Printf(out," , ");

    printPtr(out,SafePtr(defs.fixedFormat));

    Printf(out," , ");

    printAnyPtr(out,defs.placement.getPtr());

    Printf(out," }");
   }
 };

} // namespace SaveAdapter

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
     Printf(out,format,SaveAdapter::Adapter<TT>(tt)...);
    }

   void queue(unsigned index,ObjPtr objptr)
    {
     list.insLast(Rec{index,objptr});
    }

   template <class ... TT>
   void queueCast(unsigned index,AnyPtr<TT...> objptr)
    {
     queue(index,CastAnyPtr<ObjPtr>(objptr));
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

   template <class T>
   friend struct SaveAdapter::Adapter;

   auto bind(const auto &obj) { return BindCtx(this,obj); }

  private:

   void print(unsigned index,Font *ptr)
    {
     printf("Font #; = { #; , #; , #; , #; , #; , #; , #; };\n\n",index
                                                                 ,ptr->name
                                                                 ,ptr->open
                                                                 ,ptr->face
                                                                 ,ptr->size
                                                                 ,ptr->bold
                                                                 ,ptr->italic
                                                                 ,ptr->strength);
    }

   void print(unsigned index,Format *ptr)
    {
     printf("Format #; = { #; , #; , #; , #; , #; , #; };\n\n",index
                                                              ,ptr->name
                                                              ,ptr->open
                                                              ,bind(ptr->font)
                                                              ,ptr->back
                                                              ,ptr->fore
                                                              ,ptr->effect);
    }

   void print(unsigned index,SingleLine *ptr)
    {
     printf("SingleLine #; = { #; , #; , #; , #; };\n\n",index
                                                        ,ptr->name
                                                        ,ptr->open
                                                        ,ptr->width
                                                        ,ptr->line);
    }

   void print(unsigned index,DoubleLine *ptr)
    {
     printf("DoubleLine #; = { #; , #; , #; , #; , #; };\n\n",index
                                                             ,ptr->name
                                                             ,ptr->open
                                                             ,ptr->width
                                                             ,ptr->gray
                                                             ,ptr->snow);
    }


   void print(unsigned index,Page *ptr) // TODO
    {
     Used(ptr);

     printf("Page #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Scope *ptr) // TODO
    {
     Used(ptr);

     printf("Scope #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Section *ptr) // TODO
    {
     Used(ptr);

     printf("Section #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Bitmap *ptr) // TODO
    {
     Used(ptr);

     printf("Bitmap #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Collapse *ptr) // TODO
    {
     Used(ptr);

     printf("Collapse #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,TextList *ptr) // TODO
    {
     Used(ptr);

     printf("TextList #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Table *ptr) // TODO
    {
     Used(ptr);

     printf("Table #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,Text *ptr) // TODO
    {
     Used(ptr);

     printf("Text #; = { ",index);

     printf(" };\n\n");
    }

   void print(unsigned index,FixedText *ptr) // TODO
    {
     Used(ptr);

     printf("FixedText #; = { ",index);

     printf(" };\n\n");
    }


   void print(unsigned index,Border *ptr)
    {
     printf("Border #; = { #; , #; , #; , #; , #; };\n\n",index
                                                         ,ptr->name
                                                         ,ptr->open
                                                         ,ptr->space
                                                         ,ptr->width
                                                         ,ptr->line);

    }

   void print(unsigned index,OneLine *ptr)
    {
     printf("OneLine #; = { #; , #; , #; };\n\n",index
                                                ,ptr->name
                                                ,ptr->open
                                                ,ptr->align);
    }

   void print(unsigned index,MultiLine *ptr)
    {
     printf("MultiLine #; = { #; , #; , #; , #; };\n\n",index
                                                       ,ptr->name
                                                       ,ptr->open
                                                       ,ptr->line_space
                                                       ,ptr->first_line_space);
    }

  public:

   explicit SaveContext(PrintBase &out_) : out(out_) {}

   void print(Doc *doc)
    {
     printf("Doc Data = { #; , #; , #; , #; , #; ,\n\n#;\n};\n\n",doc->title
                                                                 ,doc->back
                                                                 ,doc->fore
                                                                 ,bind(doc->start)
                                                                 ,bind(doc->defs)
                                                                 ,bind(doc->list));

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
