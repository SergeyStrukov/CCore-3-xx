# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: BeagleBoot 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2016 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../../..

include $(CCORE_ROOT)/Makefile.host

TARGET = $(HOME)/bin/CCore-BeagleBoot.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) r 192.168.99.10 ../../test/main.exe




