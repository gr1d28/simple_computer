#include <stdio.h>
extern int SIZE;
extern int RAM[];

void
printCell (int address)
{
  if (address < 0 || address >= 128)
    printf ("Выход за границы\n");
  else
    printf ("%d\n", RAM[address]);
}