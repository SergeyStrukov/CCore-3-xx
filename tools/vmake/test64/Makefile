# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: vmake 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2019 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

CCORE_TARGET = WIN64utf8

TARGET = ./test.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	export ABRA=CODABRA ; $(TARGET) name "long name"
