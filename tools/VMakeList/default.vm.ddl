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

Target proj = { "proj" , "proj.vm.ddl" } ;

Target prep = { "prep" , "prep.vm.ddl" } ;

Rule r1 = { {&proj,&obj,&mkdep} , {&main} , {&r1vmake} } ; 

VMake r1vmake = { "-> PROJ" , "proj.vm.ddl" } ;

//----------------------------------------------------------------------------------------

Target desc = { "desc" , "default.vml.ddl" } ;

Rule r2 = { {&desc} , {&proj,&prep} , {&r2exe} } ;

Exe r2exe = { "LIST" , "CCore-VMakeList.exe" , { "default.vml.ddl" , "proj.vm.ddl" , "prep.vm.ddl" } } ;

//----------------------------------------------------------------------------------------

Target list = { "list" } ;

Rule r3 = { {} , {&list} , {&r2exe} } ;

//----------------------------------------------------------------------------------------

Target obj = { "obj" } ;

Rule r4 = { {&prep} , {&obj} , {&r4vmake} } ;

VMake r4vmake = { "-> OBJ" , "prep.vm.ddl" , "obj" } ;

//----------------------------------------------------------------------------------------

Target clean = { "clean" } ;

Rule r5 = { {&prep} , {&clean} , {&r5vmake} } ; 

VMake r5vmake = { "-> CLEAN" , "prep.vm.ddl" , "clean" } ;

//----------------------------------------------------------------------------------------

Target dep = { "dep" } ;

Rule r6 = { {&prep} , {&dep} , {&r6vmake} } ; 

VMake r6vmake = { "-> CLEAN DEP" , "prep.vm.ddl" , "clean_dep" } ;

//----------------------------------------------------------------------------------------

Target mkdep = { "mkdep" } ;

Rule r7 = { {&prep} , {&mkdep} , {&r7vmake} } ; 

VMake r7vmake = { "-> MAKE DEP" , "prep.vm.ddl" , "make_dep" } ;

//----------------------------------------------------------------------------------------




