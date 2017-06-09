# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 3.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

all:
	make $(OPT) -C MakeList
	make $(OPT) -C Keywords
	make $(OPT) -C CondLangLR1/Main
	make $(OPT) -C CondLangLR1/Gen
	make $(OPT) -C DDLShow
	make $(OPT) -C DDLTypeSet
	make $(OPT) -C EllipticPi
	make $(OPT) -C EchoServer
	make $(OPT) -C PTPEchoServer
	make $(OPT) -C PTPServerProc
	make $(OPT) -C PTPServer
	make $(OPT) -C PTPSecureServerProc
	make $(OPT) -C PTPSecureServer
	make $(OPT) -C PTPSecureClient
	make $(OPT) -C exectest
	make $(OPT) -C PSecEchoServer
	make $(OPT) -C Regen

clean:
	make -C MakeList               clean
	make -C Keywords               clean
	make -C CondLangLR1/Main       clean
	make -C CondLangLR1/Gen        clean
	make -C DDLShow                clean
	make -C DDLTypeSet             clean
	make -C EllipticPi             clean
	make -C EchoServer             clean
	make -C PTPEchoServer          clean
	make -C PTPServerProc          clean
	make -C PTPServer              clean
	make -C PTPSecureServerProc    clean
	make -C PTPSecureServer        clean
	make -C PTPSecureClient        clean
	make -C exectest               clean
	make -C PSecEchoServer         clean
	make -C Regen                  clean

list:
	make -C MakeList               list
	make -C Keywords               list
	make -C CondLangLR1/Main       list
	make -C CondLangLR1/Gen        list
	make -C DDLShow                list
	make -C DDLTypeSet             list
	make -C EllipticPi             list
	make -C EchoServer             list
	make -C PTPEchoServer          list
	make -C PTPServerProc          list
	make -C PTPServer              list
	make -C PTPSecureServerProc    list
	make -C PTPSecureServer        list
	make -C PTPSecureClient        list
	make -C exectest               list
	make -C PSecEchoServer         list
	make -C Regen                  list



