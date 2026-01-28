CC = cc

all: bin bin/stard

bin/stard: 
	$(CC) src/main.c src/TaskBar.c -lX11 -o $@

clean:
	rm -rf bin

bin:
	mkdir -p bin

.PHONY: all clean
