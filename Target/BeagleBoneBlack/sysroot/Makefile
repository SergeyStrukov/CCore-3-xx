# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 3.00
#
#  Tag: Target/BeagleBoneBlack
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2016 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

XCORE_ROOT = ../../..

XCORE_TARGET = BeagleBoneBlack

# CC tool

CC = /opt/BBB-9.1.0/bin/arm-gcc.exe

NOWARN = -Wno-non-virtual-dtor -Wno-switch

CCINC = -I$(XCORE_ROOT)/Target/$(XCORE_TARGET)

CCCPU = -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3 -mno-unaligned-access

CCOPT = -c -std=c++17 -fconcepts -fwrapv -O3 $(CCCPU) -Wall -Wextra $(NOWARN) $(CCINC) $(CCOPT_EXTRA) -D__STDBUILD

CCOPT_C = -c -O3 $(CCCPU) -Wall -Wextra $(CCINC) -D__STDBUILD

# AS tool

AS = /opt/BBB-9.1.0/bin/arm-as.exe

ASOPT = -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3

# AR tool

AR = /opt/BBB-9.1.0/bin/arm-ar.exe

# RM tool

RM = rm -f

# obj list

OBJ_LIST = obj/ctype.o       \
           obj/string_c.o    \
           obj/errno.o       \
           obj/locale.o      \
           obj/stdlib.o      \
           obj/string.o      \
           obj/time.o        \
           obj/consts.o      \
           obj/string_s.o    \

# deps

all: lib/libc.a lib/libm.a lib/crt0.o

clean:
	$(RM) $(OBJ_LIST) lib/libc.a lib/libm.a lib/crt0.o

install: all
	cp -r -v ./lib /opt/BBB-9.1.0/sysroot

lib/libc.a : $(OBJ_LIST)
	$(RM) $@
	$(AR) -r $@ $(OBJ_LIST)

lib/libm.a :
	$(RM) $@
	$(AR) -r $@ 

obj/%.o : src/%.cpp
	$(CC) $(CCOPT) $< -o $@

obj/%.o : src/%.c
	$(CC) $(CCOPT_C) $< -o $@

obj/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@

lib/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@





