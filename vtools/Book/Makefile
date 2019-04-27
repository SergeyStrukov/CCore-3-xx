# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: Book 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2018 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

SRC_PATH_LIST = src

TARGET = $(HOME)/bin/CCore-Book.exe

CCOPT_EXTRA = -I.

TARGET_DESKTOP = yes

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) docs/test.book.ddl

#----------------------------------------------------------------------------------------

TypeSet = $(HOME)/bin/CCore-DDLTypeSet.exe

MakeString = $(HOME)/bin/CCore-MakeString.exe

src/./AppState.TypeDef.gen.h : src/AppState.ddl
	$(TypeSet) src/AppState.ddl src/AppState.TypeDef.gen.h src/AppState.TypeSet.gen.h

src/./AppState.Pretext.gen.h : src/AppState.ddl
	$(MakeString) -s src/AppState.ddl src/AppState.Pretext.gen.h
