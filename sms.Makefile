sms: main.o menu.o operation.o student.o
	gcc -o sms main.o menu.o operation.o student.o

main.o: sourceFile/main.c include/menu.h
	gcc -c sourceFile/main.c

menu.o: sourceFile/menu.c include/menu.h include/operation.h
	gcc -c sourceFile/menu.c

operation.o: sourceFile/operation.c include/operation.h include/student.h
	gcc -c sourceFile/operation.c

student.o: sourceFile/student.c include/student.h
	gcc -c sourceFile/student.c