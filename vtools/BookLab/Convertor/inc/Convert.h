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

namespace App {

/* classes */

struct SpanType;

class Span;

class Text;

class Image;

class Frame;

class FrameList;

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

  public:

   Span(SpanType type_,String text_,String url_=Null) : type(type_),text(text_),url(url_) {}
 };

/* enum TextType */

enum TextType
 {
  TextP,
  TextH1,
  TextH2,
  TextH3,
  TextH4,
  TextH5
 };

/* class Text */

class Text
 {
   TextType type;
   DynArray<Span> list;

  public:

   explicit Text(TextType type_) : type(type_) {}

   TextType getType() const { return type; }

   void add(Span span) { list.append_copy(span); }
 };

/* class Image */

class Image
 {
   String file_name;

  public:

   explicit Image(String file_name_) : file_name(file_name_) {}
 };

/* class Frame */

class Frame
 {
   AnyObjectPtr<> ptr;

  public:

   explicit Frame(OneOfTypes<Text,Image> &&obj) : ptr(std::move(obj)) {}
 };

/* class FrameList */

class FrameList
 {
   DynArray<Frame> list;

  public:

   FrameList() {}

   void add(OneOfTypes<Text,Image> &&obj) { list.append_fill(Frame(std::move(obj))); }
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

      void add(OneOfTypes<Text,Image> &&obj) { result.add(std::move(obj)); }

      FrameList complete() { return std::move(result); }
    };

   class Builder
    {
      using BuilderPtr = AnyPtr<TextBuilder,FrameListBuilder> ;

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
      explicit Builder(T &&obj)  : ptr(std::move(obj)) {}

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
    };

  private:

   String name;

   PrintFile out;

   DynArray<Builder> stack;

   Builder top;

  private:

   void start();

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

#if 0

class Convert : NoCopy
 {
   String name;

   PrintFile out;

   enum State
    {
     Start = 0,

     TagH1,
     TagH2,
     TagH3,
     TagH4,
     TagH5,
     TagP,

     TagB,
     TagI,
     TagA,

     TagOL,
     TagLI
    };

   State state = Start ;
   unsigned level = 0 ;

   ulen ind = 1 ;
   bool first = true ;

   State parent = Start ;

   unsigned number[10];

  private:

   void start()
    {
     Printf(out,"/* #;.book.ddl */\n\n",name);

     Printf(out,"include <#;.style.ddl>\n\n",name);

     Putobj(out,"scope Pages {\n\n");
    }

   // H1

   void startH1()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH1(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH1()
    {
     Putobj(out,"} , &fmt_h1 , &align_h1 } ;\n\n");
    }

   // H2

   void startH2()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH2(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH2()
    {
     Putobj(out,"} , &fmt_h2 , &align_h2 } ;\n\n");
    }

   // H3

   void startH3()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH3(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH3()
    {
     Putobj(out,"} , &fmt_h3 , &align_h3 } ;\n\n");
    }

   // H4

   void startH4()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH4(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH4()
    {
     Putobj(out,"} , &fmt_h4 , &align_h4 } ;\n\n");
    }

   // H5

   void startH5()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH5(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH5()
    {
     Putobj(out,"} , &fmt_h5 , &align_h5 } ;\n\n");
    }

   // P

   void startP()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordP(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endP()
    {
     Putobj(out,"} } ;\n\n");
    }

   // B

   void startB() {}

   void wordB(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_b}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_b}\n",DDLString(word));
       }
    }

   void endB() {}

   // I

   void startI() {}

   void wordI(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_i}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_i}\n",DDLString(word));
       }
    }

   void endI() {}

   // A

   void startA(String url) { Used(url); }

   void wordA(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_u}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_u}\n",DDLString(word));
       }
    }

   void endA() {}

   // OL

   void startOL()
    {
     Printf(out,"TextList text#; = { {\n",ind++);

     number[level]=1;
    }

   void endOL()
    {
     Putobj(out,"} } ;\n\n");
    }

   // LI

   void startLI()
    {
     unsigned num=number[level]++;

     if( num==1 )
       {
        Printf(out,"{'#;.',{",num);
       }
     else
       {
        Printf(out,",{'#;.',{",num);
       }
    }

   void wordLI(String word)
    {
    }

   void endLI()
    {
     Putobj(out,"}}\n");
    }

   // Img

   void makeImg(String file_name) { makeImg(Range(file_name)); }

   void makeImg(StrLen file_name)
    {
     SplitPath split1(file_name);
     SplitName split2(split1.path);
     SplitExt split3(split2.name);

     file_name.len-=split3.ext.len;

     Printf(out,"Bitmap text#; = { ",ind++);

     Printf(out,"#; + '.bitmap' ",DDLPrintableString(file_name));

     Putobj(out," };\n\n");
    }

  public:

   explicit Convert(StrLen output_file_name)
    : out(output_file_name)
    {
     SplitPath split1(output_file_name);
     SplitName split2(split1.path);
     SplitFullExt split3(split2.name);

     name=String(split3.name);

     start();
    }

   ~Convert() {}

   bool word(String word)
    {
     switch( state )
       {
        case TagH1 : wordH1(word); return true;

        case TagH2 : wordH2(word); return true;

        case TagH3 : wordH3(word); return true;

        case TagH4 : wordH4(word); return true;

        case TagH5 : wordH5(word); return true;

        case TagP : wordP(word); return true;

        case TagB : wordB(word); return true;

        case TagI : wordI(word); return true;

        case TagA : wordA(word); return true;

        case TagLI : wordLI(word); return true;
       }

     return false;
    }

   bool tagH1()
    {
     if( state==Start )
       {
        startH1();

        state=TagH1;

        return true;
       }

     return false;
    }

   bool tagH1end()
    {
     if( state==TagH1 )
       {
        endH1();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH2()
    {
     if( state==Start )
       {
        startH2();

        state=TagH2;

        return true;
       }

     return false;
    }

   bool tagH2end()
    {
     if( state==TagH2 )
       {
        endH2();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH3()
    {
     if( state==Start )
       {
        startH3();

        state=TagH3;

        return true;
       }

     return false;
    }

   bool tagH3end()
    {
     if( state==TagH3 )
       {
        endH3();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH4()
    {
     if( state==Start )
       {
        startH4();

        state=TagH4;

        return true;
       }

     return false;
    }

   bool tagH4end()
    {
     if( state==TagH4 )
       {
        endH4();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH5()
    {
     if( state==Start )
       {
        startH5();

        state=TagH5;

        return true;
       }

     return false;
    }

   bool tagH5end()
    {
     if( state==TagH5 )
       {
        endH5();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagP()
    {
     if( state==Start )
       {
        startP();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagPend()
    {
     if( state==TagP )
       {
        endP();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagB()
    {
     if( state==TagP )
       {
        startB();

        state=TagB;

        return true;
       }

     return false;
    }

   bool tagBend()
    {
     if( state==TagB )
       {
        endB();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagI()
    {
     if( state==TagP )
       {
        startI();

        state=TagI;

        return true;
       }

     return false;
    }

   bool tagIend()
    {
     if( state==TagI )
       {
        endI();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagA(String url)
    {
     if( state==TagP || state==TagLI )
       {
        startA(url);

        parent=Replace(state,TagA);

        return true;
       }

     return false;
    }

   bool tagAend()
    {
     if( state==TagA )
       {
        endA();

        state=parent;

        return true;
       }

     return false;
    }

   bool tagOL()
    {
     if( state==Start || state==TagLI )
       {
        level++;

        if( level>=DimOf(number) )
          {
           return false;
          }

        startOL();

        state=TagOL;

        return true;
       }

     return false;
    }

   bool tagOLend()
    {
     if( state==TagOL && level )
       {
        endOL();

        level--;

        state=level?TagLI:Start;

        return true;
       }

     return false;
    }

   bool tagLI()
    {
     if( state==TagOL )
       {
        startLI();

        state=TagLI;

        return true;
       }

     return false;
    }

   bool tagLIend()
    {
     if( state==TagLI )
       {
        endLI();

        state=TagOL;

        return true;
       }

     return false;
    }

   bool tagImg(String file_name)
    {
     if( state==Start )
       {
        makeImg(file_name);

        return true;
       }

     return false;
    }

   bool complete()
    {
     Putobj(out,"Page page1 = { Pages#PageName , {\n");

     for(ulen i=1; i<ind ;i++)
       {
        if( i==1 )
          Printf(out,"{ &text#; }\n",i);
        else
          Printf(out,",{ &text#; }\n",i);
       }

     Putobj(out,"} };\n\n");

     Putobj(out,"} // scope Pages\n\n");

     Putobj(out,"Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;");

     return true;
    }
 };

#endif

} // namespace App

#endif

