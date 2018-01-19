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

LDOPT_EXTRA = -lgdiplus

include $(CCORE_ROOT)/Makefile.host

TARGET = ./Bitmap.exe

include $(CCORE_ROOT)/Target/Makefile.app

.PHONY : run

run: $(TARGET) 
	$(TARGET)  img/Colors.png img/Colors.bitmap
	$(TARGET)  img/Mandelbrot.png img/Mandelbrot.bitmap






