CC = cc

all: bin bin/stard

bin/stard: src/main.c
	$(CC) $< -lX11 -o $@

clean:
	rm -rf bin

bin:
	mkdir -p bin

.PHONY: all clean
