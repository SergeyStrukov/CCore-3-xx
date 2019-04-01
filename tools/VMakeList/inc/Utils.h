/* Utils.h */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_Utils_h
#define App_Utils_h

#include <CCore/inc/GenFile.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct FromProgram;

class RootDir;

class HomeDir;

/* struct FromProgram */

struct FromProgram
 {
  StrLen str;
  bool ok = false ;

  FromProgram(StrLen cmdline,PtrLen<char> result_buf);
 };

/* class RootDir */

class RootDir : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen str;
   bool done = false ;

  private:

   void make();

  public:

   RootDir() {}

   StrLen get()
    {
     if( Change(done,true) ) make();

     return str;
    }
 };

/* class HomeDir */

class HomeDir : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen str;
   bool done = false ;

  private:

   void make();

  public:

   HomeDir() {}

   StrLen get()
    {
     if( Change(done,true) ) make();

     return str;
    }
 };

} // namespace App

#endif


