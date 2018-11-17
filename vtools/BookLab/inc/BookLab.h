/* BookLab.h */
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

#ifndef BookLab_h
#define BookLab_h

#include <inc/BookElements.h>
#include <inc/SingleRoom.h>

#include <CCore/inc/TextTools.h>
#include <CCore/inc/ForLoop.h>
#include <CCore/inc/ErrorText.h>

namespace App {
namespace BookLab {

/* consts */

enum HandleResult
 {
  HandleNone = 0,

  HandleOk,
  HandleUpdate,
 };

/* functions */

template <class DomainPtr>
auto SafePtr(DomainPtr &ptr) { return !ptr ? 0 : ptr.getPtr() ; }

/* name functions */

template <OneOfTypes<Char,char> Ch>
bool TestKeyword(PtrLen<const Ch> str);

bool IsNameFirst_char(char ch);

bool IsNameNext_char(char ch);

inline bool IsNameBreak_char(char ch) { return ch==' '; }

bool TestName(StrLen text);

bool IsNameFirst(Char ch);

bool IsNameNext(Char ch);

inline bool IsNameBreak(Char ch) { return ch==' '; }

bool TestName(PtrLen<const Char> text);

/* classes */

class PropTable;

template <class IntList> class IntListCur;

struct Index;

class NextIndex;

template <class Ctx,class T> struct BindCtx;

struct Ref;

struct PaneRef;

class TempData;

struct InsData;

struct Config;

class Book;

/* class PropTable */

enum CharClass
 {
  CharClassNone = 0 ,

  CharNameFirst,
  CharNameNext
 };

class PropTable : public CharPropTable<CharClass,CharClassNone>
 {
  public:

   PropTable();

   static PropTable Object;
 };

/* class IntListCur<IntList> */

template <class IntList>
class IntListCur
 {
   using Ptr = decltype( SafePtr(Meta::TypeBox<IntList &>::Get().beg) ) ;

   Ptr ptr; // T *

  public:

   explicit IntListCur(IntList &list) : ptr(SafePtr(list.beg)) {}

   bool operator + () const { return ptr; }

   auto & operator * () const { return *ptr; }

   void operator ++ () { ptr=SafePtr(ptr->next); }
 };

template <class IntList>
auto ForIntList(IntList &list) { return ForLoop(IntListCur(list)); }

/* struct Index */

struct Index
 {
  unsigned index;
 };

/* class NextIndex */

class NextIndex : NoCopy
 {
   unsigned next_index = 1 ;

  public:

   NextIndex() {}

   Index getIndex();
 };

/* struct BindCtx<Ctx,T> */

template <class Ctx,class T>
struct BindCtx
 {
  Ctx *ctx;
  const T &obj;

  BindCtx(Ctx *ctx_,const T &obj_) : ctx(ctx_),obj(obj_) {}
 };

/* struct Ref */

using ModeType = AnyPtr<OpenFlag,FrameList,ItemList,ElementList> ;

using PadType =

AnyPtr<bool,Coord,String,

       OptDataBase<bool>,OptDataBase<Coord>,OptDataBase<ulen>,
       OptDataBase<VColor>,OptDataBase<Strength>,OptDataBase<Align>,OptDataBase<Effect>,
       OptDataBase<Point>,OptDataBase<Ratio>,

       NamedPtr<Font>,NamedPtr<Page>,NamedPtr<Format>,NamedPtr<Border>,
       NamedPtr<OneLine,MultiLine>,NamedPtr<SingleLine,DoubleLine>,
       NamedPtr<Bitmap,Collapse,TextList,Table,Text,FixedText>,

       IntObjPtr<SingleLine>,IntObjPtr<DoubleLine>,IntObjPtr<Format>,IntObjPtr<Border>,
       IntAnyObjPtr<OneLine,MultiLine>,

       DynArray<Span>,DynArray<TextLine>,Table::Data,Link,

       FrameList,ItemList,Element> ;

struct Ref
 {
  ModeType mode;
  PadType pad;

  Ref() noexcept {}

  template <class T>
  Ref(T *ptr) : mode(ptr) {}

  Ref(ElementList &list,Element &elem) : mode(&list),pad(&elem) {}

  Ref(NothingType,PadType pad_) : pad(pad_) {}
 };

/* struct PaneRef */

struct PaneRef
 {
  Pane pane;
  Ref ref;

  // constructors

  PaneRef() noexcept {}

  PaneRef(NothingType) noexcept {}

  PaneRef(Pane pane_,Ref ref_) : pane(pane_),ref(ref_) {}

  // methods

  bool isPad() const { return +ref.pad; }

  bool isElement() const { return +ref.pad && ref.pad.hasType<Element>() ; }

  Element * getElement() const { return ref.pad.castPtr<Element>(); }

  ElementList * getElementList() const { return ref.mode.castPtr<ElementList>(); }

  template <class Func>
  void applyToPad(Func func) { ref.pad.apply(func); }

  struct IsRef;

  bool is(Ref ref_) const;

  // testMode()

  bool testMode(ElementList *) { return false; }

  template <OneOfTypes<OpenFlag,FrameList,ItemList> T>
  bool testMode(T *ptr) { return ptr; }

  bool testMode();

  // handleMode()

  HandleResult handleMode(Point,ElementList *) { return HandleNone; }

  HandleResult handleMode(Point point,OpenFlag *ptr);

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleMode(Point point,T *ptr);

  HandleResult handleMode(Point point);

  // handleList()

  HandleResult handleList(Point,bool,ElementList *) { return HandleNone; }

  HandleResult handleList(Point,bool,OpenFlag *) { return HandleNone; }

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleList(Point point,bool prev,T *ptr);

  HandleResult handleList(Point point,bool prev);

  // handleList...()

  template <class T>
  HandleResult handleListPrev(T *) { return HandleNone; }

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleListPrev(T *ptr) { return ptr->gotoPrev()?HandleUpdate:HandleOk; }

  HandleResult handleListPrev();


  template <class T>
  HandleResult handleListNext(T *) { return HandleNone; }

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleListNext(T *ptr) { return ptr->gotoNext()?HandleUpdate:HandleOk; }

  HandleResult handleListNext();


  template <class T>
  HandleResult handleListBeg(T *) { return HandleNone; }

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleListBeg(T *ptr) { return ptr->gotoBeg()?HandleUpdate:HandleOk; }

  HandleResult handleListBeg();


  template <class T>
  HandleResult handleListEnd(T *) { return HandleNone; }

  template <OneOfTypes<FrameList,ItemList> T>
  HandleResult handleListEnd(T *ptr) { return ptr->gotoEnd()?HandleUpdate:HandleOk; }

  HandleResult handleListEnd();
 };

/* class TempData */

class TempData : NoCopy
 {
   SingleRoom<bool,Coord,String,ulen,VColor,Strength,Align,Effect,Point,Ratio> data;

  private:

   template <class T>
   static StrLen GetTypeName(T *) { return Null; }

   static StrLen GetTypeName(bool *) { return "bool"_c; }

   static StrLen GetTypeName(Coord *) { return "Coord"_c; }

   static StrLen GetTypeName(String *) { return "text"_c; }

   static StrLen GetTypeName(ulen *) { return "ulen"_c; }

   static StrLen GetTypeName(VColor *) { return "Color"_c; }

   static StrLen GetTypeName(Strength *) { return "int"_c; }

   static StrLen GetTypeName(Align *) { return "Align"_c; }

   static StrLen GetTypeName(Effect *) { return "Effect"_c; }

   static StrLen GetTypeName(Point *) { return "Point"_c; }

   static StrLen GetTypeName(Ratio *) { return "Ratio"_c; }

   template <class T>
   bool copy(T *,ModeType) { return false; }

   template <OneOfTypes<bool,Coord,String,ulen,VColor,Strength,Align,Effect,Point,Ratio> T>
   bool copy(T *ptr,ModeType)
    {
     data.create<T>(*ptr);

     return true;
    }

   template <class T>
   bool copy(OptDataBase<T> *ptr,ModeType)
    {
     if( ptr->def ) return false;

     data.create<T>(ptr->data);

     return true;
    }

   template <class T>
   bool past(T *,ModeType) { return false; }

   template <OneOfTypes<bool,Coord,String,ulen,VColor,Strength,Align,Effect,Point,Ratio> T>
   bool past(T &ret)
    {
     if( T *src=data.getPtr().castPtr<T>() )
       {
        ret=*src;

        return true;
       }

     return false;
    }

   template <OneOfTypes<bool,Coord,String,ulen,VColor,Strength,Align,Effect,Point,Ratio> T>
   bool past(T *ptr,ModeType)
    {
     return past(*ptr);
    }

   template <class T>
   bool past(OptDataBase<T> *ptr,ModeType)
    {
     if( past(ptr->data) )
       {
        ptr->def=false;

        return true;
       }

     return false;
    }

  public:

   TempData();

   ~TempData();

   StrLen getTypeName() const;

   bool copy(Ref cursor);

   bool past(Ref cursor);

   void del();
 };

/* struct InsData */

enum ElementType
 {
  ElementNone = 0,

  ElementFont,
  ElementFormat,
  ElementSingleLine,
  ElementDoubleLine,
  ElementPage,
  ElementScope,
  ElementSection,
  ElementBitmap,
  ElementCollapse,
  ElementTextList,
  ElementBorder,
  ElementCell,
  ElementTable,
  ElementLink,
  ElementFixedText,
  ElementOneLine,
  ElementMultiLine,
  ElementText
 };

enum InsPlace
 {
  InsBefore = 1,
  InsAfter,
  InsInside
 };

struct InsData
 {
  ElementType type = ElementNone ;
  InsPlace place = InsAfter ;
  String text; // name OR comment
 };

/* struct Config */

struct Config
 {
  // user

  RefVal<VColor> gray  = Gray ;
  RefVal<VColor> snow  = Snow ;
  RefVal<VColor> face  = Black ;
  RefVal<VColor> alert = Pink ;

  // app

  RefVal<Fraction> line_width = Fraction(6,2) ;

  RefVal<Coord> table_dxy     = 3 ;
  RefVal<Coord> element_space = 5 ;
  RefVal<Coord> knob_dxy = 20 ;

  RefVal<VColor> table   = Black ;
  RefVal<VColor> text    = Blue ;
  RefVal<VColor> element = Black ;
  RefVal<VColor> comment = ForestGreen ;

  RefVal<CCore::Video::Font> text_font;
  RefVal<CCore::Video::Font> element_font;
  RefVal<CCore::Video::Font> comment_font;

  template <class AppPref>
  Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
   {
    bindUser(user_pref.get(),user_pref.getSmartConfig());
    bindApp(app_pref.get());
   }

  template <class Bag,class Proxy>
  void bindUser(const Bag &bag,Proxy proxy)
   {
    Used(proxy);

    gray.bind(bag.gray);
    snow.bind(bag.snow);
    face.bind(bag.face);
    alert.bind(bag.alert);
   }

  template <class Bag>
  void bindApp(const Bag &bag)
   {
    line_width.bind(bag.line_width);
    table_dxy.bind(bag.table_dxy);
    element_space.bind(bag.element_space);
    knob_dxy.bind(bag.knob_dxy);
    table.bind(bag.table);
    text.bind(bag.text);
    element.bind(bag.element);
    comment.bind(bag.comment);
    text_font.bind(bag.text_font.font);
    element_font.bind(bag.element_font.font);
    comment_font.bind(bag.comment_font.font);
   }
 };

/* class Book */

class Book : NoCopy
 {
   class Domain : public ObjectDomain
    {
      static constexpr ulen MemCap = 100_MByte ;

      PageHeap heap;

     private:

      virtual void * try_alloc(ulen len) { return heap.alloc(len); }

      virtual void free(void *mem) { heap.free(mem); }

     public:

      Domain() : ObjectDomain(MemCap) {}

      ~Domain() { cleanup(); }
    };

   Domain domain;

   ExtObjPtr<Doc> doc;

   bool linked = true ;

  private:

   static StrLen Pretext();

   class SaveContext;

   template <class T> struct LoadType;

   class LoadContext;

   class BookContext;

   class ScopeContext;

   void setScope();

   class ShowData;

   class ShowName;

   class PrepareContext;

   class DrawContext;

  private:

   ExtObjPtr<Element> create(InsData data);

   template <class T>
   bool insElementInside(ExtObjPtr<Element>,T *) { return false; }

   template <OneOfTypes<Scope,Section> T>
   bool insElementInside(ExtObjPtr<Element> elem,T *ptr) { insElementInside(elem,ptr->list); return true; }

   void insElementInside(ExtObjPtr<Element> elem,ElementList &list);

  public:

   Book();

   ~Book();

   void collect() { domain.collect(); }

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const;

   bool isLinked() const { return linked; }

   void unlink() { linked=false; }

   ErrorText link(PtrLen<char> ebuf);

   ErrorText book(StrLen file_name,PtrLen<char> ebuf) const;

   struct PrepareResult
    {
     Point size;
     bool erase_cursor;
    };

   PrepareResult prepare(const Config &cfg,DynArray<PaneRef> &refs,PaneRef &cursor) const;

   void draw(const Config &cfg,DrawBuf buf,Point base) const;

   // create

   template <class T>
   ExtObjPtr<T> create() { return ExtObjPtr<T>(domain); }

   // del

   template <class T>
   bool delItem(PaneRef &,T *) { return false; }

   bool delItem(PaneRef &cursor,FrameList *ptr);

   bool delItem(PaneRef &cursor,ItemList *ptr);

   bool delItem(PaneRef &cursor,Element *ptr);

   bool delItem(PaneRef &cursor);

   // ins

   HandleResult insFirst();

   bool insElement(InsData data);

   bool insElement(InsData data,PaneRef cursor);

   void insAfter(FrameList *ptr);

   void insAfter(ItemList *ptr);
 };

} // namespace BookLab
} // namespace App

#endif

