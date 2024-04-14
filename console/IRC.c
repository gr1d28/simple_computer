#include "console.h"
#include <stdio.h>
#include <unistd.h>
extern int address;
extern int last_address;

void
IRC (int signo)
{
  int check_reg = 1;
  sc_regGet (4, &check_reg);
  if (check_reg == 0)
    {
      CU ();
      // if(address - last_address == 1)
      if (address - last_address > 1)
        printCell (last_address, 1, 0);
      last_address = address;
      sc_regGet (4, &check_reg);
      if (!check_reg)
        address++;
      else
        last_address = address;
      sc_icounterSet (address);
      printCell (last_address, 1, 0);
      printCell (address, 0, 7);
    }
}
