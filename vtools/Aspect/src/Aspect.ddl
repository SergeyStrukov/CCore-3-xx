/* Aspect.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Status = uint8 ;

Status New    = 0 ; 
Status Ignore = 1 ;
Status Red    = 2 ;
Status Yellow = 3 ;
Status Green  = 4 ;

struct File
 {
  text name;
  Status status;  
 };

struct Dir
 {
  text name;
  Status status; 
  
  Dir * [] dirs;
  File[] files;
 };

struct Aspect
 {
  text path;
  
  Dir root;  
 };
 
