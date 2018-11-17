/* BookLab.cpp */
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

/* test() */

#if 0

template <class T>
void testOne(ObjectDomain *domain)
 {
  static_assert( Has_keepAlive<T> ,"has keepAlive");

  ExtObjPtr<T> test(domain);
 }

template <class ... TT>
void testList(ObjectDomain *domain)
 {
  ( testOne<TT>(domain) , ... );
 }

void test(ObjectDomain *domain)
 {
  testList<Font,Format,SingleLine,DoubleLine,Frame,FrameList,Page,Element,ElementList,Defaults,
           Scope,Section,Bitmap,Collapse,Item,ItemList,TextList,Border,Cell,Table,Link,Span,TextLine,
           FixedText,OneLine,MultiLine,Text>(domain);
 }

#endif

/* name functions */

template <OneOfTypes<Char,char> Ch>
bool TestKeyword(PtrLen<const Ch> str)
 {
  if( !str ) return false;

  switch( str[0] )
    {
     case 'c' :
      {
       ++str;

       if( str.len==4 && str[0]=='o' && str[1]=='n' && str[2]=='s' && str[3]=='t' ) return true; else return false;
      }

     case 'i' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'n' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'c' :
                {
                 ++str;

                 if( str.len==4 && str[0]=='l' && str[1]=='u' && str[2]=='d' && str[3]=='e' ) return true; else return false;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==0 ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'p' :
           {
            ++str;

            if( str.len==0 ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'n' :
      {
       ++str;

       if( str.len==3 && str[0]=='u' && str[1]=='l' && str[2]=='l' ) return true; else return false;
      }

     case 's' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'c' :
           {
            ++str;

            if( str.len==3 && str[0]=='o' && str[1]=='p' && str[2]=='e' ) return true; else return false;
           }

          case 'i' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return true;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return true; else return false;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return true; else return false;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return true; else return false;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return true; else return false;
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          case 't' :
           {
            ++str;

            if( str.len==4 && str[0]=='r' && str[1]=='u' && str[2]=='c' && str[3]=='t' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 't' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( str.len==2 && str[0]=='x' && str[1]=='t' ) return true; else return false;
           }

          case 'y' :
           {
            ++str;

            if( str.len==2 && str[0]=='p' && str[1]=='e' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'u' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'i' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return true;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return true; else return false;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return true; else return false;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return true; else return false;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return true; else return false;
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          case 'l' :
           {
            ++str;

            if( str.len==2 && str[0]=='e' && str[1]=='n' ) return true; else return false;
           }

          default: return false;
         }
      }

     default: return false;
    }
 }

bool IsNameFirst_char(char ch)
 {
  return PropTable::Object[ch]==CharNameFirst;
 }

bool IsNameNext_char(char ch)
 {
  return PropTable::Object[ch]>=CharNameFirst;
 }

bool TestName(StrLen text)
 {
  if( !text ) return false;

  if( !IsNameFirst_char(*text) ) return false;

  StrLen start=text;

  for(++text; +text && IsNameNext_char(*text) ;++text);

  return ( !text || IsNameBreak_char(*text) ) && !TestKeyword( start.prefix(text) ) ;
 }

bool IsNameFirst(Char ch)
 {
  int code=ToChar(ch);

  if( code<0 ) return false;

  return IsNameFirst_char((char)code);
 }

bool IsNameNext(Char ch)
 {
  int code=ToChar(ch);

  if( code<0 ) return false;

  return IsNameNext_char((char)code);
 }

bool TestName(PtrLen<const Char> text)
 {
  if( !text ) return false;

  if( !IsNameFirst(*text) ) return false;

  PtrLen<const Char> start=text;

  for(++text; +text && IsNameNext(*text) ;++text);

  return ( !text || IsNameBreak(*text) ) && !TestKeyword( start.prefix(text) ) ;
 }

/* class PropTable */

PropTable::PropTable()
 {
  setSet(GetCLetterChars(),CharNameFirst);
  setSet(GetDigitChars(),CharNameNext);
 }

PropTable PropTable::Object;

/* class NextIndex */

Index NextIndex::getIndex()
 {
  unsigned ret=next_index;

  if( !ret )
    {
     Printf(Exception,"App::BookLab::NextIndex::getIndex() : too many objects");
    }

  next_index++;

  return {ret};
 }

/* class TempData */

TempData::TempData()
 {
 }

TempData::~TempData()
 {
 }

StrLen TempData::getTypeName() const
 {
  StrLen ret;

  data.getPtr().apply( [&] (auto *ptr) { ret=GetTypeName(ptr); } );

  return ret;
 }

bool TempData::copy(Ref cursor)
 {
  bool ret=false;

  cursor.pad.apply( [&] (auto *ptr) { if( ptr ) ret=copy(ptr,cursor.mode); } );

  return ret;
 }

bool TempData::past(Ref cursor)
 {
  bool ret=false;

  cursor.pad.apply( [&] (auto *ptr) { if( ptr ) ret=past(ptr,cursor.mode); } );

  return ret;
 }

void TempData::del()
 {
  data.destroy();
 }

/* class Book::ScopeContext */

class Book::ScopeContext : NoCopy
 {
   unsigned level = 100 ;

  private:

   void subs(IntAnyObjPtr<Scope,Doc>,Font *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Format *ptr)
    {
     set(scope,ptr->font);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,SingleLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc>,DoubleLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Page *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Scope *ptr)
    {
     set(scope,ptr->defs);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Section *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,Bitmap *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Collapse *ptr)
    {
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,TextList *ptr)
    {
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,Border *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Cell *ptr)
    {
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Table *ptr)
    {
     set(scope,ptr->border);
     set(scope,ptr->table.cells);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Link *ptr)
    {
     set(scope,ptr->page);
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,FixedText *ptr)
    {
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

   void subs(IntAnyObjPtr<Scope,Doc>,OneLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc>,MultiLine *)
    {
    }

   void subs(IntAnyObjPtr<Scope,Doc> scope,Text *ptr)
    {
     set(scope,ptr->placement);
     set(scope,ptr->format);
     set(scope,ptr->list);
    }

  private:

   template <class T>
   void set(IntAnyObjPtr<Scope,Doc> scope,T *ptr)
    {
     LockUse lock(level);

     ptr->scope=scope;

     subs(scope,ptr);
    }

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *obj) { if( obj ) set(scope,obj); } );
    }

   template <class T>
   void set(IntAnyObjPtr<Scope,Doc> scope,IntObjPtr<T> ptr)
    {
     if( +ptr ) set(scope,ptr.getPtr());
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,IntObjPtr<Scope> ptr)
    {
     if( +ptr )
       {
        LockUse lock(level);

        ptr->scope=scope;

        subs(ptr,ptr.getPtr());
       }
    }

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,IntAnyObjPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (IntObjPtr<auto> ptr) { set(scope,ptr); } );
    }

  private:

   template <class ... TT>
   void set(IntAnyObjPtr<Scope,Doc> scope,NamedPtr<TT...> &obj)
    {
     if( obj.isAnonym() ) set(scope,obj.ptr.getPtr());
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Defaults &obj)
    {
     set(scope,obj.singleLine);
     set(scope,obj.doubleLine);
     set(scope,obj.collapseFormat);
     set(scope,obj.bulletFormat);
     set(scope,obj.border);
     set(scope,obj.textFormat);
     set(scope,obj.fixedFormat);
     set(scope,obj.placement);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Element &obj)
    {
     set(scope,obj.ptr);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Frame &obj)
    {
     set(scope,obj.line);
     set(scope,obj.body);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Item &obj)
    {
     set(scope,obj.list);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,Span &span)
    {
     set(scope,span.format);
     set(scope,span.ref);
    }

   void set(IntAnyObjPtr<Scope,Doc> scope,TextLine &line)
    {
     set(scope,line.list);
    }

   template <OneOfTypes<ElementList,FrameList,ItemList> List>
   void set(IntAnyObjPtr<Scope,Doc> scope,List &list)
    {
     for(auto &obj : ForIntList(list) ) set(scope,obj);
    }

   template <class T>
   void set(IntAnyObjPtr<Scope,Doc> scope,DynArray<T> &list)
    {
     for(T &obj : list ) set(scope,obj);
    }

  public:

   ScopeContext() {}

   void set(IntObjPtr<Doc> ptr)
    {
     set(ptr,ptr->start);
     set(ptr,ptr->defs);
     set(ptr,ptr->list);
    }
 };

/* class Book */

void Book::setScope()
 {
  if( +doc )
    {
     ScopeContext ctx;

     ctx.set(doc);
    }
 }

Book::Book()
 {
 }

Book::~Book()
 {
 }

void Book::blank()
 {
  doc=Null;
  linked=true;

  domain.collect();
 }

ErrorText Book::link(PtrLen<char> ebuf) // TODO
 {
  PrintBuf eout(ebuf);
  ReportExceptionTo report(eout);

  try
    {
     Printf(Exception,"not implemented");

     return Success;
    }
  catch(CatchType)
    {
     return eout.close();
    }
 }

} // namespace BookLab
} // namespace App

