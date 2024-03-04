#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK 0xF

char translate (int value);

void
printAccumulator (void)
{
  int accumulator, k;
  char sc[4] = { 's', 'c', ':', ' ' };
  char hex[5] = { 'h', 'e', 'x', ':', ' ' };
  char sc_buf[5];
  char hex_buf[4];
  int col = 60;
  sc_accumulatorGet (&accumulator);
  k = accumulator;
  if (k >> 15)
    sc_buf[0] = '-';
  else
    sc_buf[0] = '+';
  accumulator = accumulator ^ 0x8000;
  for (int i = 3; i >= 0; i--)
    {
      sc_buf[i + 1] = hex_buf[i] = translate (k & MASK);
      k = k >> 4;
    }
  mt_gotoXY (0, col);
  write (1, sc, 4);
  write (1, sc_buf, 5);
  col += 10;
  mt_gotoXY (0, col);
  write (1, hex, 5);
  write (1, hex_buf, 4);
}

// int main()
// {
//   sc_accumulatorInit();
//   sc_accumulatorSet(56);
//   printAccumulator();
//   return 0;
// }