/* signal.h */
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore_signal_h
#define XCore_signal_h

/* Fake -- required to build cross-compiler */

typedef int sig_atomic_t;

void (*signal(int sig, void (*func)(int)))(int);

int raise(int sig);

#endif

