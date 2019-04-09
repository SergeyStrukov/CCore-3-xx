/* ProcessUtils.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ProcessUtils_h
#define CCore_inc_ProcessUtils_h

#include <CCore/inc/GenFile.h>

namespace CCore {

/* classes */

struct FromProgram;

class UnixRootDir;

class UnixHomeDir;

/* struct FromProgram */

struct FromProgram
 {
  StrLen str;
  bool ok = false ;

  FromProgram(StrLen cmdline,PtrLen<char> result_buf);
 };

/* class UnixRootDir */

class UnixRootDir : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen str;
   bool done = false ;

  private:

   void make();

  public:

   UnixRootDir() {}

   StrLen get()
    {
     if( Change(done,true) ) make();

     return str;
    }
 };

/* class UnixHomeDir */

class UnixHomeDir : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen str;
   bool done = false ;

  private:

   void make();

  public:

   UnixHomeDir() {}

   StrLen get()
    {
     if( Change(done,true) ) make();

     return str;
    }
 };

} // namespace CCore

#endif

