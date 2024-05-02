#include "console.h"
#include <stdio.h>
#include <unistd.h>
extern int address;
extern int last_address;
extern int numbers[];
extern int size_of_numbers;

void
IRC (int signo)
{
  int check_reg = 1, value = 0, t = 0;
  static int ch = 1;
  sc_regGet (4, &check_reg);
  if (check_reg == 0)
    {
      if (sc_cacheValidate (address / 10) != 0)
        {
          if (ch)
            {
              sc_timerSet (10);
              ch = 0;
            }
          sc_timerGet (&t);
          printTimer ();
          if (t > 0)
            {
              sc_timerTick ();
              printTimer ();
              return;
            }
          else
            ch = 1;
          sc_cacheLoad (address / 10);
          printCache ();
        }
      CU ();
      if (address - last_address > 1 || last_address - address > 1)
        printCell (last_address, 1, 0);
      last_address = address;
      sc_regGet (4, &check_reg);
      if (!check_reg)
        address++;
      else
        last_address = address;
      if (address >= 0 && last_address >= 0)
        {
          sc_icounterSet (address);
          printCell (last_address, 1, 0);
          printCell (address, 0, 7);
          sc_memoryGet (address, &value);
          printBigCell (numbers, size_of_numbers, value, address);
        }
      printFlags ();
    }
}
