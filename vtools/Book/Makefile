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
	$(TARGET)

TypeSet = $(HOME)/bin/CCore-DDLTypeSet.exe

MakeString = $(HOME)/bin/CCore-MakeString.exe

inc/Book1.TypeDef.gen.h : docs/Book1.ddl
	$(TypeSet) docs/Book1.ddl inc/Book1.TypeDef.gen.h src/Book1.TypeSet.gen.h Font Frame Bitmap

src/./Book1.Pretext.gen.h : docs/Book1.ddl
	$(MakeString) -s docs/Book1.ddl src/Book1.Pretext.gen.h
