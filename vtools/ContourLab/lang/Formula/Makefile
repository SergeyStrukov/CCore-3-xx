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

LANG = $(HOME)/bin/CCore-CondLangLR1.exe

GEN = $(HOME)/bin/CCore-ParserGen.exe

run:
	$(LANG) Formula.lang
	$(GEN) Formula.ddl FormulaParserData Formula.gen.h_ Formula.gen.cpp_
