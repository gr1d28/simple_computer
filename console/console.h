#include "BC.h"
#include "MR.h"
#include "MT.h"
#include "SC.h"

void printAccumulator (void);

void printCell (int address, color fg, color bg);

void printCommand (void);

void printCounters (void);

void printDecodedCommand (int value);

void printFlags (void);

void printTerm (int address, int input);

int font ();

void printBigCell (int *big, int size, int value, int number);

void printKeys (void);

void printTimer (void);

void CU (void);

void IRC (int signo);

int ALU (int command, int operand);

void printCache (void);