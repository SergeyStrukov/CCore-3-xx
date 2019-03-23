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

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

SRC_PATH_LIST = src

TARGET = sample/vmake.exe 

# $(HOME)/bin/vmake.exe

CCOPT_EXTRA = -I.

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) main sample/default.vm.ddl

#----------------------------------------------------------------------------------------

TypeSet = $(HOME)/bin/CCore-DDLTypeSet.exe

MakeString = $(HOME)/bin/CCore-MakeString.exe

inc/vmake.TypeDef.gen.h : src/vmake.ddl
	$(TypeSet) src/vmake.ddl inc/vmake.TypeDef.gen.h src/vmake.TypeSet.gen.h Target Rule MenuItem

src/./vmake.Pretext.gen.h : src/vmake.ddl
	$(MakeString) -s src/vmake.ddl src/vmake.Pretext.gen.h
