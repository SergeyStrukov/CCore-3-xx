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
  text desc;
  text file = null ;
 };
 
struct Env
 {
  text name;
  text value;
 }; 
 
struct Exe
 {
  text echo; 
  text exe;
  text[] args;
  text wdir;
  Env[] env;
 };
 
struct Cmd
 {
  text echo; 
  text cmdline;
  text wdir;
  Env[] env;
 };
 
struct VMake
 {
  text echo; 
  text file;
  text target = 'main' ;
  text wdir;
 };

struct Echo
 {
  text str;
  text outfile;
 };
 
struct Cat
 {
  text[] files;
  text outfile;
 };
 
struct Rm
 {
  text[] files;
 };
 
struct Mkdir
 {
  text path;
 };   
 
struct IntCmd
 {
  text echo;
  {Echo,Cat,Rm,Mkdir} *cmd; 
  text wdir;
 }; 
 
struct Rule
 {
  Target * [] src; 
  Target * [] dst;
  {Exe,Cmd,VMake,IntCmd} * [] cmd;
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

    