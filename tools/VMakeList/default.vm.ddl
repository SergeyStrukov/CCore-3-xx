/* default.vm.ddl */
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

Target main = { "main" } ;

Target list = { "list" , "list.vm.ddl" } ;

Target desc = { "desc" , "default.vml.ddl" } ;

Rule r1 = { {&desc} , {&list} , {&r1exe} } ;

Exe r1exe = { "LIST" , "CCore-VMakeList.exe" , { "default.vml.ddl" , "list.vm.ddl" } } ;

Rule r2 = { {&list} , {&main} , {&r2vmake} } ; 

VMake r2vmake = { "PROJ" , "list.vm.ddl" } ;
