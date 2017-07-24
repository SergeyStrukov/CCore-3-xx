# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CondLangLR1-ParserGen 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2017 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

include $(CCORE_ROOT)/Makefile.host

OBJ_PATH = obj

TARGET = $(HOME)/bin/CCore-ParserGen.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET)
	$(TARGET) sample/Formula.ddl FormulaParserData sample/Formula.gen.h sample/Formula.gen.cpp





