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
#include <inc/PrintPage.h>
#include <inc/CppText.h>

#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/List.h>
#include <CCore/inc/CompactList.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* IsSpace() */

bool IsSpace(StrLen str);

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

template <class ... TT> class TextMix;

struct TListBase;

struct ElemOL;

struct ElemUL;

struct ElemLI;

struct ElemImg;

struct ExtName;

class PrintBook;

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

   template <class Func>
   void apply(Func func) const
    {
     ulen ind=0;

     for(auto cur=list.start(); +cur ;++cur,++ind)
       {
        func(ind,cur->obj);
       }
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

   template <class Func>
   void setLink(Builder &builder,StrLen str,Func func);

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

   template <class Func>
   DomErrorId setA(Builder &builder,const String &str,Func func);

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

  template <class Kind>
  void printKind(PrintBase &out,Kind kind) const
   {
    if( has_link )
      {
       if( !fmt )
         Printf(out,"{ #; , null , & #; }",PrintSpan(text),link);
       else
         Printf(out,"{ #; , & fmt_#;_#; , & #; }",PrintSpan(text),kind,fmt,link);
      }
    else
      {
       if( !fmt )
         Printf(out,"{ #; }",PrintSpan(text));
       else
         Printf(out,"{ #; , & fmt_#;_#; }",PrintSpan(text),kind,fmt);
      }
   }
 };

void AddSpan(List<Span> &spans,Builder &builder,const Format &format,StrLen str);

void AddSpan(List<Span> &spans,Builder &builder,const Format &format,StrLen cfmt,StrLen str);

template <class Kind>
void PrintSpanList(PrintBase &out,Kind kind,const List<Span> &spans);

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

   template <class Kind>
   void printKind(PrintBase &out,Kind kind) const;
 };

/* struct Line */

struct Line : NoCopy
 {
  List<Span> spans;

  template <class Kind>
  void printKind(PrintBase &out,Kind kind) const;
 };

/* class Fixed */

class Fixed : NoCopy
 {
   Format format;

   CppText::Tokenizer tokenizer;

   List<Line *> lines;

   Line * cur = 0 ;

  private:

   static StrLen CFmt(CppText::TokenClass tc);

   void provideLine(Builder &builder);

   void breakLine(Builder &builder);

   void extLine(Builder &builder,StrLen str);

  public:

   Format & refFormat() { return format; }

   DomErrorId frame(Builder &builder,StrLen str);

   DomErrorId complete();

   template <class Kind>
   void printKind(PrintBase &out,Kind kind) const;
 };

/* struct TextBase */

struct TextBase : NoCopy
 {
  Text text;

  Format & refFormat(Builder &) { return text.refFormat(); }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }

  StrLen getType() const { return "Text"_c; }

  template <class Kind>
  void printKind(PrintBase &out,Kind kind) const;
 };

/* struct ElemH1 */

struct ElemH1 : TextBase
 {
  StrLen id;

  StrLen getKind() const { return "h1"_c; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemH2 */

struct ElemH2 : TextBase
 {
  StrLen id;

  StrLen getKind() const { return "h2"_c; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemH3 */

struct ElemH3 : TextBase
 {
  StrLen id;

  StrLen getKind() const { return "h3"_c; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemH4 */

struct ElemH4 : TextBase
 {
  StrLen id;

  StrLen getKind() const { return "h4"_c; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemH5 */

struct ElemH5 : TextBase
 {
  StrLen id;

  StrLen getKind() const { return "h5"_c; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemP */

struct ElemP : TextBase
 {
  StrLen id;

  struct Kind
   {
    StrLen name;
    bool has = false ;

    void set(StrLen name_)
     {
      name=name_;
      has=true;
     }

    void print(PrinterType &out) const
     {
      if( has )
        Printf(out,"text_#;",name);
      else
        Putobj(out,"text"_c);
     }
   };

  Kind kind;

  auto getKind() const { return kind; }

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* struct ElemPRE */

struct ElemPRE : NoCopy
 {
  StrLen id;
  Fixed text;

  Format & refFormat(Builder &) { return text.refFormat(); }

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }

  StrLen getKind() const { return "cpp"_c; }

  StrLen getType() const { return "FixedText"_c; }

  template <class Kind>
  void printKind(PrintBase &out,Kind kind) const;

  void print(PrintBase &out) const { printKind(out,getKind()); }
 };

/* class TextMix<TT> */

template <class ... TT>
class TextMix : NoCopy
 {
   using APtr = AnyPtr<Text,TT...> ;

   List<APtr> list;

   Text * cur = 0 ;

  private:

   void provideText(Builder &builder);

  public:

   TextMix() {}

   Format & refFormat(Builder &builder)
    {
     provideText(builder);

     return cur->refFormat();
    }

   DomErrorId frame(Builder &builder,StrLen str)
    {
     if( IsSpace(str) ) return {};

     provideText(builder);

     return cur->frame(builder,str);
    }

   template <OneOfTypes<TT...> T>
   DomErrorId add(Builder &builder,T *elem)
    {
     DomErrorId ret;

     if( cur )
       {
        ret=cur->complete();

        cur=0;
       }

     list.add(builder,elem);

     return ret;
    }

   DomErrorId complete()
    {
     if( cur ) return cur->complete();

     return {};
    }

   template <class Func>
   void apply(Func func) const { list.apply(func); }
 };

/* struct TListBase */

struct TListBase : TextMix<ElemLI>
 {
 };

/* struct ElemOL */

struct ElemOL : TListBase
 {
  StrLen id;

  StrLen getKind() const { return "list"_c; }

  StrLen getType() const { return "TextList"_c; }

  template <class Kind>
  static void PrintItem(PrintBook &book,Text *text,Kind kind,ulen &bullet);

  template <class Kind>
  static void PrintItem(PrintBook &book,ElemLI *elem,Kind kind,ulen &bullet);

  template <class Kind>
  void printKind(PrintBook &book,Kind kind) const;

  void print(PrintBook &book) const { printKind(book,getKind()); }
 };

/* struct ElemUL */

struct ElemUL : TListBase
 {
  StrLen id;

  StrLen getKind() const { return "list"_c; }

  StrLen getType() const { return "TextList"_c; }

  template <class Kind>
  static void PrintItem(PrintBook &book,Text *text,Kind kind);

  template <class Kind>
  static void PrintItem(PrintBook &book,ElemLI *elem,Kind kind);

  template <class Kind>
  void printKind(PrintBook &book,Kind kind) const;

  void print(PrintBook &book) const { printKind(book,getKind()); }
 };

/* struct ElemLI */

struct ElemLI : TextMix<ElemOL,ElemUL>
 {
  template <class Kind>
  static void PrintItem(PrintBook &book,Text *text,Kind kind);

  template <class Elem,class Kind>
  static void PrintItem(PrintBook &book,Elem *elem,Kind kind);

  template <class Kind>
  void printKind(PrintBook &book,Kind kind) const;
 };

/* struct ElemImg */

struct ElemImg : NoCopy
 {
  StrLen id;
  StrLen file_name;

  StrLen getKind() const { return "img"_c; }

  StrLen getType() const { return "Bitmap"_c; }

  void print(PrintBase &out) const;
 };

/* Ptr types */

using TopPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemImg> ;

using BuildPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemLI> ;

/* concept ExtPrint<T> */

template <class T>
concept bool ExtPrint = requires(T &obj,PrintBook &book) { obj.print(book); } ;

/* struct ExtName */

struct ExtName
 {
  ulen ind;

  void print(PrinterType &out) const { Printf(out,"o#;",ind); }
 };

/* class PrintBook */

class PrintBook : NoCopy
 {
   PrintBase &out;

   ulen extind = 0 ;

  private:

   template <class Elem>
   void print(ulen ind,Elem *elem);

   template <ExtPrint Elem>
   void print(ulen ind,Elem *elem);

   ExtName getExtName() { return {extind++}; }

  private:

   struct RecBase : MemBase
    {
     RecBase() {}

     virtual ~RecBase() {}

     virtual void print(PrintBook &book) const = 0 ;
    };

   template <class Elem,class Kind>
   struct Rec : RecBase
    {
     ExtName name;
     Elem *elem;
     Kind kind;

     Rec(ExtName name_,Elem *elem_,Kind kind_) : name(name_),elem(elem_),kind(kind_) {}

     virtual ~Rec() {}

     virtual void print(PrintBook &book) const
      {
       book.print(name,elem,kind);
      }
    };

   CompactList2<OwnPtr<RecBase> > defer_list;

   template <class Elem,class Kind>
   void addRec(ExtName name,Elem *elem,Kind kind);

   void process(RecBase *rec);

   template <class Kind>
   void print(ExtName name,Text *text,Kind kind);

   template <class Elem,class Kind>
   void print(ExtName name,Elem *elem,Kind kind);

   template <ExtPrint Elem,class Kind>
   void print(ExtName name,Elem *elem,Kind kind);

  public:

   explicit PrintBook(PrintBase &out_) : out(out_) {}

   template <class Elem,class Kind>
   ExtName addExt(Elem *elem,Kind kind);

   void pump();

   // common

   void print(ulen ind,TopPtr aptr);

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     Printf(out,format,tt...);
    }

   template <class ... TT>
   void putobj(const TT & ... tt)
    {
     Putobj(out,tt...);
    }

   void put(char ch) { out.put(ch); }
 };

/* class Builder */

class Builder : NoCopy
 {
   ElementPool pool;

   StrLen title;

   List<TopPtr> elems;

  public:

   Builder() : title("untitled"_c) {}

   ~Builder() {}

   // common

   template <class T,class ... SS>
   T * create(SS && ... ss) { return pool.create<T>( std::forward<SS>(ss)... ); }

   StrLen dup(StrLen str) { return pool.dup(str); }

   StrLen dup(const String &str) { return pool.dup(Range(str)); }

   template <class ... TT>
   StrLen cat(TT ... tt) { return pool.cat(tt...); }

   // add

   StrLen getTitle() const { return title; }

   void setTitle(StrLen title_) { title=title_; }

   void add(TopPtr ptr) { elems.add(pool,ptr); }

   // print

   void print(PrintBase &out,PageParam param) const;
 };

template <class ... TT>
void TextMix<TT...>::provideText(Builder &builder)
 {
  if( !cur )
    {
     cur=builder.create<Text>();

     list.add(builder,cur);
    }
 }

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
concept bool Has_refFormat = requires(T &obj,Builder &builder) { obj.refFormat(builder); } ;

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

   Collector<String> page_list;

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
   EId setFormat(Elem *elem,Func func);

   template <Dom::Has_refFormat Elem,class Func>
   EId setFormat(Elem *elem,Func func);

   template <class Func>
   EId setFormat(Func func);

   template <class Elem>
   EId frame(Elem *elem,StrLen str);

   template <Dom::Has_frame Elem>
   EId frame(Elem *elem,StrLen str);

  public:

   DomConvert();

   ~DomConvert();

   // pages

   DynArray<String> getPageList()
    {
     DynArray<String> ret;

     page_list.extractTo(ret);

     return ret;
    }

   // title

   StrLen getTitle() const { return builder.getTitle(); }

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

   // print

   void print(PrintBase &out,PageParam param) const { builder.print(out,param); }
 };

} // namespace App

#endif



