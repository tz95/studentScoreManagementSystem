# 变量定义
source := $(find sourceFile -name "*.c")
include := $(find include -name "*.h")
objs := $(source:.c=.o)
objs := $(objs:sourceFile/%=objs/%)

CC = gcc

ALL: sms

sms: main.o menu.o operation.o student.o
	$(CC) -o sms main.o menu.o operation.o student.o

main.o: sourceFile/main.c include/menu.h
	$(CC) -c sourceFile/main.c

menu.o: sourceFile/menu.c include/menu.h include/operation.h
	$(CC) -c sourceFile/menu.c

operation.o: sourceFile/operation.c include/operation.h include/student.h
	$(CC) -c sourceFile/operation.c

student.o: sourceFile/student.c include/student.h
	$(CC) -c sourceFile/student.c

.PHONY: clean ALL
clean:
	rm -f main.o menu.o operation.o student.o