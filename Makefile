# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 2.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

include Makefile.host

OPT = -j 8

all:
	make $(OPT) -C Target/$(CCORE_TARGET)
	make $(OPT) -C Target/$(CCORE_TARGET)/test
	make $(OPT) -C tools

clean:
	make -C Target/$(CCORE_TARGET)       clean
	make -C Target/$(CCORE_TARGET)/test  clean
	make -C tools                        clean

list:
	make -C Target/WIN32                 list
	make -C Target/WIN32/test            list
	make -C Target/WIN64                 list
	make -C Target/WIN64/test            list
	make -C Target/LIN64                 list
	make -C Target/LIN64/test            list
	make -C Target/BeagleBoneBlack       list
	make -C Target/BeagleBoneBlack/test  list
	make -C tools                        list
	make -C vtools                       list


