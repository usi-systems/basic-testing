.PHONY: all run debug clean
all:
	gcc -g -c alloc.c -o alloc.o
	gcc -g -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=realloc alloc.o override.c -o overidden

run: all
	./overidden

debug: all
	gdb ./overidden -ex "break main" -ex "run"

clean:
	rm ./overidden alloc.o
