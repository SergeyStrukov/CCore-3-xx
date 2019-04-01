/* Utils.cpp */
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

#include <inc/Utils.h>

#include <CCore/inc/Exception.h>

namespace App {

namespace Private_Utils {

/* struct FromProgram */

struct FromProgram
 {
  StrLen str;
  bool ok = false ;

  FromProgram(StrLen cmd_line,PtrLen<char> result) // TODO
   {
    Used(cmd_line);
    Used(result);
   }
 };

} // namespace Private_Utils

using namespace Private_Utils;

/* class RootDir */

void RootDir::make()
 {
  FromProgram result("cygpath -m -a --codepage UTF8 /"_c,Range(buf));

  if( result.ok )
    {
     str=result.str;
    }
  else
    {
     Printf(Exception,"App : cannot find root path");
    }
 }

/* class HomeDir */

void HomeDir::make()
 {
  FromProgram result("cygpath -m -a --codepage UTF8 ~"_c,Range(buf));

  if( result.ok )
    {
     str=result.str;
    }
  else
    {
     Printf(Exception,"App : cannot find home path");
    }
 }

} // namespace App

