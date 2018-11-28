/* BookLab.edit.cpp */
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

/* functions */

inline Coord MoveListZone(Pane pane,Point point)
 {
  if( pane.dy<=0 ) return -1;

  return (5*(point.y-pane.y))/pane.dy;
 }

/* struct PaneRef */

 // methods

struct PaneRef::IsRef
 {
  bool same;

  operator bool() const { return same; }

  IsRef() : same(false) {}

  IsRef(bool same_) : same(same_) {}

  IsRef(unsigned,unsigned) : same(false) {}
 };

bool PaneRef::is(Ref ref_) const
 {
  return PadType::Binary<IsRef>(ref.pad,ref_.pad, [] (auto *ptr1,auto *ptr2) -> IsRef { return ptr1==ptr2; } );
 }

 // testMode()

bool PaneRef::testMode()
 {
  bool ret=false;

  ref.mode.apply( [&] (auto *ptr) { ret=testMode(ptr); } );

  return ret;
 }

 // handleMode()

HandleResult PaneRef::handleMode(Point,OpenFlag *ptr,bool)
 {
  ptr->change();

  return HandleUpdate;
 }

template <OneOfTypes<FrameList,ItemList> T>
HandleResult PaneRef::handleMode(Point point,T *ptr,bool move_flag)
 {
  if( move_flag )
    {
     switch( MoveListZone(pane,point) )
       {
        case 1 : return ptr->movePrev()?HandleUpdate:HandleOk;
        case 3 : return ptr->moveNext()?HandleUpdate:HandleOk;
       }
    }
  else
    {
     switch( MoveListZone(pane,point) )
       {
        case 0 : return ptr->gotoBeg()?HandleUpdate:HandleOk;
        case 1 : return ptr->gotoPrev()?HandleUpdate:HandleOk;
        case 3 : return ptr->gotoNext()?HandleUpdate:HandleOk;
        case 4 : return ptr->gotoEnd()?HandleUpdate:HandleOk;
       }
    }

  return HandleOk;
 }

HandleResult PaneRef::handleMode(Point point,bool move_flag)
 {
  HandleResult ret=HandleNone;

  ref.mode.apply( [&] (auto *ptr) { if( ptr ) ret=handleMode(point,ptr,move_flag); } );

  return ret;
 }

 // handleList()

template <OneOfTypes<FrameList,ItemList> T>
HandleResult PaneRef::handleList(Point point,bool prev,T *ptr,bool move_flag)
 {
  if( MoveListZone(pane,point)==2 )
    {
     if( move_flag )
       {
        if( prev )
          return ptr->movePrev()?HandleUpdate:HandleOk;
        else
          return ptr->moveNext()?HandleUpdate:HandleOk;
       }
     else
       {
        if( prev )
          return ptr->gotoPrev()?HandleUpdate:HandleOk;
        else
          return ptr->gotoNext()?HandleUpdate:HandleOk;
       }
    }

  return HandleOk;
 }

HandleResult PaneRef::handleList(Point point,bool prev,bool move_flag)
 {
  HandleResult ret=HandleNone;

  ref.mode.apply( [&] (auto *ptr) { if( ptr ) ret=handleList(point,prev,ptr,move_flag); } );

  return ret;
 }

 // handleList...()

HandleResult PaneRef::handleListPrev()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleListPrev(ptr); } );

  return ret;
 }

HandleResult PaneRef::handleListNext()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleListNext(ptr); } );

  return ret;
 }

HandleResult PaneRef::handleListBeg()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleListBeg(ptr); } );

  return ret;
 }

HandleResult PaneRef::handleListEnd()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleListEnd(ptr); } );

  return ret;
 }

 // handleMove...()

HandleResult PaneRef::handleMovePrev()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleMovePrev(ptr); } );

  return ret;
 }

HandleResult PaneRef::handleMoveNext()
 {
  HandleResult ret=HandleNone;

  ref.pad.apply( [&] (auto *ptr) { if( ptr ) ret=handleMoveNext(ptr); } );

  return ret;
 }

/* class Book */

 // del

bool Book::delItem(PaneRef &,FrameList *ptr)
 {
  return ptr->del();
 }

bool Book::delItem(PaneRef &,ItemList *ptr)
 {
  return ptr->del();
 }

bool Book::delItem(PaneRef &cursor,Element *ptr)
 {
  if( ElementList *list=cursor.getElementList() )
    {
     if( Element *subst=list->del(ptr) )
       {
        cursor.ref.pad=subst;
       }
     else
       {
        cursor=Null;
       }

     return true;
    }

  return false;
 }

bool Book::delItem(PaneRef &cursor)
 {
  bool ret=false;

  cursor.applyToPad( [&] (auto *ptr) { if( ptr ) ret=delItem(cursor,ptr); } );

  return ret;
 }

 // ins

HandleResult Book::insFirst()
 {
  if( !doc )
    {
     doc.create(domain,domain);

     return HandleUpdate;
    }
  else if( !doc->list.beg )
    {
     return HandleOk;
    }

  return HandleNone;
 }

ExtObjPtr<Element> Book::create(InsData data)
 {
  ExtObjPtr<Element> ret(domain);

  switch( data.type )
    {
     case ElementFont :
      {
       ExtObjPtr<Font> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementFormat :
      {
       ExtObjPtr<Format> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementSingleLine :
      {
       ExtObjPtr<SingleLine> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementDoubleLine :
      {
       ExtObjPtr<DoubleLine> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementPage :
      {
       ExtObjPtr<Page> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementScope :
      {
       ExtObjPtr<Scope> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementSection :
      {
       ExtObjPtr<Section> ptr(domain);

       ptr->comment=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementBitmap :
      {
       ExtObjPtr<Bitmap> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementCollapse :
      {
       ExtObjPtr<Collapse> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementTextList :
      {
       ExtObjPtr<TextList> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementBorder :
      {
       ExtObjPtr<Border> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementCell :
      {
       ExtObjPtr<Cell> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementTable :
      {
       ExtObjPtr<Table> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementLink :
      {
       ExtObjPtr<Link> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementFixedText :
      {
       ExtObjPtr<FixedText> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementOneLine :
      {
       ExtObjPtr<OneLine> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementMultiLine :
      {
       ExtObjPtr<MultiLine> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;

     case ElementText :
      {
       ExtObjPtr<Text> ptr(domain);

       ptr->name=data.text;

       ret->ptr=ptr;
      }
     break;
    }

  return ret;
 }

bool Book::insElement(InsData data)
 {
  if( !data.type || !doc ) return false;

  if( +doc->list.beg ) return false;

  doc->list.insFirst(create(data));

  return true;
 }

bool Book::insElement(InsData data,PaneRef cursor)
 {
  Element *ptr=cursor.getElement();
  ElementList *list=cursor.getElementList();

  if( !data.type || !ptr || !list ) return false;

  auto elem=create(data);

  switch( data.place )
    {
     case InsBefore :
      {
       list->insBefore(ptr,elem);
      }
     return true;

     case InsAfter :
      {
       list->insAfter(ptr,elem);
      }
     return true;

     case InsInside :
      {
       bool ret=false;

       ptr->ptr.getPtr().apply( [&] (auto *obj) { ret=insElementInside(elem,obj); } );

       return ret;
      }

     default: return false;
    }
 }

void Book::insAfter(FrameList *ptr)
 {
  ptr->insAfter(ExtObjPtr<Frame>(domain));
 }

void Book::insAfter(ItemList *ptr)
 {
  ptr->insAfter(ExtObjPtr<Item>(domain));
 }

} // namespace BookLab
} // namespace App


