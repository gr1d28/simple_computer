#include "BC.h"
#include <unistd.h>
#define SIM "a"
#define NSIM " "
#define MASK 0x80

int
bc_printbigchar (int *big, int x, int y, color bg, color fg)
{
  int check = 0;
  mt_gotoXY (x, y);
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);
  for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 4; j++)
        {
          for (int k = 0; k < 8; k++)
            {
              bc_getbigcharpos (big, j + i * 4, k, &check);
              if (check)
                bc_printA (SIM);
              else
                bc_printA (NSIM);
            }
          x++;
          mt_gotoXY (x, y);
        }
    }
  mt_setdefaultcolor ();
}