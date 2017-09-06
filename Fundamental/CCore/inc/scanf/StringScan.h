/* StringScan.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_StringScan_h
#define CCore_inc_StringScan_h

#include <CCore/inc/String.h>

#include <CCore/inc/scanf/ScanTools.h>

namespace CCore {

/* classes */

//enum StringScanType;

struct StringScanOpt;

class StringScan;

class StringSetScan;

/* enum StringScanType */

enum StringScanType
 {
  StringScanQuote,
  StringScanToSpace,
  StringScanToPunct,

  StringScanDefault = StringScanToPunct
 };

template <CharPeekType Dev>
bool Parse_try(Dev &dev,StringScanType &ret)
 {
  typename Dev::Peek peek(dev);

  if( !peek )
    {
     return false;
    }
  else
    {
     switch( *peek )
       {
        case 'q' : case 'Q' : ret=StringScanQuote;   ++dev; return true;
        case 's' : case 'S' : ret=StringScanToSpace; ++dev; return true;
        case 'p' : case 'P' : ret=StringScanToPunct; ++dev; return true;
       }

     return false;
    }
 }

/* struct StringScanOpt */

struct StringScanOpt
 {
  StringScanType type;

  void setDefault()
   {
    type=StringScanDefault;
   }

  StringScanOpt() { setDefault(); }

  StringScanOpt(const char *ptr,const char *lim);

  //
  // [.q|.Q|.s|.S|.p|.P]
  //
 };

/* class StringScan */

class StringScan : NoCopy
 {
   String &ret;

  private:

   void scanQuote(ScannerType &inp)
    {
     PassChars(inp,'"');

     PrintString out;

     for(; +inp ;++inp)
       {
        char ch=*inp;

        if( ch=='"' )
          {
           ++inp;

           ret=out.close();

           return;
          }
        else
          {
           out.put(ch);
          }
       }

     inp.fail();
    }

   void scanToSpace(ScannerType &inp)
    {
     PrintString out;

     for(char ch; +inp && !CharIsSpace(ch=*inp) ;++inp) out.put(ch);

     ret=out.close();
    }

   void scanToPunct(ScannerType &inp)
    {
     PrintString out;

     for(char ch; +inp && !CharIsSpaceOrPunct(ch=*inp) ;++inp) out.put(ch);

     ret=out.close();
    }

  public:

   explicit StringScan(String &ret_) : ret(ret_) {}

   void scan(ScannerType &inp,StringScanOpt opt)
    {
     ret=Empty;

     switch( opt.type )
       {
        case StringScanQuote : scanQuote(inp); break;
        case StringScanToSpace : scanToSpace(inp); break;
        case StringScanToPunct : scanToPunct(inp); break;
       }
    }
 };

/* class StringSetScan */

class StringSetScan : NoCopy
 {
   ulen index = 0 ;

   struct Rec
    {
     StrLen str;
     ulen index;

     Rec(StrLen str_) : str(str_),index(0) {}
    };

   DynArray<Rec> list;

  private:

   static PtrLen<Rec> Select(PtrLen<Rec> r,char ch,ulen off);

   static PtrLen<Rec> Select(PtrLen<Rec> r,ulen off);

   void prepare();

  public:

   StringSetScan(std::initializer_list<const char *> zstr_list);

   StringSetScan(std::initializer_list<StrLen> str_list);

   ~StringSetScan();

   using PrintProxyType = ulen ;

   operator ulen() const { return index; }

   void scan(ScannerType &inp)
    {
     index=0;

     auto r=Range(list);
     ulen off=0;

     for(; +inp ;++inp)
       {
        char ch=*inp;

        auto next_r=Select(r,ch,off);

        if( !next_r ) break;

        r=next_r;
        off++;
       }

     r=Select(r,off);

     if( !r )
       {
        inp.fail();
       }
     else
       {
        index=r->index;
       }
    }
 };

} // namespace CCore

#endif


