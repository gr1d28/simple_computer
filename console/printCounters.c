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
  char ic[5] = { 'I', 'C', ':', ' ', '\0' };
  char ic_buf[5];
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
    }
  bc_box (str - 1, col - 2, 1, 21, 7, 9, "Command counter", 1, 9);
  mt_gotoXY (str, col + 10);
  write (1, ic, 4);
  write (1, ic_buf, 5);
}