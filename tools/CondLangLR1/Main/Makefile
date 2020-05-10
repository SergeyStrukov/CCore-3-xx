# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CondLangLR1 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

include $(CCORE_ROOT)/Makefile.host

TARGET = $(HOME)/bin/CCore-CondLangLR1.exe

CCOPT_EXTRA = -I. -Wno-non-template-friend

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) ../AMP/AMP
	$(TARGET) ../DDL/DDL.lang





