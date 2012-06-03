
CC=gcc
CFLAGS=
CLIBS=
STRIP=strip

all: brpn

brpn: brpn.c
	$(CC) $(CFLAGS) $(CLIBS) -o brpn brpn.c
	$(STRIP) brpn

clean:
	rm -f *.o a.out *.core brpn
