CFLAGS = -g -pthread

all: clean ping_pong

ping_pong: ping_pong.c
	gcc $(CFLAGS) -o ping_pong ping_pong.c

clean:
	rm -f ping_pong
