# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: SubLab 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2016 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

SRC_PATH_LIST = .

TARGET = ./SubLab.exe

CCOPT_EXTRA = -I.

TARGET_DESKTOP = yes

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET)



