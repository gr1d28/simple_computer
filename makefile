DIR = mySimpleComputer
LIB_NAME_SC = MSC.a
LIB_NAME_MT = MyT.a
MT = myTerm
CON = console
PROG_NAME = con

$(CON)/$(PROG_NAME): $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT)
	gcc -Wall -I$(DIR)/ -I$(MT)/ $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT) -o $(PROG_NAME) -g
	mv $(PROG_NAME) $(CON)/$(PROG_NAME)

$(MT)/$(LIB_NAME_MT): $(MT)/*.o
	ar rcs $(LIB_NAME_MT) $(MT)/*.o
	mv $(LIB_NAME_MT) $(MT)/$(LIB_NAME_MT)

$(MT)/*.o: $(MT)/*.c
	gcc -c $(MT)/*.c -g
	mv *.o $(MT)/

$(CON)/*.o: $(CON)/*.c
	gcc -I$(DIR)/ -I$(MT)/ -c $(CON)/*.c -g
	mv *.o $(CON)/

$(DIR)/$(LIB_NAME_SC): $(DIR)/*.o
	ar rcs $(LIB_NAME_SC) $(DIR)/*.o
	mv $(LIB_NAME_SC) $(DIR)/$(LIB_NAME_SC)

$(DIR)/*.o: $(DIR)/*.c
	gcc -c $(DIR)/*.c -g
	mv *.o $(DIR)/

clean:
	rm $(DIR)/*.o
	rm $(CON)/*.o
	rm $(MT)/*.o

clean_lib:
	rm $(DIR)/$(LIB_NAME_SC)
	rm $(MT)/$(LIB_NAME_MT)