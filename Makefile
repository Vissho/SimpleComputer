CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/ -I thirdparty/

.PHONY: all

all: mySimpleComputer test

mySimpleComputer: src/main.c src/interface.c mySimpleComputer.a myTerm.a
	$(CC) $(CFLAGS) $(LIBS) -o $@ -L. $^

mySimpleComputer.a: src/mySimpleComputer.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r mySimpleComputer.a mySimpleComputer.o

myTerm.a: src/myTerm.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myTerm.a myTerm.o

.PHONY: test
test: mySimpleComputer_test myTerm_test

mySimpleComputer_test: test/main.c test/mySimpleComputer_test.c mySimpleComputer.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

myTerm_test: test/main.c test/myTerm_test.c myTerm.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

.PHONY: clean
clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -name "*.d" -exec rm -f {} \;
	rm -rf mySimpleComputer
	rm -rf mySimpleComputer_test
	rm -rf myTerm_test

rebuild: clean all

run:
	./mySimpleComputer

test_run1:
	./mySimpleComputer_test

test_run2:
	./myTerm_test

memory_check:
	valgrind --leak-check=full ./mySimpleComputer
	valgrind --leak-check=full ./mySimpleComputer_test
	valgrind --leak-check=full ./myTerm_test
