CFLAGS = -Wall -pedantic -g

self-linker: self-linker.c
	gcc $(CFLAGS) -o self-linker self-linker.c -ldl

.PHONY: clean
clean:
	rm -f self-linker
