/* LineInput.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_LineInput_h
#define CCore_inc_LineInput_h

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/InputUtils.h>

namespace CCore {

/* classes */

template <ReadConType ReadCon,ulen MaxLen=80> class LineInput;

/* class LineInput<ReadCon,ulen MaxLen> */

template <ReadConType ReadCon,ulen MaxLen>
class LineInput : NoCopy
 {
   ReadCon con;

   char buf[MaxLen];
   ulen len;

  private:

   bool process(Symbol ch,PtrLen<const char> &ret);

  public:

   template <class ... SS>
   explicit LineInput(SS && ... ss) : con( std::forward<SS>(ss)... ),len(0) {}

   ~LineInput() {}

   PtrLen<const char> get();

   bool get(TimeScope time_scope,PtrLen<const char> &ret);
 };

template <ReadConType ReadCon,ulen MaxLen>
bool LineInput<ReadCon,MaxLen>::process(Symbol ch,PtrLen<const char> &ret)
 {
  switch( ToChar(ch) )
    {
     case '\r' :
     case '\n' :
      {
       con.put("\r\n"_c);

       ret=Range_const(buf,Replace_null(len));
      }
     return true;

     case '\b' :
      {
       if( len>0 )
         {
          len=PopSymbol(buf,len);

          con.put("\b \b"_c);
         }
      }
     break;

     default:
      {
       if( len+SymbolLen(ch)<=MaxLen && CharIsPrintable(ch) )
         {
          len=PutSymbol(buf,len,ch);

          con.put(ch);
         }
      }
    }

  return false;
 }

template <ReadConType ReadCon,ulen MaxLen>
PtrLen<const char> LineInput<ReadCon,MaxLen>::get()
 {
  PtrLen<const char> ret;

  while( !process(con.get(),ret) );

  return ret;
 }

template <ReadConType ReadCon,ulen MaxLen>
bool LineInput<ReadCon,MaxLen>::get(TimeScope time_scope,PtrLen<const char> &ret)
 {
  for(;;)
    {
     Symbol ch;

     if( !con.get(time_scope,ch) ) return false;

     if( process(ch,ret) ) return true;
    }
 }

} // namespace CCore

#endif


