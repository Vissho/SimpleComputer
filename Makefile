CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/ -I thirdparty/

.PHONY: all

all: mySimpleComputer.out test sat.out sbt.out

mySimpleComputer.out: src/main.c src/interface.c mySimpleComputer.a myTerm.a myBigChars.a myReadkey.a mySignal.a myCU.a myALU.a
	$(CC) $(CFLAGS) $(LIBS) -o $@ -L. $^

mySimpleComputer.a: src/mySimpleComputer.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r mySimpleComputer.a mySimpleComputer.o

myTerm.a: src/myTerm.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myTerm.a myTerm.o

myBigChars.a: src/myBigChars.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myBigChars.a myBigChars.o

myReadkey.a: src/myReadkey.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myReadkey.a myReadkey.o

mySignal.a: src/mySignal.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r mySignal.a mySignal.o

myALU.a: src/myALU.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myALU.a myALU.o

myCU.a: src/myCU.c
	$(CC) $(CFLAGS) $(LIBS) -c $^
	ar r myCU.a myCU.o

sat.out: src/sat.c mySimpleComputer.a
	$(CC) $(CFLAGS) $(LIBS) -o $@ -L. $^ -lm

sbt.out: src/sbt.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ -L. $^

.PHONY: test
test: mySimpleComputer_test.out myTerm_test.out myBigChars_test.out myReadkey_test.out mySignal_test.out

mySimpleComputer_test.out: test/main.c test/mySimpleComputer_test.c mySimpleComputer.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

myTerm_test.out: test/main.c test/myTerm_test.c myTerm.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

myBigChars_test.out: test/main.c test/myBigChars_test.c myBigChars.a  mySimpleComputer.a myTerm.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

myReadkey_test.out: test/main.c test/myReadkey_test.c myReadkey.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

mySignal_test.out: test/main.c test/mySignal_test.c src/interface.c mySignal.a myBigChars.a  mySimpleComputer.a myTerm.a myReadkey.a myCU.a myALU.a
	$(CC) $(CFLAGS) $(LIBS)  -o $@ -L. $^

.PHONY: clean
clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -name "*.d" -exec rm -f {} \;
	find . -type f -name "*.sa" -exec rm -f {} \;

rebuild: clean all

run:
	./mySimpleComputer.out

test_run1:
	./mySimpleComputer_test.out

test_run2:
	./myTerm_test.out

test_run3:
	./myBigChars_test.out

test_run4:
	./myReadkey_test.out

test_run5:
	./mySignal_test.out

test_run:
	./mySimpleComputer_test.out
	./myTerm_test.out
	./myBigChars_test.out
	./mySignal_test.out

memory_check:
	valgrind --leak-check=full ./mySimpleComputer.out
	valgrind --leak-check=full ./mySimpleComputer_test.out
	valgrind --leak-check=full ./myTerm_test.out
	valgrind --leak-check=full ./myBigChars_test.out
	valgrind --leak-check=full ./myReadkey_test.out
	valgrind --leak-check=full ./mySignal_test.out
