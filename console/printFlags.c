#include "MT.h"
#include "SC.h"
#include "BC.h"
#include <stdio.h>
#include <unistd.h>

void
printFlags (void)
{
  char names[5] = { 'P', '0', 'M', 'T', 'E' };
  char buf[5];
  int start = 94;
  int value = 0;
  for (int i = 0; i < 5; i++)
    {
      sc_regGet (i + 1, &value);
      if (value)
        buf[i] = names[i];
      else
        buf[i] = '_';
      value = 0;
    }
  bc_box(1, start - 8, 1, 21, 7, 9, "Аlag register", 1, 9);
  mt_gotoXY (2, start);
  write (1, buf, 5);
}