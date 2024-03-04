#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MASK 0xF
char translate (int value);
void
printTerm (int address, int input)
{
  int value = 0, str = 18, col = 61;
  static int c = 1;
  static char this[9] = { '0', '3', '>', ' ' };
  static char first[9] = { '0', '2', '>', ' ' };
  static char second[9] = { '0', '1', '>', ' ' };
  static char third[9] = { '0', '0', '>', ' ' };

  if (c)
    {
      sc_memoryGet (0, &value);
      third[4] = (value >> 15) ? '-' : '+';
      for (int i = 8; i >= 5; i--)
        {
          third[i] = translate (value & MASK);
          value = value >> 4;
        }
      sc_memoryGet (1, &value);
      second[4] = (value >> 15) ? '-' : '+';
      for (int i = 8; i >= 5; i--)
        {
          second[i] = translate (value & MASK);
          value = value >> 4;
        }
      sc_memoryGet (2, &value);
      first[4] = (value >> 15) ? '-' : '+';
      for (int i = 8; i >= 5; i--)
        {
          first[i] = translate (value & MASK);
          value = value >> 4;
        }
      sc_memoryGet (3, &value);
      this[4] = (value >> 15) ? '-' : '+';
      for (int i = 8; i >= 5; i--)
        {
          this[i] = translate (value & MASK);
          value = value >> 4;
        }
      c = 0;
    }
  strncpy (third, second, 9);
  strncpy (second, first, 9);
  strncpy (first, this, 9);
  sprintf (this, "%d> ", address);

  this[1] = translate (address & MASK);
  address = address >> 4;
  this[0] = translate (address & MASK);
  this[2] = '>';
  this[3] = ' ';
  if (input == 0)
    {
      sc_memoryGet (address, &value);
      this[4] = (value >> 15) ? '-' : '+';
      for (int i = 8; i >= 5; i--)
        {
          this[i] = translate (value & MASK);
          value = value >> 4;
        }
    }

  mt_gotoXY (str, col);
  write (1, this, 10);
  str++;
  mt_gotoXY (str, col);
  write (1, first, 10);
  str++;
  mt_gotoXY (str, col);
  write (1, second, 10);
  str++;
  mt_gotoXY (str, col);
  write (1, third, 10);
}