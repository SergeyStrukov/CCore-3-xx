/* TagTest.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_TagTest_h
#define App_TagTest_h

#include <inc/ErrorId.h>

#include <CCore/inc/String.h>

namespace App {

/* classes */

class TagTest;

/* class TagTest */

class TagTest : NoCopy
 {
   enum BlockType
    {
     NoBlock,

     Block_H1,
     Block_H2,
     Block_H3,
     Block_H4,
     Block_H5,
     Block_P,
     Block_PRE,
     Block_OL,
     Block_UL
    };

   BlockType block = NoBlock ;

  public:

   enum ErrorCode
    {
     Error_NoBlock = 1,
    };

   static StrLen ToString(int code);

   class TagErrorId : public ErrorId
    {
     public:

      TagErrorId() {}

      TagErrorId(ErrorCode code) : ErrorId(code,ToString) {}
    };

   TagTest() {}

   // frame

   TagErrorId frame(String str);

   // text

   TagErrorId tagH1();

   TagErrorId tagH1end();

   TagErrorId tagH2();

   TagErrorId tagH2end();

   TagErrorId tagH3();

   TagErrorId tagH3end();

   TagErrorId tagH4();

   TagErrorId tagH4end();

   TagErrorId tagH5();

   TagErrorId tagH5end();

   TagErrorId tagP();

   TagErrorId tagPend();

   TagErrorId tagP(String tclass);

   TagErrorId tagPRE();

   TagErrorId tagPREend();

   // format

   TagErrorId tagBR();

   TagErrorId tagB();

   TagErrorId tagBend();

   TagErrorId tagI();

   TagErrorId tagIend();

   TagErrorId tagU();

   TagErrorId tagUend();

   TagErrorId tagSUB();

   TagErrorId tagSUBend();

   TagErrorId tagSUP();

   TagErrorId tagSUPend();

   TagErrorId tagSPAN(String tclass);

   TagErrorId tagSPANend();

   // hyperlink

   TagErrorId tagA(String url);

   TagErrorId tagA(String type,String url);

   TagErrorId tagAname(String name);

   TagErrorId tagAend();

   // list

   TagErrorId tagOL();

   TagErrorId tagOLend();

   TagErrorId tagUL();

   TagErrorId tagULend();

   TagErrorId tagLI();

   TagErrorId tagLIend();

   // image

   TagErrorId tagImg(String file_name);

   // complete

   TagErrorId complete();
 };

} // namespace App

#endif


