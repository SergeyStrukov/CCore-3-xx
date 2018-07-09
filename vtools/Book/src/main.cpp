/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

#include <CCore/inc/Abort.h>

/* main() */

using namespace App;

const AbortMsgFuncType CCore::AbortMsgFunc = AbortMsgBox ;

int main(int argc,const char *argv[])
 {
  return AppMain<AppProp>(StartDisplay(),argc,argv);
 }




