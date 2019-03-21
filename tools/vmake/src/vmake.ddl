/* vmake.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

struct Target
 {
  text file = null ;
 };
 
struct Env
 {
  text name;
  text value;
 }; 
 
struct Exe
 {
  text exe;
  text cmdline;
  text wdir;
  Env[] env;
  text echo; 
 };
 
struct Cmd
 {
  text cmdline;
  text wdir;
  Env[] env;
  text echo; 
 };
 
struct VMake
 {
  text file;
  text target = 'main' ;
  text wdir;
  text echo; 
 };
 
struct Rule
 {
  Target * [] src; 
  Target * [] dst;
  {Exe,Cmd,VMake} * [] cmd;
 };
 
struct Dep
 {
  Target * [] src; 
  Target * [] dst;
 };

struct MenuItem
 {
  Target *dst;
  text desc;
  
  MenuItem * [] sub = {} ;  
 };
 
struct Menu
 {
  MenuItem[] list;
 };

// menu OR auto

    