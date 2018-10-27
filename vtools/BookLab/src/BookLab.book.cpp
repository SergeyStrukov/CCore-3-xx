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

        Printf(out,"& Doc##ANONYM#;",index);

        // TODO
       }
    }

   void print(StrLen name,const OptData<VColor,DefNoColor> &data)
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
     Printf(eout,"\n@ #.q;",file_name);

     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

