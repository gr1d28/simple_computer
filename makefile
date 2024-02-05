DIR = console

make: $(DIR)/test.o
	gcc -Wall $(DIR)/test.o -o $(DIR)/test
obj: $(DIR)/test.c
	gcc -c $(DIR)/test.c
	mv test.o $(DIR)/test.o