#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>

void
printFlags (void)
{
  char names[5] = { 'P', '0', 'M', 'T', 'E' };
  char buf[5];
  int start = 82;
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
  mt_gotoXY (0, start);
  write (1, buf, 5);
}

// int main()
// {
//   sc_regInit();
//   sc_regSet(5, 1);
//   printFlags();
//   return 0;
// }