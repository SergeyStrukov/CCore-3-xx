/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: SubLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Abort.h>

/* main() */

using namespace App;

const AbortMsgFuncType CCore::AbortMsgFunc = AbortMsgBox ;

int main()
 {
  return Main(StartDisplay());
 }




