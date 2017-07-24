# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: PTPServer 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

CCOPT_EXTRA = -I../PTPServerProc 

LDOPT_EXTRA = ../PTPServerProc/PTPServerProc.a

include $(CCORE_ROOT)/Makefile.host

TARGET = $(HOME)/bin/CCore-PTPServer.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	cd root && $(TARGET)





