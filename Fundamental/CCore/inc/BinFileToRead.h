/* BinFileToRead.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_BinFileToRead_h
#define CCore_inc_BinFileToRead_h

#include <CCore/inc/GenFile.h>
#include <CCore/inc/RefObjectBase.h>
#include <CCore/inc/ToMemBase.h>

namespace CCore {

/* guard functions */

void GuardBinFileTooLong(StrLen file_name,ulen max_len,FilePosType file_len);

/* classes */

class AbstractBinFileToRead;

class BinFileToMem;

/* class AbstractBinFileToRead */

class AbstractBinFileToRead : NoCopy
 {
  protected:

   bool is_opened = false ;
   FilePosType file_len = 0 ;

  protected:

   void reset()
    {
     is_opened=false;
     file_len=0;
    }

  public:

   virtual void open(StrLen file_name,FileOpenFlags oflags=Open_Read) =0;

   virtual void close() =0;

   bool isOpened() const { return is_opened; }

   FilePosType getLen() const { return file_len; }

   virtual ulen read(FilePosType off,uint8 *buf,ulen len) =0;

   virtual void read_all(FilePosType off,uint8 *buf,ulen len) =0;
 };

/* type BinFileToReadBase */

using BinFileToReadBase = RefObjectBase<AbstractBinFileToRead> ;

/* GetNullBinFileToReadPtr() */

BinFileToReadBase * GetNullBinFileToReadPtr();

/* type BinFileToRead */

using BinFileToRead = RefObjectHook<BinFileToReadBase,AbstractBinFileToRead,GetNullBinFileToReadPtr> ;

/* class BinFileToMem */

class BinFileToMem : public ToMemBase
 {
  public:

   BinFileToMem() noexcept {}

   BinFileToMem(BinFileToRead file,StrLen file_name,ulen max_len=MaxULen);

   ~BinFileToMem() {}

   // std move

   BinFileToMem(BinFileToMem &&obj) noexcept = default ;

   BinFileToMem & operator = (BinFileToMem &&obj) noexcept = default ;

   // swap/move objects

   void objSwap(BinFileToMem &obj)
    {
     Swap<ToMemBase>(*this,obj);
    }

   explicit BinFileToMem(ToMoveCtor<BinFileToMem> obj) : ToMemBase(obj.template cast<ToMemBase>()) {}
 };

} // namespace CCore

#endif

