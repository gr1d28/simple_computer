#include "MT.h"
#include "SC.h"
#include "BC.h"

void printAccumulator (void);

void printCell (int address, color fg, color bg);

void printCommand (void);

void printCounters (void);

void printDecodedCommand (int value);

void printFlags (void);

void printTerm (int address, int input);

int font();

void printBigCell (int *big, int size, int value, int number);