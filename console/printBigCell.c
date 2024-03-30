#include "BC.h"
#include "MT.h"
#include <unistd.h>
#define MASK 0xF
extern char translate (int value);

void
printBigCell (int *big, int size, int value, int number)
{
  int str = 8, col = 65, k = 0, m = 10;
  char buf[4];
  bc_box (str - 1, col - 2, 9, 46, 7, 9, "Editable memory cell", 1, 7);
  if (value >= 0)
    {
      bc_printbigchar (&big[16 * 2], str, col, 9, 7);
    }
  else
    {
      bc_printbigchar (&big[17 * 2], str, col, 9, 7);
      value = (value ^ 0xFFFF) + 1;
    }
  for (int i = 3; i >= 0; i--)
    {
      col += 9;
      k = (value >> i * 4) & MASK;
      bc_printbigchar (&big[k * 2], str, col, 9, 7);
    }
  k = 0;
  for (int i = 2; i >= 0; i--)
    {
      k = (value % m) - (value % (m / 10));
      buf[i] = translate (k);
      m *= 10;
    }
  buf[3] = '\0';
  mt_gotoXY (str + 8, col - 36);
  mt_setfgcolor (4);
  write (1, "number of the cell being edited: ", 33);
  write (1, buf, 4);
  mt_setdefaultcolor ();
}