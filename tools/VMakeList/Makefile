# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: VMakeList 1.00
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

CCOPT_EXTRA = -I.

TARGET = $(HOME)/bin/CCore-VMakeList.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) default.vml.ddl proj.vm.ddl prep.vm.ddl

#----------------------------------------------------------------------------------------

TypeSet = $(HOME)/bin/CCore-DDLTypeSet.exe

MakeString = $(HOME)/bin/CCore-MakeString.exe

inc/VMakeList.TypeDef.gen.h : src/VMakeList.ddl
	$(TypeSet) src/VMakeList.ddl inc/VMakeList.TypeDef.gen.h src/VMakeList.TypeSet.gen.h 

src/./VMakeList.Pretext.gen.h : src/VMakeList.ddl
	$(MakeString) -s src/VMakeList.ddl src/VMakeList.Pretext.gen.h





