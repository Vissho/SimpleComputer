CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/ -I thirdparty/

.PHONY: all

all: bin/mySimpleComputer libs/mySimpleComputer.a

bin/mySimpleComputer: src/main.c libs/mySimpleComputer.a
	$(CC) $(CFLAGS) $(LIBS) -o $@ *.o -L/libs/mySimpleComputer

libs/mySimpleComputer.a:
	$(CC) $(CFLAGS) $(LIBS) -c src/*.c
	ar r libs/mySimpleComputer.a *.o

obj/%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

.PHONY: test
test: bin/mySimpleComputer_test libs/test.a

bin/mySimpleComputer_test: test/main.c test/mySimpleComputer_test.c libs/test.a
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ *.o -L/libs/mySimpleComputer

libs/test.a:
	$(CC) $(CFLAGS) $(LIBS) -c test/*.c
	ar r libs/test.a main.o mySimpleComputer.o mySimpleComputer_test.o

.PHONY: clean
clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.o" -exec rm -f {} \;
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
