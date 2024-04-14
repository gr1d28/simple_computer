#include "BC.h"
#include "MT.h"
#include <stdio.h>
#include <unistd.h>
#define MASK3 0x7
#define MASK4 0xF
extern char translate (int value);

void
printBigCell (int *big, int size, int value, int number)
{
  int str = 8, col = 65, k = 0, m = 10, shift = 11;
  char buf[4];
  bc_box (str - 1, col - 2, 9, 46, 7, 9, "Editable memory cell", 1, 7);
  if (value >> 14)
    {
      bc_printbigchar (&big[17 * 2], str, col, 9, 7);
      value = value & 0x3FFF;
    }
  else
    bc_printbigchar (&big[16 * 2], str, col, 9, 7);

  for (int i = 3; i >= 0; i--)
    {
      if (i % 2 != 0)
        {
          k = (value >> shift) & MASK3;
          shift -= 4;
        }
      else
        {
          k = (value >> shift) & MASK4;
          shift -= 3;
        }
      col += 9;
      bc_printbigchar (&big[k * 2], str, col, 9, 7);
      // k = (value >> i * 4) & MASK;
      // bc_printbigchar (&big[k * 2], str, col, 9, 7);
    }
  k = 0;
  sprintf (buf, "%d", number);
  mt_gotoXY (str + 8, col - 36);
  mt_setfgcolor (4);
  write (1, "number of the cell being edited: ", 33);
  if (number < 10)
    {
      buf[1] = '\0';
      buf[2] = '\0';
      write (1, "00", 2);
    }
  else if (number < 100)
    {
      buf[2] = '\0';
      write (1, "0", 1);
    }
  else
    buf[3] = '\0';
  write (1, buf, 3);
  mt_setdefaultcolor ();
}