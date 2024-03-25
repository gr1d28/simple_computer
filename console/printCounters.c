#include "MT.h"
#include "SC.h"
#include "BC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK 0xF

char translate (int value);

void
printCounters (void)
{
  char ic[3] = { 'T', ':', ' ' };
  char ic_buf[2];
  int str = 5, col = 65, count = 0;
  sc_icounterGet (&count);

  for (int i = 1; i >= 0; i--)
    {
      ic_buf[i] = translate (count & MASK);
      count = count >> 4;
    }
  bc_box(str - 1, col - 2, 1, 21, 7, 9, "Command counter", 1, 9);
  mt_gotoXY (str, col);
  write (1, ic, 3);
  write (1, ic_buf, 2);
}