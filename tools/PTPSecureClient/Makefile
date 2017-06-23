# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: PTPSecureClient 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

DDLTYPESET = $(HOME)/bin/CCore-DDLTypeSet.exe

include $(CCORE_ROOT)/Makefile.host

TARGET = $(HOME)/bin/CCore-PTPSecureClient.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	$(TARGET) Config.ddl

ddl:
	$(DDLTYPESET) Config.ddl Config.type.h Config.typeset.h
