/* DomConvert.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_DomConvert_h
#define App_DomConvert_h

#include <inc/ErrorId.h>

#include <CCore/inc/String.h>
#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* classes */

template <class T> class List;

//enum ErrorCode;

class DomErrorId;

class Format;

struct Span;

class Text;

class Fixed;

struct TextBase;

struct ElemH1;

struct ElemH2;

struct ElemH3;

struct ElemH4;

struct ElemH5;

struct ElemP;

struct ElemPRE;

struct TListBase;

struct ElemOL;

struct ElemUL;

struct ElemLI;

struct ElemImg;

class Builder;

/* class List<T> */

template <class T>
class List : NoCopy
 {
   struct Node : NoCopy
    {
     SLink<Node> link;

     T obj;

     explicit Node(const T &obj_) : obj(obj_) {}
    };

   using Algo = typename SLink<Node>::template LinearAlgo<&Node::link> ;

   typename Algo::FirstLast list;

  public:

   List() {}

   template <class Pool>
   void add(Pool &pool,const T &obj)
    {
     Node *node=pool.template create<Node>(obj);

     list.ins_last(node);
    }
 };

/* enum ErrorCode */

enum ErrorCode
 {
  Error_NoElem = 1,
  Error_NotClosed,

  Error_NoTop,
  Error_TagMismatch,
  Error_NoText,
  Error_NoFormat,

  Error_CannotAdd,

  Error_HasFmt,
  Error_NoFmt
 };

StrLen ToString(int code);

/* class DomErrorId */

class DomErrorId : public ErrorId
 {
  public:

   DomErrorId() {}

   DomErrorId(ErrorCode code) : ErrorId(code,ToString) {}
 };

/* class Format */

class Format : NoCopy
 {
   bool fmt_b = false ;
   bool fmt_i = false ;
   bool fmt_u = false ;

   bool fmt_sub = false ;
   bool fmt_sup = false ;

   bool fmt_span = false ;
   StrLen spanclass;

   bool fmt_a = false ;

   StrLen fmt;

   StrLen link;
   bool has_link = false ;

  private:

   void prepareFmt();

   DomErrorId setFmt(bool &flag);

   DomErrorId clearFmt(bool &flag);

   void setLink(Builder &builder,StrLen str);

  public:

   Format() {}

   DomErrorId setB() { return setFmt(fmt_b); }

   DomErrorId endB() { return clearFmt(fmt_b); }

   DomErrorId setI() { return setFmt(fmt_i); }

   DomErrorId endI() { return clearFmt(fmt_i); }

   DomErrorId setU() { return setFmt(fmt_u); }

   DomErrorId endU() { return clearFmt(fmt_u); }

   DomErrorId setSUB() { return setFmt(fmt_sub); }

   DomErrorId endSUB() { return clearFmt(fmt_sub); }

   DomErrorId setSUP() { return setFmt(fmt_sup); }

   DomErrorId endSUP() { return clearFmt(fmt_sup); }

   DomErrorId setSPAN(Builder &builder,const String &str);

   DomErrorId endSPAN() { return clearFmt(fmt_span); }

   DomErrorId setA();

   DomErrorId setA(Builder &builder,const String &str);

   DomErrorId endA();

   StrLen getFmt() const { return fmt; }

   bool hasLink() const { return has_link; }

   StrLen getLink() const { return link; }

   DomErrorId noFormat() const;
 };

/* struct Span */

struct Span
 {
  StrLen text;
  StrLen fmt;

  StrLen link;
  bool has_link = false ;
 };

void AddSpan(List<Span> &spans,Builder &builder,const Format &format,StrLen str);

/* class Text */

class Text : NoCopy
 {
   Format format;

   List<Span> spans;

  private:

   void addSpan(Builder &builder,StrLen str);

  public:

   Format & refFormat() { return format; }

   DomErrorId frame(Builder &builder,StrLen str);

   DomErrorId complete();
 };

/* struct Line */

struct Line : NoCopy
 {
  List<Span> spans;
 };

/* class Fixed */

class Fixed : NoCopy
 {
   Format format;

   List<Line *> lines;

   Line * cur = 0 ;

  private:

   void provideLine(Builder &builder);

   void breakLine(Builder &builder);

   void extLine(Builder &builder,StrLen str);

  public:

   Format & refFormat() { return format; }

   DomErrorId frame(Builder &builder,StrLen str);

   DomErrorId complete();
 };

/* struct TextBase */

struct TextBase : NoCopy
 {
  Text text;

  Format & refFormat() { return text.refFormat(); }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }
 };

/* struct ElemH1 */

struct ElemH1 : TextBase
 {
  StrLen id;
 };

/* struct ElemH2 */

struct ElemH2 : TextBase
 {
  StrLen id;
 };

/* struct ElemH3 */

struct ElemH3 : TextBase
 {
  StrLen id;
 };

/* struct ElemH4 */

struct ElemH4 : TextBase
 {
  StrLen id;
 };

/* struct ElemH5 */

struct ElemH5 : TextBase
 {
  StrLen id;
 };

/* struct ElemP */

struct ElemP : TextBase
 {
  StrLen id;
  StrLen elem_class;
 };

/* struct ElemPRE */

struct ElemPRE : NoCopy
 {
  StrLen id;
  Fixed text;

  Format & refFormat() { return text.refFormat(); }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }
 };

/* struct TListBase */

struct TListBase : NoCopy // TODO
 {
  Text text;

  Format & refFormat() { return text.format; }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  List<ElemLI *> list;

  DomErrorId add(Builder &builder,ElemLI *elem);

  DomErrorId complete() { return {}; }
 };

/* struct ElemOL */

struct ElemOL : TListBase
 {
  StrLen id;
 };

/* struct ElemUL */

struct ElemUL : TListBase
 {
  StrLen id;
 };

/* struct ElemLI */

struct ElemLI : NoCopy // TODO
 {
  Text text;

  Format & refFormat() { return text.format; }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId add(Builder &builder,ElemOL *elem);

  DomErrorId add(Builder &builder,ElemUL *elem);

  DomErrorId complete();
 };

/* struct ElemImg */

struct ElemImg : NoCopy
 {
  StrLen id;
  StrLen file_name;
 };

/* class Builder */

using TopPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemImg> ;

using BuildPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemLI> ;

class Builder : NoCopy
 {
   ElementPool pool;

   StrLen title;

   List<TopPtr> elems;

  public:

   Builder() {}

   ~Builder() {}

   // common

   template <class T,class ... SS>
   T * create(SS && ... ss) { return pool.create<T>( std::forward<SS>(ss)... ); }

   StrLen dup(StrLen str) { return pool.dup(str); }

   StrLen dup(const String &str) { return pool.dup(Range(str)); }

   template <class ... TT>
   StrLen cat(TT ... tt) { return pool.cat(tt...); }

   // add

   void setTitle(StrLen title_) { title=title_; }

   void add(TopPtr ptr) { elems.add(pool,ptr); }
 };

/* concept Has_id<T> */

template <class T>
concept bool Has_id = requires(T &obj,StrLen str) { obj.id=str; } ;

/* concept CanAdd<Elem,Base> */

template <class Elem,class Base>
concept bool CanAdd = requires(Base *base,Elem *elem,Builder &builder) { base->add(builder,elem); } ;

/* concept Has_frame<T> */

template <class T>
concept bool Has_frame = requires(T &obj,Builder &builder,StrLen str) { obj.frame(builder,str); } ;

/* concept Has_refFormat<T> */

template <class T>
concept bool Has_refFormat = requires(T &obj) { obj.refFormat(); } ;

} // namespace Dom

/* guard functions */

void GuardStackEmpty();

/* functions */

template <class T,class ... TT>
bool TrySetAnyPtr(AnyPtr<TT...> &dst,T *ptr) requires ( OneOfTypes<T,TT...> )
 {
  dst=ptr;

  return true;
 }

template <class T,class Ptr>
bool TrySetAnyPtr(T &,Ptr)
 {
  return false;
 }

template <class T,class S>
bool TryCastAnyPtr(T &dst,S src)
 {
  bool null=true;
  bool ret=false;

  src.apply( [&] (auto *ptr) { ret=TrySetAnyPtr(dst,ptr); null=false; } );

  if( null )
    {
     dst=Null;

     return true;
    }

  return ret;
 }

/* TestSpace() */

bool TestSpace(StrLen str);

/* classes */

template <class T> class Stack;

class DomConvert;

/* class Stack<T> */

template <class T>
class Stack : NoCopy
 {
   DynArray<T> buf;

  public:

   Stack() : buf(DoReserve,100) {}

   ~Stack() {}

   bool isEmpty() const { return buf.isEmpty(); }

   T top() const
    {
     ulen len=buf.getLen();

     if( !len ) GuardStackEmpty();

     return buf[len-1];
    }

   void push(const T &obj)
    {
     buf.append_copy(obj);
    }

   T pop()
    {
     T ret=top();

     buf.shrink_one();

     return ret;
    }
 };

/* class DomConvert */

class DomConvert : NoCopy
 {
   Dom::Builder builder;

   Stack<Dom::BuildPtr> stack;

   String id;
   bool has_id = false ;

  public:

   using EId = Dom::DomErrorId ;

  private:

   template <class Elem>
   void setId(Elem *elem);

   template <Dom::Has_id Elem>
   void setId(Elem *elem);

   template <class Elem,class Func>
   EId openElem(Func func);

   template <class Elem>
   EId openElem() { return openElem<Elem>( [] (Elem *) {} ); }

   template <class Base,class Elem>
   EId addElem(Base *base,Elem *elem);

   template <class Base,Dom::CanAdd<Base> Elem>
   EId addElem(Base *base,Elem *elem);

   template <class Elem>
   EId closeElem();

   template <class Elem,class Func>
   static EId SetFormat(Elem *elem,Func func);

   template <Dom::Has_refFormat Elem,class Func>
   static EId SetFormat(Elem *elem,Func func);

   template <class Func>
   EId setFormat(Func func);

   template <class Elem>
   EId frame(Elem *elem,StrLen str);

   template <Dom::Has_frame Elem>
   EId frame(Elem *elem,StrLen str);

  public:

   DomConvert();

   ~DomConvert();

   // title

   void setTitle(String title);

   // id

   void setId(String id);

   // frame

   EId frame(String str);

   // text

   EId tagH1();

   EId tagH1end();

   EId tagH2();

   EId tagH2end();

   EId tagH3();

   EId tagH3end();

   EId tagH4();

   EId tagH4end();

   EId tagH5();

   EId tagH5end();

   EId tagP();

   EId tagP(String tclass);

   EId tagPend();

   EId tagPRE();

   EId tagPREend();

   // format

   EId tagB();

   EId tagBend();

   EId tagI();

   EId tagIend();

   EId tagU();

   EId tagUend();

   EId tagSUB();

   EId tagSUBend();

   EId tagSUP();

   EId tagSUPend();

   EId tagSPAN(String tclass);

   EId tagSPANend();

   // hyperlink

   EId tagA(String url);

   EId tagA(String type,String url);

   EId tagAend();

   // list

   EId tagOL();

   EId tagOLend();

   EId tagUL();

   EId tagULend();

   EId tagLI();

   EId tagLIend();

   // image

   EId tagImg(String file_name);

   // complete

   EId complete();
 };

} // namespace App

#endif



