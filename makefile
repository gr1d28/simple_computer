DIR = mySimpleComputer
LIB_NAME_SC = MSC.a
LIB_NAME_MT = MyT.a
LIB_NAME_MBC = MBT.a
LIB_NAME_MK = MK.a
MK = myReadKey
MT = myTerm
CON = console
MBC = myBigChars
PROG_NAME = con

$(CON)/$(PROG_NAME): $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT) $(MBC)/$(LIB_NAME_MBC) $(MK)/$(LIB_NAME_MK)
	gcc -Wall -I$(DIR)/ -I$(MT)/ -I$(MBC) -I$(MK) $(CON)/*.o $(DIR)/$(LIB_NAME_SC) $(MT)/$(LIB_NAME_MT) $(MBC)/$(LIB_NAME_MBC) $(MK)/$(LIB_NAME_MK) -o $(PROG_NAME) -g
	mv $(PROG_NAME) $(CON)/$(PROG_NAME)
	cd simpleassembler &&  $(MAKE) all
	cd simplebasic && $(MAKE) all

$(MK)/$(LIB_NAME_MK): $(MK)/*.o
	ar rcs $(LIB_NAME_MK) $(MK)/*.o
	mv $(LIB_NAME_MK) $(MK)/$(LIB_NAME_MK)

$(MK)/*.o: $(MK)/*.c
	gcc -c $(MK)/*.c -g
	mv *.o $(MK)/

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
	gcc -I$(DIR)/ -I$(MT)/ -I$(MBC)/ -I$(MK) -c $(CON)/*.c -g
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
	rm $(MK)/*.o

clean_lib:
	rm $(DIR)/$(LIB_NAME_SC)
	rm $(MT)/$(LIB_NAME_MT)
	rm $(MBC)/$(LIB_NAME_MBC)
	rm $(MK)/$(LIB_NAME_MK)