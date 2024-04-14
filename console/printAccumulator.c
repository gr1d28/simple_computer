#include "BC.h"
#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK3 0x7
#define MASK4 0xF

char translate (int value);

void
printAccumulator (void)
{
  int accumulator, k, shift = 0;
  char sc[4] = { 's', 'c', ':', ' ' };
  char hex[5] = { 'h', 'e', 'x', ':', ' ' };
  char sc_buf[5];
  char hex_buf[4];
  int col = 65;
  sc_accumulatorGet (&accumulator);
  k = accumulator;
  if (accumulator >> 14)
    {
      sc_buf[0] = '-';
      k = (~(k & 0x3FFF) | 0x4000 + 1) & 0x7FFF;
    }
  else
    sc_buf[0] = '+';

  accumulator = accumulator & 0x3FFF;
  for (int i = 3; i >= 0; i--)
    {
      if (i % 2 != 0)
        {
          sc_buf[i + 1] = translate (accumulator & MASK4);
          // hex_buf[i] = translate(k & MASK4);
          shift = 4;
        }
      else
        {
          sc_buf[i + 1] = translate (accumulator & MASK3);
          // hex_buf[i] = translate(k & MASK3);
          shift = 3;
        }
      hex_buf[i] = translate (k & MASK4);
      accumulator = accumulator >> shift;
      k = k >> 4;
      // sc_buf[i + 1] = translate (accumulator & MASK);
      // hex_buf[i] = translate (k & MASK);
      // accumulator = accumulator >> 4;
      // k = k >> 4;
    }
  bc_box (1, col - 2, 1, 21, 7, 9, "Accumulator", 1, 9);
  mt_gotoXY (2, col);
  write (1, sc, 4);
  write (1, sc_buf, 5);
  col += 10;
  mt_gotoXY (2, col);
  write (1, hex, 5);
  write (1, hex_buf, 4);
}