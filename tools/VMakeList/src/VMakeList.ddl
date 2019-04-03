/* VMakeList.ddl */
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

int TargetConsole = 1 ;
int TargetDesktop = 2 ;
int TargetLib     = 3 ;
int TargetCCore   = 4 ;

struct Param
 {
  text CCORE_ROOT = "" ;

  text CCORE_TARGET = "" ;

  text OBJ_PATH = ".obj" ;

  text[] SRC_PATH_LIST = {"."} ;

  text[] CCOPT_EXTRA = {} ;

  text[] ASOPT_EXTRA = {} ;
  
  text[] LDOPT_EXTRA = {} ;
  
  text TARGET = "./main.exe" ;
  
  int target;
  
  Tools * tools = null ;
 };
 
struct Tools
 {
  text CC = "g++" ;
  text AS = "as"  ;
  text LD = "g++" ;
  text AR = "ar"  ;
  
  text VMDEP = "#HOME;/bin/CCore-VMakeDep.exe" ;
  
  text RM = "rm -f" ;
  text MKDIR = "mkdir -p" ;
  text MKEMPTY = 'echo \"empty file\"' ;
  text CAT = "cat" ;
  
  text[] CCINC;
  text[] CCOPT;
  text[] DEPOPT;
  text[] ASOPT;
  text[] LDOPT;
  
  text[] LDOPT_DESKTOP;
  
  text CORELIB;
 };




