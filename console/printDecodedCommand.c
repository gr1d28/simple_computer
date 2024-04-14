#include "BC.h"
#include "MT.h"
#include <stdio.h>
#include <unistd.h>
#define BINMASK 0x1
#define OCTMASK 0x7
#define HEXMASK 0xF

char translate (int value);

void
printDecodedCommand (int value)
{
  char bin[5] = { 'b', 'i', 'n', ':', ' ' };
  char oct[5] = { 'o', 'c', 't', ':', ' ' };
  char dec[5] = { 'd', 'e', 'c', ':', ' ' };
  char hex[5] = { 'h', 'e', 'x', ':', ' ' };
  char bin_buf[15];
  char oct_buf[5];
  char dec_buf[5] = { ' ', ' ', ' ', ' ', ' ' };
  char hex_buf[4];
  int k;
  int str = 19, col = 3;
  mt_gotoXY (str, col);
  write (1, dec, 5);
  write (1, dec_buf, 5);
  if (value >> 14)
    value = (~(value & 0x3FFF) | 0x4000 + 1) & 0x7FFF;
  k = value;
  sprintf (dec_buf, "%d", k);
  for (int i = 14; i >= 0; i--)
    {
      if (k & BINMASK)
        bin_buf[i] = '1';
      else
        bin_buf[i] = '0';
      k = k >> 1;
    }
  k = value;
  for (int i = 4; i >= 0; i--)
    {
      oct_buf[i] = translate (k & OCTMASK);
      k = k >> 3;
    }
  k = value;
  for (int i = 3; i >= 0; i--)
    {
      hex_buf[i] = translate (k & HEXMASK);
      k = k >> 4;
    }
  bc_box (str - 1, col - 2, 1, 60, 7, 9, "Editable memory cell (format)", 1,
          7);
  mt_gotoXY (str, col);
  write (1, dec, 5);
  write (1, dec_buf, 5);
  col += 13;
  mt_gotoXY (str, col);
  write (1, oct, 5);
  write (1, oct_buf, 5);
  col += 13;
  mt_gotoXY (str, col);
  write (1, hex, 5);
  write (1, hex_buf, 4);
  col += 12;
  mt_gotoXY (str, col);
  write (1, bin, 5);
  write (1, bin_buf, 15);
  write (1, " ", 1);
}
