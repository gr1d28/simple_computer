DIR = mySimpleComputer
LIB_NAME_SC = MSC.a
LIB_NAME_MT = MyT.a
LIB_NAME_MBC = MBT.a
MT = myTerm
CON = console
MBC = myBigChars
PROG_NAME = con

$(CON)/$(PROG_NAME): $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT) $(MBC)/$(LIB_NAME_MBC)
	gcc -Wall -I$(DIR)/ -I$(MT)/ -I$(MBC) $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT) $(MBC)/$(LIB_NAME_MBC) -o $(PROG_NAME) -g
	mv $(PROG_NAME) $(CON)/$(PROG_NAME)

# $(CON)/font: $(CON)/font.o $(MBC)/$(LIB_NAME_MBC)
# 	gcc -Wall -I$(MBC)/ $(CON)/font.o $(MBC)/$(LIB_NAME_MBC) -o font
# 	mv font $(CON)/font

$(MBC)/$(LIB_NAME_MBC): $(MBC)/*.o
	ar rcs $(LIB_NAME_MBC) $(MBC)/*.o
	mv $(LIB_NAME_MBC) $(MBC)/$(LIB_NAME_MBC)

$(MBC)/*.o: $(MBC)/*.c
	gcc -c -I$(MT)/ $(MBC)/*.c -g
	mv *.o $(MBC)/

$(MT)/$(LIB_NAME_MT): $(MT)/*.o
	ar rcs $(LIB_NAME_MT) $(MT)/*.o
	mv $(LIB_NAME_MT) $(MT)/$(LIB_NAME_MT)

$(MT)/*.o: $(MT)/*.c
	gcc -c $(MT)/*.c -g
	mv *.o $(MT)/

$(CON)/*.o: $(CON)/*.c
	gcc -I$(DIR)/ -I$(MT)/ -I$(MBC)/ -c $(CON)/*.c -g
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
	rm $(MBC)/*.o

clean_lib:
	rm $(DIR)/$(LIB_NAME_SC)
	rm $(MT)/$(LIB_NAME_MT)
	rm $(MBC)/$(LIB_NAME_MBC)