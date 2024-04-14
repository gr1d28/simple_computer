#include "BC.h"
#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK3 0x7
#define MASK4 0xF

char translate (int value);

void
printCounters (void)
{
  char T[4] = { 'T', ':', ' ', '\0' };
  char ic[5] = { 'I', 'C', ':', ' ', '\0' };
  char T_buf[3], ic_buf[5];
  int str = 5, col = 65, count = 0;
  sc_icounterGet (&count);

  if (count >> 14)
    ic_buf[0] = '-';
  else
    ic_buf[0] = '+';

  for (int i = 4; i >= 1; i--)
    {
      if (i % 2 == 0)
        {
          ic_buf[i] = translate (count & MASK4);
          count = count >> 4;
        }
      else
        {
          ic_buf[i] = translate (count & MASK3);
          count = count >> 3;
        }
      // ic_buf[i] = translate (count & MASK);
      // count = count >> 4;
    }
  T_buf[0] = '0';
  T_buf[1] = '0';
  T_buf[2] = '0';
  bc_box (str - 1, col - 2, 1, 21, 7, 9, "Command counter", 1, 9);
  mt_gotoXY (str, col);
  write (1, T, 3);
  write (1, T_buf, 3);
  mt_gotoXY (str, col + 10);
  write (1, ic, 4);
  write (1, ic_buf, 5);
}