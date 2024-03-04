#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK 0xF

char translate (int value);

void
printCounters (void)
{
  char ic[4] = { 'I', 'C', ':', ' ' };
  char ic_buf[5];
  int str = 4, col = 60, count = 0;
  sc_icounterGet (&count);
  if (count >> 15)
    ic_buf[0] = '-';
  else
    ic_buf[0] = '+';
  for (int i = 4; i >= 1; i--)
    {
      ic_buf[i] = translate (count & MASK);
      count = count >> 4;
    }
  mt_gotoXY (str, col);
  write (1, ic, 4);
  write (1, ic_buf, 5);
}