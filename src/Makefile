VERSION=0.2
SOURCES=configure  Makefile  nosync-browser  nosync-browser.c  

all: nosync-browser.so

nosync-browser.so: nosync-browser.c
	clang -Wall -fPIC -shared -o nosync-browser.so nosync-browser.c -lc -ldl

install:
	install -m 0755 nosync-browser /usr/bin
	install -m 0644 nosync-browser.so /usr/lib

dist:
	mkdir nosync-browser-$(VERSION)
	cp $(SOURCES) nosync-browser-$(VERSION)
	tar -czf nosync-browser-$(VERSION).tar.gz nosync-browser-$(VERSION)
	rm -r nosync-browser-$(VERSION)
