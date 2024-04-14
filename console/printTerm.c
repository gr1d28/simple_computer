#include "BC.h"
#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MASK3 0x7
#define MASK4 0xF
char translate (int value);
void
printTerm (int address, int input)
{
  int value = 0, str = 19, col = 65;
  static int c = 1;
  static char this[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  static char first[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  static char second[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  static char third[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };

  strncpy (third, second, 9);
  strncpy (second, first, 9);
  strncpy (first, this, 9);
  value = address;
  this[1] = translate (value & MASK4);
  value = value >> 4;
  this[0] = translate (value & MASK4);

  sc_memoryGet (address, &value);
  this[4] = (value >> 14) ? '-' : '+';
  value = value & 0x3FFF;
  for (int i = 8; i >= 5; i--)
    {
      if (i % 2 == 0)
        {
          this[i] = translate (value & MASK4);
          value = value >> 4;
        }
      else
        {
          this[i] = translate (value & MASK3);
          value = value >> 3;
        }
      // this[i] = translate (value & MASK);
      // value = value >> 4;
    }
  if (input == 0)
    this[2] = '>';
  else
    this[2] = '<';
  bc_box (str - 1, col - 1, 4, 9, 7, 9, "IN--OUT", 2, 7);
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