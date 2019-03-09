/* Convert.h */
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

#ifndef App_Convert_h
#define App_Convert_h

#include <inc/AnyObjectPtr.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/String.h>
#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/PrintStem.h>

#include <CCore/inc/video/PrintDDL.h>

namespace App {

/* using */

using Video::DDLString;
using Video::DDLPrintableString;

/* classes */

struct SpanType;

class Span;

class OName;

class Text;

class Image;

class Frame;

class FrameList;

class ListItem;

class TextList;

class Convert;

/* enum Effect */

enum Effect
 {
  NoEffect,

  Underline,
  Strikeout,
  Hyperlink
 };

/* struct SpanType */

struct SpanType
 {
  bool bold = false ;
  bool italic = false ;

  Effect effect = NoEffect ;
 };

/* class Span */

class Span
 {
   SpanType type;
   String text;
   String url;

  private:

   static StrLen GetTail(SpanType type);

   StrLen getTail() const { return GetTail(type); }

  public:

   Span(SpanType type_,String text_,String url_=Null) : type(type_),text(text_),url(url_) {}

   // print object

   void print(PrinterType &out) const
    {
     Printf(out,"{#;#;}",DDLString(text),getTail());
    }
 };

/* enum TextType */

enum TextType
 {
  TextP,
  TextH1,
  TextH2,
  TextH3,
  TextH4,
  TextH5,
  TextLI
 };

/* class OName */

class OName
 {
   ulen ind;

   static ulen Next;

  public:

   OName() : ind(Next++) {}

   OName(NothingType) : ind(0) {}

   // print object

   void print(PrinterType &out) const
    {
     if( ind ) Printf(out,"o#;",ind); else Putobj(out,"<none>");
    }
 };

/* class Text */

class Text
 {
   OName name;
   TextType type;
   DynArray<Span> list;

  private:

   static StrLen GetTail(TextType type);

   StrLen getTail() const { return GetTail(type); }

  public:

   explicit Text(TextType type_) : type(type_) {}

   bool operator + () const { return list.getLen()>0; }

   OName getName() const { return name; }

   TextType getType() const { return type; }

   void add(Span span) { list.append_copy(span); }

   // print object

   void print(PrinterType &out) const
    {
     Printf(out,"Text #; = { {\n",name);

     PrintFirst stem(""_c,","_c);

     for(auto &obj : list ) Printf(out,"#;#;\n",stem,obj);

     Printf(out,"}#;} ;\n\n",getTail());
    }
 };

/* class Image */

class Image
 {
   OName name;
   String file_name;

  private:

   static StrLen GetFileName(StrLen file_name);

   StrLen getFileName() const { return GetFileName(Range(file_name)); }

  public:

   explicit Image(String file_name_) : file_name(file_name_) {}

   OName getName() const { return name; }

   // print object

   void print(PrinterType &out) const
    {
     Printf(out,"Bitmap #; = { ",name);

     Printf(out,"#; + '.bitmap' ",DDLPrintableString(getFileName()));

     Putobj(out," };\n\n");
    }
 };

/* class Frame */

class Frame
 {
   struct GetName
    {
     OName &ret;

     template <class T>
     void operator () (T &obj)
      {
       ret=obj.getName();
      }
    };

   struct Print
    {
     PrintBase &out;

     template <class T>
     void operator () (T &obj)
      {
       Putobj(out,obj);
      }
    };

   AnyObjectPtr<GetName,Print> ptr;
   bool no_space;

  public:

   explicit Frame(OneOfTypes<Text,Image,TextList> &&obj,bool no_space_=false) : ptr(std::move(obj)),no_space(no_space_) {}

   OName getName() const;

   bool getNoSpace() const { return no_space; }

   // print object

   void print(PrintBase &out) const;
 };

/* class FrameList */

class FrameList
 {
   DynArray<Frame> list;

  public:

   FrameList() {}

   void add(OneOfTypes<Text,Image,TextList> &&obj,bool no_space=false) { list.append_fill(Frame(std::move(obj),no_space)); }

   struct Frames
    {
     PtrLen<const Frame> list;

     // print object

     void print(PrinterType &out) const
      {
       for(auto &obj : list ) Printf(out,"#;\n\n",obj);
      }
    };

   Frames getFrames() const { return {Range(list)}; }

   // print object

   void print(PrinterType &out) const
    {
     Putobj(out,"{\n");

     PrintFirst stem(""_c,","_c);

     for(auto &obj : list )
       if( obj.getNoSpace() )
         Printf(out,"#;{ &#; , null , {0,0} , {0,0} }\n",stem,obj.getName());
       else
         Printf(out,"#;{ &#; }\n",stem,obj.getName());

     Putobj(out,"}");
    }
 };

/* class ListItem */

class ListItem
 {
   String bullet;
   FrameList list;

  public:

   explicit ListItem(ulen index) : bullet(Stringf("#;.",index)) {}

   void add(OneOfTypes<Text,TextList> &&obj) { list.add(std::move(obj),true); }

   auto getFrames() const { return list.getFrames(); }

   // print object

   void print(PrinterType &out) const
    {
     Printf(out,"{#;,#;}",DDLPrintableString(bullet),list);
    }
 };

/* class TextList */

class TextList
 {
   OName name;
   DynArray<ListItem> list;

  public:

   TextList() noexcept {}

   OName getName() const { return name; }

   void add(ListItem &&item) { list.append_fill(std::move(item)); }

   // print object

   void print(PrinterType &out) const
    {
     Printf(out,"TextList #; = { {",name);

     PrintFirst stem(""_c,","_c);

     for(auto &obj : list ) Printf(out,"#;#;\n",stem,obj);

     Putobj(out,"} };\n\n");

     for(auto &obj : list ) Putobj(out,obj.getFrames());
    }
 };

/* class Convert */

template <class T,class S>
concept bool CanPopTypes = requires(T *obj,S *top)
 {
  obj->add(top->complete());
 } ;

class Convert : NoCopy
 {
   class TextBuilder
    {
      Text text;
      SpanType span_type;

     public:

      explicit TextBuilder(TextType type) : text(type) {}

      TextBuilder(TextType type,SpanType span_type_) : text(type),span_type(span_type_) {}

      bool operator + () const { return +text; }

      SpanType getSpanType() const { return span_type; }

      bool check(TextType type) const { return text.getType()==type; }

      bool word(String word) { text.add(Span(span_type,word)); return true; }

      bool tagB() { return Change(span_type.bold,true); }

      bool tagBend() { return Change(span_type.bold,false); }

      bool tagI() { return Change(span_type.italic,true); }

      bool tagIend() { return Change(span_type.italic,false); }

      bool tagImg(String) { return false; }

      void add(Span span) { text.add(span); }

      Text complete() { return std::move(text); }
    };

   class ABuilder
    {
      String url;
      SpanType span_type;

      Collector<char> text;
      bool first = true ;

     public:

      ABuilder(String url_,SpanType span_type_) : url(url_),span_type(span_type_) { span_type.effect=Hyperlink; }

      bool check() const { return true; }

      bool word(String word)
       {
        if( !Change(first,false) ) text.append_copy(' ');

        text.extend_copy(Range(word));

        return true;
       }

      bool tagB() { return false; }

      bool tagBend() { return false; }

      bool tagI() { return false; }

      bool tagIend() { return false; }

      bool tagImg(String) { return false; }

      Span complete() { return Span(span_type,String(text.flat()),url); }
    };

   class ListItemBuilder
    {
      ListItem result;

      TextBuilder cur;

     private:

      void addText()
       {
        if( +cur )
          {
           SpanType span_type=cur.getSpanType();

           result.add(cur.complete());

           cur=TextBuilder(TextLI,span_type);
          }
       }

     public:

      explicit ListItemBuilder(ulen index) : result(index),cur(TextLI) {}

      SpanType getSpanType() const { return cur.getSpanType(); }

      bool check() const { return true; }

      bool word(String word) { return cur.word(word); }

      bool tagB() { return cur.tagB(); }

      bool tagBend() { return cur.tagBend(); }

      bool tagI() { return cur.tagI(); }

      bool tagIend() { return cur.tagIend(); }

      bool tagImg(String) { return false; }

      void add(TextList &&obj)
       {
        addText();

        result.add(std::move(obj));
       }

      void add(Span span)
       {
        cur.add(span);
       }

      ListItem complete()
       {
        addText();

        return std::move(result);
       }
    };

   class TextListBuilder
    {
      TextList result;
      ulen index = 1 ;

     public:

      TextListBuilder() {}

      ulen nextIndex() { return index++; }

      bool check() const { return true; }

      bool word(String) { return false; }

      bool tagB() { return false; }

      bool tagBend() { return false; }

      bool tagI() { return false; }

      bool tagIend() { return false; }

      bool tagImg(String) { return false; }

      void add(ListItem &&obj) { result.add(std::move(obj)); }

      TextList complete() { return std::move(result); }
    };

   class FrameListBuilder
    {
      FrameList result;

     public:

      FrameListBuilder() {}

      bool check() const { return true; }

      bool word(String) { return false; }

      bool tagB() { return false; }

      bool tagBend() { return false; }

      bool tagI() { return false; }

      bool tagIend() { return false; }

      bool tagImg(String file_name) { result.add(Image(file_name)); return true; }

      void add(OneOfTypes<Text,Image,TextList> &&obj) { result.add(std::move(obj)); }

      FrameList complete() { return std::move(result); }
    };

   class Builder
    {
      using BuilderPtr = AnyPtr<TextBuilder,ABuilder,ListItemBuilder,TextListBuilder,FrameListBuilder> ;

      struct Elaborate;

      AnyObjectPtr<Elaborate> ptr;

     private:

      BuilderPtr elaborate();

      template <class T,class S> requires( !CanPopTypes<T,S> )
      static void Add(T *,S *) {}

      template <class T,class S> requires( CanPopTypes<T,S> )
      static void Add(T *obj,S *top);

      template <class T>
      static void Add(T *obj,Builder &top);

     public:

      template <class T> requires ( !IsType<T,ToMoveCtor<Builder> &> )
      explicit Builder(T &&obj) : ptr(std::move(obj)) {}

      template <class T,class ... SS>
      bool check(SS && ... ss);

      template <class T>
      bool canPop();

      void pop(Builder &top);

      bool word(String word);

      bool tagB();

      bool tagBend();

      bool tagI();

      bool tagIend();

      bool tagImg(String file_name);

      template <class T>
      T * getOf();
    };

  private:

   String name;

   PrintFile out;

   DynArray<Builder> stack;

   Builder top;

  private:

   void start();

   void complete(FrameList list);

   template <class T,class ... SS>
   bool push(SS && ... ss);

   template <class T,class ... SS>
   bool pop(SS && ... ss);

  public:

   explicit Convert(StrLen output_file_name);

   ~Convert() {}

   // word

   bool word(String word);

   // text

   bool tagH1();

   bool tagH1end();

   bool tagH2();

   bool tagH2end();

   bool tagH3();

   bool tagH3end();

   bool tagH4();

   bool tagH4end();

   bool tagH5();

   bool tagH5end();

   bool tagP();

   bool tagPend();

   bool tagP(String pclass);

   bool tagPRE();

   bool tagPREend();

   bool tagSPAN(String pclass);

   bool tagSPANend();

   // format

   bool tagB();

   bool tagBend();

   bool tagI();

   bool tagIend();

   // hyperlink

   bool tagA(String url);

   bool tagAend();

   // list

   bool tagOL();

   bool tagOLend();

   bool tagLI();

   bool tagLIend();

   // image

   bool tagImg(String file_name);

   // complete

   bool complete();
 };

} // namespace App

#endif

