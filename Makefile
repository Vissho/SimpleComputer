CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/ -I thirdparty/

.PHONY: all

all: bin/mySimpleComputer libs/mySimpleComputer.so

bin/mySimpleComputer: src/main.c libs/mySimpleComputer.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

libs/mySimpleComputer.so: src/mySimpleComputer.c
	$(CC) $(CFLAGS) -shared $(LIBS) -o $@ $^

.PHONY: test
test: bin/mySimpleComputer_test

bin/mySimpleComputer_test: test/main.c test/mySimpleComputer_test.c libs/mySimpleComputer.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

.PHONY: clean
clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.tmp" -exec rm -f {} \;
	find . -type f -name "*.d" -exec rm -f {} \;
	rm -rf bin/mySimpleComputer
	rm -rf bin/mySimpleComputer_test

rebuild: clean all

run:
	bin/mySimpleComputer

test_run:
	bin/mySimpleComputer_test

memory_check:
	valgrind --leak-check=full bin/mySimpleComputer
	valgrind --leak-check=full bin/mySimpleComputer_test
