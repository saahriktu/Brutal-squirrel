ifeq ($(prefix),)
	prefix=/usr/local
endif
ifeq ($(shell which $(CC)),)
	CC=gcc
endif
all:
	$(CC) $(CFLAGS) -o brtlsqrrl brtlsqrrl.c
	strip -S brtlsqrrl
install:
	if [ ! -d "$(DESTDIR)$(prefix)/bin" ]; then mkdir -p $(DESTDIR)$(prefix)/bin; fi
	install -m755 brtlsqrrl $(DESTDIR)$(prefix)/bin
clean:
	rm brtlsqrrl
