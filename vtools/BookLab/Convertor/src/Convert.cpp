/* Convert.cpp */
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

#include <inc/Convert.h>

#include <CCore/inc/Path.h>

namespace App {

/* class OName */

ulen OName::Next = 1 ;

/* class Span */

StrLen Span::GetTail(SpanType type)
 {
  if( type.bold )
    {
     if( type.italic )
       {
        switch( type.effect )
          {
           case Underline : return ",&fmt_biu"_c;
           case Strikeout : return ",&fmt_bis"_c;
           case Hyperlink : return ",&fmt_bih"_c;
           default: return ",&fmt_bi"_c;
          }
       }
     else
       {
        switch( type.effect )
          {
           case Underline : return ",&fmt_bu"_c;
           case Strikeout : return ",&fmt_bs"_c;
           case Hyperlink : return ",&fmt_bh"_c;
           default: return ",&fmt_b"_c;
          }
       }
    }
  else
    {
     if( type.italic )
       {
        switch( type.effect )
          {
           case Underline : return ",&fmt_iu"_c;
           case Strikeout : return ",&fmt_is"_c;
           case Hyperlink : return ",&fmt_ih"_c;
           default: return ",&fmt_i"_c;
          }
       }
     else
       {
        switch( type.effect )
          {
           case Underline : return ",&fmt_u"_c;
           case Strikeout : return ",&fmt_s"_c;
           case Hyperlink : return ",&fmt_h"_c;
           default: return ""_c;
          }
       }
    }
 }

/* class Text */

StrLen Text::GetTail(TextType type)
 {
  switch( type )
    {
     case TextH1 : return " , &fmt_h1 , &align_h1 "_c;
     case TextH2 : return " , &fmt_h2 , &align_h2 "_c;
     case TextH3 : return " , &fmt_h3 , &align_h3 "_c;
     case TextH4 : return " , &fmt_h4 , &align_h4 "_c;
     case TextH5 : return " , &fmt_h5 , &align_h5 "_c;
     case TextLI : return " , &fmt_li , &align_li "_c;

     default: return Null;
    }
 }

/* class Image */

StrLen Image::GetFileName(StrLen file_name)
 {
  SplitPath split1(file_name);
  SplitName split2(split1.path);
  SplitExt split3(split2.name);

  file_name.len-=split3.ext.len;

  return file_name;
 }

/* class Frame */

OName Frame::getName() const
 {
  OName ret(Nothing);

  ptr.apply(GetName{ret});

  return ret;
 }

 // print object

void Frame::print(PrintBase &out) const
 {
  ptr.apply(Print{out});
 }

/* class Convert::Builder */

struct Convert::Builder::Elaborate
 {
  BuilderPtr &ret;

  template <class T>
  void operator () (T &obj)
   {
    ret=&obj;
   }
 };

auto Convert::Builder::elaborate() -> BuilderPtr
 {
  BuilderPtr ret;

  ptr.apply(Elaborate{ret});

  return ret;
 }

template <class T,class S> requires( CanPopTypes<T,S> )
void Convert::Builder::Add(T *obj,S *top)
 {
  if( obj && top )
    {
     obj->add(top->complete());
    }
 }

template <class T>
void Convert::Builder::Add(T *obj,Builder &top)
 {
  top.elaborate().apply( [obj] (auto *top) { Add(obj,top); } );
 }

template <class T,class ... SS>
bool Convert::Builder::check(SS && ... ss)
 {
  bool ret=false;

  elaborate().applyFor<T>( [&] (T *obj) { if( obj ) ret=obj->check( std::forward<SS>(ss)... ); } );

  return ret;
 }

template <class T>
bool Convert::Builder::canPop()
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { ret=CanPopTypes<std::decay_t<decltype(*obj)>,T>; } );

  return ret;
 }

void Convert::Builder::pop(Builder &top)
 {
  elaborate().apply( [&] (auto *obj) { Add(obj,top); } );

  top=std::move(*this);
 }

bool Convert::Builder::word(String word)
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->word(word); } );

  return ret;
 }

bool Convert::Builder::tagB()
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->tagB(); } );

  return ret;
 }

bool Convert::Builder::tagBend()
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->tagBend(); } );

  return ret;
 }

bool Convert::Builder::tagI()
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->tagI(); } );

  return ret;
 }

bool Convert::Builder::tagIend()
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->tagIend(); } );

  return ret;
 }

bool Convert::Builder::tagImg(String file_name)
 {
  bool ret=false;

  elaborate().apply( [&] (auto *obj) { if( obj ) ret=obj->tagImg(file_name); } );

  return ret;
 }

template <class T>
T * Convert::Builder::getOf()
 {
  return elaborate().castPtr<T>();
 }

/* class Convert */

void Convert::start()
 {
  Printf(out,"/* #;.book.ddl */\n\n",name);

  Printf(out,"include <#;.style.ddl>\n\n",name);

  Putobj(out,"scope Pages {\n\n");
 }

void Convert::complete(FrameList list)
 {
  Printf(out,"Page page1 = { Pages##PageName , #; };\n\n",list);

  Putobj(out,list.getFrames());

  Putobj(out,"} // scope Pages\n\n");

  Putobj(out,"Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;\n\n");
 }

template <class T,class ... SS>
bool Convert::push(SS && ... ss)
 {
  if( top.canPop<T>() )
    {
     stack.append_fill( std::move(top) );

     top=Builder( T( std::forward<SS>(ss)... ) );

     return true;
    }

  return false;
 }

template <class T,class ... SS>
bool Convert::pop(SS && ... ss)
 {
  if( top.check<T>( std::forward<SS>(ss)... ) )
    {
     if( ulen len=stack.getLen() )
       {
        len--;

        stack[len].pop(top);

        stack.shrink_one();

        return true;
       }
    }

  return false;
 }

Convert::Convert(StrLen output_file_name)
 : out(output_file_name),

   top(FrameListBuilder())
 {
  SplitPath split1(output_file_name);
  SplitName split2(split1.path);
  SplitFullExt split3(split2.name);

  name=String(split3.name);

  start();
 }

 // word

bool Convert::word(String word)
 {
  return top.word(word);
 }

 // text

bool Convert::tagH1()
 {
  return push<TextBuilder>(TextH1);
 }

bool Convert::tagH1end()
 {
  return pop<TextBuilder>(TextH1);
 }

bool Convert::tagH2()
 {
  return push<TextBuilder>(TextH2);
 }

bool Convert::tagH2end()
 {
  return pop<TextBuilder>(TextH2);
 }

bool Convert::tagH3()
 {
  return push<TextBuilder>(TextH3);
 }

bool Convert::tagH3end()
 {
  return pop<TextBuilder>(TextH3);
 }

bool Convert::tagH4()
 {
  return push<TextBuilder>(TextH4);
 }

bool Convert::tagH4end()
 {
  return pop<TextBuilder>(TextH4);
 }

bool Convert::tagH5()
 {
  return push<TextBuilder>(TextH5);
 }

bool Convert::tagH5end()
 {
  return pop<TextBuilder>(TextH5);
 }

bool Convert::tagP()
 {
  return push<TextBuilder>(TextP);
 }

bool Convert::tagPend()
 {
  return pop<TextBuilder>(TextP);
 }

bool Convert::tagP(String pclass) // TODO
 {
  Used(pclass);

  return tagP();
 }

bool Convert::tagPRE() // TODO
 {
  return tagP();
 }

bool Convert::tagPREend() // TODO
 {
  return tagPend();
 }

bool Convert::tagSPAN(String pclass) // TODO
 {
  Used(pclass);

  return true;
 }

bool Convert::tagSPANend() // TODO
 {
  return true;
 }


 // format

bool Convert::tagB()
 {
  return top.tagB();
 }

bool Convert::tagBend()
 {
  return top.tagBend();
 }

bool Convert::tagI()
 {
  return top.tagI();
 }

bool Convert::tagIend()
 {
  return top.tagIend();
 }

 // hyperlink

bool Convert::tagA(String url)
 {
  if( TextBuilder *text=top.getOf<TextBuilder>() )
    {
     return push<ABuilder>(url,text->getSpanType());
    }

  if( ListItemBuilder *item=top.getOf<ListItemBuilder>() )
    {
     return push<ABuilder>(url,item->getSpanType());
    }

  return false;
 }

bool Convert::tagAend()
 {
  return pop<ABuilder>();
 }

 // list

bool Convert::tagOL()
 {
  return push<TextListBuilder>();
 }

bool Convert::tagOLend()
 {
  return pop<TextListBuilder>();
 }

bool Convert::tagLI()
 {
  if( TextListBuilder *list=top.getOf<TextListBuilder>() )
    {
     return push<ListItemBuilder>(list->nextIndex());
    }

  return false;
 }

bool Convert::tagLIend()
 {
  return pop<ListItemBuilder>();
 }

 // image

bool Convert::tagImg(String file_name)
 {
  return top.tagImg(file_name);
 }

 // complete

bool Convert::complete()
 {
  if( stack.getLen() ) return false;

  if( FrameListBuilder *obj=top.getOf<FrameListBuilder>() )
    {
     complete(obj->complete());

     return true;
    }

  return false;
 }

} // namespace App

