CFLAGS=
LDFLAGS=

all: example.o;
	clang example.c hotrod.c -o example -O0 $(CFLAGS) $(LDFLAGS)

run:
	./example

clean:
	rm -f *.o hot_*.c hot_*.so example
