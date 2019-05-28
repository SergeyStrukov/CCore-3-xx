
DUMP = /opt/BBB-9.1.0/arm-eabielf/bin/objdump.exe -xds

CC = /opt/BBB-9.1.0/bin/arm-g++.exe

FILE = crtbegin.2

all:
	$(DUMP)	$(FILE).o > $(FILE).txt 

mlib:
	$(CC) --print-multi-directory
