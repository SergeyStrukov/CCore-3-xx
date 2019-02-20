# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 3.01
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2017 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

LIST = exectest Keywords MakeList MakeString Regen Volume EllipticPi \
       EchoServer PSecEchoServer PTPEchoServer PTPServerProc PTPServer PTPSecureServerProc PTPSecureServer PTPSecureClient \
       DDLShow DDLTypeSet \
       CondLangLR1/Main CondLangLR1/Gen

include ../Target/Makefile.list

PTPServer : PTPServerProc

PTPSecureServer : PTPSecureServerProc
