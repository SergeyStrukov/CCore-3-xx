/* default.vml.ddl */
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

Param Data = {

//-----------------------------------------------

.CCORE_ROOT = "../.." ,

//-----------------------------------------------

.SRC_PATH_LIST = {"src"} ,

.CCOPT_EXTRA = {"-I."} ,

.TARGET = "#HOME;/bin/CCore-VMakeList.exe",

//-----------------------------------------------

.target = TargetConsole
 
//-----------------------------------------------

};

