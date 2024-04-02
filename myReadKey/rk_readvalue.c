#include "MR.h"
#include <stdio.h>
#include <unistd.h>
#define MASK_MINUS 0x4000

int
transl (int key, char *c)
{
  switch (key)
    {
    case 48: // 0
      *c = '0';
      return 0;
    case 49:
      *c = '1';
      return 1;
    case 50:
      *c = '2';
      return 2;
    case 51:
      *c = '3';
      return 3;
    case 52:
      *c = '4';
      return 4;
    case 53:
      *c = '5';
      return 5;
    case 54:
      *c = '6';
      return 6;
    case 55:
      *c = '7';
      return 7;
    case 56:
      *c = '8';
      return 8;
    case 57:
      *c = '9';
      return 9;
    case 65:
      *c = 'A';
      return 10;
    case 66:
      *c = 'B';
      return 11;
    case 67:
      *c = 'C';
      return 12;
    case 68:
      *c = 'D';
      return 13;
    case 69:
      *c = 'E';
      return 14;
    case 70:
      *c = 'F';
      return 15;
    case 97:
      *c = 'A';
      return 10;
    case 98:
      *c = 'B';
      return 11;
    case 99:
      *c = 'C';
      return 12;
    case 100:
      *c = 'D';
      return 13;
    case 101:
      *c = 'E';
      return 14;
    case 102:
      *c = 'F';
      return 15;
    }
  *c = ' ';
  return -1;
}

int
rk_readvalue (int *value, int timeout)
{
  keys k = 0;
  int v = 0;
  struct termios tc_saved;
  if (tcgetattr (1, &tc_saved) != 0)
    return -1;
  rk_mytermregime (1, timeout, 0, 1, 0);

  rk_readkey (&k);
  if (k == plus)
    {
      write (1, "+", 1);
      v = 0;
    }
  else if (k == minus)
    {
      write (1, "-", 1);
      v = v | MASK_MINUS;
    }
  else
    {
      tcsetattr (1, TCSANOW, &tc_saved);
      return -1;
    }

  for (int i = 3; i >= 0; i--)
    {
      rk_readkey (&k);
      int tmp = -1;
      char c = ' ';
      if ((tmp = transl (k, &c)) == -1 || (i == 3 && tmp > 3))
        {
          tcsetattr (1, TCSANOW, &tc_saved);
          return -1;
        }
      write (1, &c, 1);
      v = v | (tmp << i * 4);
    }
  tcsetattr (1, TCSANOW, &tc_saved);
  if (v > 0x7FFF)
    return -1;
  *value = v;
  return 0;
}
