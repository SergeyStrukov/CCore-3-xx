# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: PTPSecureServer 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

CCOPT_EXTRA = -I../PTPSecureServerProc 

LDOPT_EXTRA = ../PTPSecureServerProc/PTPSecureServerProc.a

DDLTYPESET = $(HOME)/bin/CCore-DDLTypeSet.exe

include $(CCORE_ROOT)/Makefile.host

OBJ_PATH = obj

TARGET = $(HOME)/bin/CCore-PTPSecureServer.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	$(TARGET) Config.ddl

ddl:
	$(DDLTYPESET) Config.ddl Config.type.h Config.typeset.h
