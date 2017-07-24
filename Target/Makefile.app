# Makefile.app
#----------------------------------------------------------------------------------------
#
#  Project: CCore 3.01
#
#  Tag: General
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2017 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

SRC_PATH_LIST ?= .

OBJ_PATH ?= .obj

TARGET ?= main.exe

RULES_FILE = $(CCORE_ROOT)/Target/Makefile.app.rules

include $(CCORE_ROOT)/Target/$(CCORE_TARGET)/Makefile.tools

.PHONY : all list

all: $(TARGET)

Makefile.files:
	$(HOME)/bin/CCore-MakeList.exe $(OBJ_PATH) -s $(SRC_PATH_LIST)

ifneq ($(MAKECMDGOALS),list)

include Makefile.files

endif

list:
	$(HOME)/bin/CCore-MakeList.exe $(OBJ_PATH) -s $(SRC_PATH_LIST)


