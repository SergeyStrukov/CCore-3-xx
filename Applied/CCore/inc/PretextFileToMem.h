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

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

class PretextMap;

template <class FileToMem,auto &Pretext> class PretextFileToMem;

/* class PretextMap */

class PretextMap : NoCopy
 {
  protected:

   void add(StrLen file_name,StrLen text);

  public:

   PretextMap();

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

   PretextFileToMem(StrLen file_name,ulen max_len)
    {
     if( auto result=Pretext(file_name) ; result.ok )
       {
        text=result.text;
       }
     else
       {
        file=FileToMem(file_name,max_len);

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

