BITMAP = $(HOME)/bin/CCore-Bitmap.exe
ZIPMAP = $(HOME)/bin/CCore-Zipmap.exe

LIST = $(wildcard *.png)

LIST1 = $(patsubst %.png,%.bitmap,$(LIST))

LIST2 = $(patsubst %.png,%.zipmap,$(LIST))

.SUFFIXES: .zipmap .png .bitmap

.png.bitmap:
	$(BITMAP) $< $@ 

.bitmap.zipmap:
	$(ZIPMAP) -z $< $@ 

all: $(LIST2)

