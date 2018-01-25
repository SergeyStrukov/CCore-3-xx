# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: Book Convertor 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2018 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

include $(CCORE_ROOT)/Makefile.host

TARGET = ./Convertor.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET) 
#	$(TARGET) Mandelbrot.html ../docs/Mandelbrot.book.ddl
	$(TARGET) CCore.html ../docs/CCore.book.ddl






