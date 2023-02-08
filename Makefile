CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/

.PHONY: all

all: bin/mySimpleComputer libs/mySimpleComputer.so

bin/mySimpleComputer: src/main.c libs/mySimpleComputer.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

libs/mySimpleComputer.so: src/mySimpleComputer.c
	$(CC) $(CFLAGS) -shared $(LIBS) -o $@ $^

.SILENT: clean

clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.tmp" -exec rm -f {} \;
	rm -rf bin/mySimpleComputer

rebuild: clean all

run:
	bin/mySimpleComputer

memory_check:
	valgrind --leak-check=full bin/mySimpleComputer
