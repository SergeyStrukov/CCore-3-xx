/* setjmp.h */ 
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore_setjmp_h
#define XCore_setjmp_h

/* Fake -- required to build cross-compiler */ 

typedef struct { int buf[32]; } jmp_buf;

int setjmp(jmp_buf env);

void longjmp(jmp_buf env,int val);

#endif

