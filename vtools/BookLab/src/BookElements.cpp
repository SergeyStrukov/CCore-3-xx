/* BookElements.cpp */
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

#include <inc/BookElements.h>

namespace App {
namespace BookLab {

/* struct ElementList */

void ElementList::insBefore(Element *ptr,ExtObjPtr<Element> obj)
 {
  IntObjPtr<Element> prev=ptr->prev;

  if( +prev )
    {
     IntObjPtr<Element> next=prev->next;

     obj->prev=prev;
     obj->next=next;

     prev->next=obj;
     next->prev=obj;
    }
  else
    {
     IntObjPtr<Element> next=beg;

     obj->prev=Null;
     obj->next=next;

     beg=obj;
     next->prev=obj;
    }
 }

void ElementList::insAfter(Element *ptr,ExtObjPtr<Element> obj)
 {
  IntObjPtr<Element> next=ptr->next;

  if( +next )
    {
     IntObjPtr<Element> prev=next->prev;

     obj->prev=prev;
     obj->next=next;

     prev->next=obj;
     next->prev=obj;
    }
  else
    {
     IntObjPtr<Element> prev=end;

     obj->prev=prev;
     obj->next=Null;

     prev->next=obj;
     end=obj;
    }
 }

void ElementList::insFirst(ExtObjPtr<Element> obj)
 {
  IntObjPtr<Element> next=beg;

  obj->prev=Null;
  obj->next=next;

  if( +next )
    {
     next->prev=obj;
    }
  else
    {
     end=obj;
    }

  beg=obj;
 }

Element * ElementList::del(Element *ptr)
 {
  IntObjPtr<Element> prev=ptr->prev;
  IntObjPtr<Element> next=ptr->next;

  if( +prev ) prev->next=next; else beg=next;

  if( +next ) next->prev=prev; else end=prev;

  if( +next ) return next.getPtr();

  if( +prev ) return prev.getPtr();

  return 0;
 }

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

} // namespace BookLab
} // namespace App


