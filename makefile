DIR = mySimpleComputer
LIB_NAME = MSC.a
CON = console
PROG_NAME = pr01

$(CON)/$(PROG_NAME): $(CON)/*.o $(DIR)/$(LIB_NAME)
	gcc -Wall -I$(DIR)/ $(CON)/*.o $(DIR)/$(LIB_NAME) -o $(PROG_NAME) -g
	mv $(PROG_NAME) $(CON)/$(PROG_NAME)

$(CON)/*.o: $(CON)/*.c
	gcc -I$(DIR)/ -c $(CON)/*.c -g
	mv *.o $(CON)/

$(DIR)/$(LIB_NAME): $(DIR)/*.o
	ar rcs $(LIB_NAME) $(DIR)/*.o
	mv $(LIB_NAME) $(DIR)/$(LIB_NAME)

$(DIR)/*.o: $(DIR)/*.c
	gcc -c $(DIR)/*.c -g
	mv *.o $(DIR)/

clean:
	rm $(DIR)/*.o
	rm $(CON)/*.o

clean_lib:
	rm $(DIR)/$(LIB_NAME)