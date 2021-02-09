VERSION=0.2
SOURCES=configure  Makefile  nosync  nosync.c  

all: nosync.so

nosync.so: nosync.c
	gcc -Wall -fPIC -shared -o nosync.so nosync.c -lc -ldl

install:
	install -m 0755 nosync /usr/bin
	install -m 0644 nosync.so /usr/lib

dist:
	mkdir nosync-$(VERSION)
	cp $(SOURCES) nosync-$(VERSION)
	tar -czf nosync-$(VERSION).tar.gz nosync-$(VERSION)
	rm -r nosync-$(VERSION)
