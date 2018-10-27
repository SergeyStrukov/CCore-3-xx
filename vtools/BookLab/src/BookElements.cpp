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

void ElementList::del(Element *ptr)
 {
  IntObjPtr<Element> prev=ptr->prev;
  IntObjPtr<Element> next=ptr->next;

  if( +prev ) prev->next=next; else beg=next;

  if( +next ) next->prev=prev; else end=prev;
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


