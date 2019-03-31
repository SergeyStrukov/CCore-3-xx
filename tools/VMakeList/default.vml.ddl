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

.CCORE_TARGET = "WIN32utf8" ,

//-----------------------------------------------

.SRC_PATH_LIST = {"src"} ,

.CCOPT_EXTRA = {"-I."} ,

.TARGET = "#HOME;/bin/CCore-VMakeList.exe",

//-----------------------------------------------

.target = TargetConsole ,

.tools = &ToolsData
 
//-----------------------------------------------

};

Tools ToolsData = {

//-----------------------------------------------

.CC = "/opt/gcc-8.3.0/bin/g++-8.3.0" ,
.LD = "/opt/gcc-8.3.0/bin/g++-8.3.0" ,
  
//-----------------------------------------------

.CORELIB = "#CCORE_ROOT;/Target/#CCORE_TARGET;/CCore.a",

.CCOPT = {
          "-c",
          "-std=c++17",
          "-fconcepts",
          "-fwrapv",
          "-O3",
          
          "-march=ivybridge",
          "-mmmx",
          "-msse",
          "-msse2",
          
          "-Wall",
          "-Wextra",
          
          "-Wno-non-virtual-dtor",
          "-Wno-switch",
          "-Wno-type-limits",
          "-Wno-enum-compare",
          "-Wno-missing-field-initializers",
          "-Wno-delete-non-virtual-dtor",
          "-Wno-misleading-indentation",

          "-I#CCORE_ROOT;/Target/#CCORE_TARGET;",
          "-I#CCORE_ROOT;/HCore",
          "-I#CCORE_ROOT;/Simple",
          "-I#CCORE_ROOT;/Fundamental",
          "-I#CCORE_ROOT;/Applied",
          "-I#CCORE_ROOT;/Desktop/Core",
          "-I#CCORE_ROOT;/Desktop/Draw",
          "-I#CCORE_ROOT;/Desktop/Font",
          "-I#CCORE_ROOT;/Desktop/Lib",
          "-I#CCORE_ROOT;/Desktop/Tools",
          "-I#CCORE_ROOT;/Desktop/App",
          
          "#CCOPT_EXTRA;",
          
          "#SRC;",
          "-o",
          "#DST;"
         },

.LDOPT = {
          "-Wl,-s",
          "#LDOPT_DESKTOP;",
          "#LDOPT_EXTRA;",
          "#CORELIB;",
          "-lws2_32",
          "-lgmp",
          "-lgdi32",
          "-lfreetype"
         },
  
.LDOPT_DESKTOP = {"-Wl,--subsystem,windows"}

//-----------------------------------------------

};

