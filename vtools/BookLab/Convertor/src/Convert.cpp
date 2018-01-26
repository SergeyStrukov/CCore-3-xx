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
#include <CCore/inc/video/PrintDDL.h>

namespace App {

/* using */

using Video::DDLString;
using Video::DDLPrintableString;

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

  elaborate().apply( [&] (auto *obj) { ret=CanPopTypes<decltype(*obj),T>; } );

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

/* class Convert */

void Convert::start()
 {
  Printf(out,"/* #;.book.ddl */\n\n",name);

  Printf(out,"include <#;.style.ddl>\n\n",name);

  Putobj(out,"scope Pages {\n\n");
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

bool Convert::tagA(String url) // TODO
 {
  Used(url);

  return false;
 }

bool Convert::tagAend() // TODO
 {
  return false;
 }

 // list

bool Convert::tagOL() // TODO
 {
  return false;
 }

bool Convert::tagOLend() // TODO
 {
  return false;
 }

bool Convert::tagLI() // TODO
 {
  return false;
 }

bool Convert::tagLIend() // TODO
 {
  return false;
 }

 // image

bool Convert::tagImg(String file_name)
 {
  return top.tagImg(file_name);
 }

 // complete

bool Convert::complete() // TODO
 {
  Putobj(out,"Page page1 = { Pages#PageName , {\n");

#if 0

  for(ulen i=1; i<ind ;i++)
    {
     if( i==1 )
       Printf(out,"{ &text#; }\n",i);
     else
       Printf(out,",{ &text#; }\n",i);
    }

#endif

  Putobj(out,"} };\n\n");

  Putobj(out,"} // scope Pages\n\n");

  Putobj(out,"Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;");

  return true;
 }

} // namespace App

