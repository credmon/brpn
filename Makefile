
CC=gcc
CFLAGS=-Wall
CLIBS=
STRIP=strip

all: brpn

brpn: brpn_main.c brpn_input.c brpn_nullary.c brpn_unary.c brpn_binary.c brpn_utility.c
	$(CC) $(CFLAGS) $(CLIBS) -o brpn brpn_main.c brpn_input.c brpn_nullary.c brpn_unary.c brpn_binary.c brpn_utility.c
	$(STRIP) brpn

clean:
	rm -f *.o a.out *.core brpn
