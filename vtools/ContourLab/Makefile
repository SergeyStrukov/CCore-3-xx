# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: ContourLab 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2017 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

SRC_PATH_LIST = src

TARGET = ./ContourLab.exe

CCOPT_EXTRA = -I. -Wno-sign-compare

TARGET_DESKTOP = yes

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET)

#----------------------------------------------------------------------------------------

TypeSet = $(HOME)/bin/CCore-DDLTypeSet.exe

MakeString = $(HOME)/bin/CCore-MakeString.exe

src/./Contour.TypeDef.gen.h : src/Contour.ddl
	$(TypeSet) src/Contour.ddl src/Contour.TypeDef.gen.h src/Contour.TypeSet.gen.h

src/./Contour.Pretext.gen.h : src/Contour.ddl
	$(MakeString) -s src/Contour.ddl src/Contour.Pretext.gen.h

