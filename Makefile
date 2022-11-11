CFLAGS = -g -pthread

all: clean pingpong

pingpong: pingpong.c
	gcc $(CFLAGS) -o pingpong pingpong.c

clean:
	rm -f pingpong
