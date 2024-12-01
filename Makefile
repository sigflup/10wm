CFLAGS += -w -DSHAPE -DCOLOR -Wall -pedantic -ansi -D_XOPEN_SOURCE -I/usr/X11R6/include -std=c99
LDLIBS = -L/usr/X11R6/lib -lXext -lX11
PREFIX ?= /usr
BIN = $(DESTDIR)$(PREFIX)/bin

MANDIR = $(DESTDIR)$(PREFIX)/share/man/man1
MANSUFFIX = 1

OBJS = 10wm.o link.o event.o manage.o menu.o client.o grab.o cursor.o error.o
 

all: 10wm

10wm: ${OBJS} 
	cc -o 10wm ${OBJS} ${LDLIBS}

install: 10wm
	mkdir -p $(BIN)
	cp 9wm $(BIN)/9wm

install.man:
	mkdir -p $(MANDIR)
	cp 9wm.man $(MANDIR)/9wm.$(MANSUFFIX)

$(OBJS): $(HFILES)

clean:
	rm -f 10wm *.o
