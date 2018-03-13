/* PretextFileToMem.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PretextFileToMem_h
#define CCore_inc_PretextFileToMem_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace CCore {

/* classes */

class PretextMap;

template <class FileToMem,auto &Pretext> class PretextFileToMem;

/* class PretextMap */

class PretextMap : NoCopy
 {
   struct Rec
    {
     StrLen file_name;
     StrLen text;

     bool operator < (const Rec &obj) const { return StrLess(file_name,obj.file_name); }
    };

   DynArray<Rec> list;
   bool ready = false ;
   bool check_dev;

  protected:

   void add(StrLen file_name,StrLen text);

   virtual void prepare()=0;

  public:

   explicit PretextMap(bool check_dev=true) noexcept;

   ~PretextMap();

   struct Result
    {
     PtrLen<const uint8> text;
     bool ok;
    };

   Result operator () (StrLen file_name);
 };

/* class PretextFileToMem<FileToMem,auto &Pretext> */

template <class FileToMem,auto &Pretext>
class PretextFileToMem
 {
   FileToMem file;

   PtrLen<const uint8> text;

  public:

   template <class ... SS>
   PretextFileToMem(SS && ... ss,StrLen file_name,ulen max_len)
    {
     if( auto result=Pretext(file_name) ; result.ok )
       {
        text=result.text;
       }
     else
       {
        file=FileToMem( std::forward<SS>(ss)... ,file_name,max_len);

        text=Range(file);
       }
    }

   ~PretextFileToMem() {}

   // range access

   const uint8 * getPtr_const() const { return text.ptr; }

   const uint8 * getPtr() const { return text.ptr; }

   ulen getLen() const { return text.len; }
 };

} // namespace CCore

#endif

