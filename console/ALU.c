#include "console.h"
#include <stdio.h>
#include <unistd.h>

int
ALU (int command, int operand)
{
  int a = 0, b = 0, res = 0;
  sc_accumulatorGet (&a);
  sc_cacheGet (operand, &b, 0);

  if (a >> 14)
    {
      a = (a & 0x3FFF) * (-1);
    }
  if (b >> 14)
    {
      b = (b & 0x3FFF) * (-1);
    }

  switch (command)
    {
    case 0x1E:

      res = a + b;
      break;

    case 0x1F:
      res = a - b;
      break;

    case 0x20:
      if (b != 0)
        {
          res = a / b;
          sc_regSet (2, 0);
        }
      else
        {
          sc_regSet (2, 1);
          sc_regSet (4, 1);
          return 0;
        }
      break;

    case 0x21:
      res = a * b;
      break;
    }

  if (res < 0)
    {
      res *= -1;
      res = res | 0x4000;
    }

  if (sc_accumulatorSet (res) != 0)
    return -1;
  printAccumulator ();
  return 0;
}