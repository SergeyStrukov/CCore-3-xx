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

#include <CCore/inc/Exception.h>

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

  domain.collect();
 }

ErrorText Book::load(StrLen file_name,PtrLen<char> ebuf)
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

} // namespace BookLab
} // namespace App
