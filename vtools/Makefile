# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 3.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

all:
	make $(OPT) -C UserPreference
	make $(OPT) -C DDLDisplay
	make $(OPT) -C SubLab
	make $(OPT) -C ContourLab
	make $(OPT) -C Aspect
	make $(OPT) -C Sample

clean:
	make -C UserPreference         clean
	make -C DDLDisplay             clean
	make -C SubLab                 clean
	make -C ContourLab             clean
	make -C Aspect                 clean
	make -C Sample                 clean

list:
	make -C UserPreference         list
	make -C DDLDisplay             list
	make -C SubLab                 list
	make -C ContourLab             list
	make -C Aspect                 list
	make -C Sample                 list


