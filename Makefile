CFLAGS=
LDFLAGS=

all: main.o;
	clang example.c hotrod.c -o example -g -O0 $(CFLAGS) $(LDFLAGS)

run:
	./example

clean: rm -f *.o hot_*.c example
