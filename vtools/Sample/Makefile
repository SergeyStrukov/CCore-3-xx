# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: Sample 1.00
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

OBJ_PATH = obj

SRC_PATH_LIST = .

TARGET = ./Sample.exe

CCOPT_EXTRA = -I.

TARGET_DESKTOP = yes

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	$(TARGET)



