int sc_accumulatorGet (int *value);

int sc_accumulatorInit (void);

int sc_accumulatorSet (int value);

int sc_commandDecode (int value, int *sign, int *command, int *operand);

int sc_commandEncode (int sign, int command, int operand, int *value);

int sc_commandValidate (int command);

int sc_icounterGet (int *value);

int sc_icounterInit (void);

int sc_icounterSet (int value);

int sc_memoryGet (int address, int *value);

int sc_memoryInit (void);

int sc_memoryLoad (char *filename);

int sc_memorySave (char *filename);

int sc_memorySet (int address, int value);

int sc_regGet (int registers, int *value);

int sc_regInit (void);

int sc_regSet (int registers, int value);

int sc_timerInit (void);

int sc_timerGet (int *value);

int sc_timerSet (int value);

int sc_timerTick (void);

int sc_cacheInit (void);

int sc_cacheGet (int address, int *value, int print);

int sc_cacheSet (int address, int value);

int sc_cacheLoad (int str_num);

int sc_cacheStore (int str_num);

int sc_cacheValidate (int str_num);