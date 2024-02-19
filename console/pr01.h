#include <stdio.h>
#include <stdlib.h>
extern unsigned int Accumulator;
extern int SIZE;
extern int RAM[];
extern unsigned int Icounter;
extern char REG;

void printAccumulator (void);

void printCell (int address);

void printCounters (void);

void printDecodedCommand (int value);

void printFlags (void);