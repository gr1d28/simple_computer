#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>
void
printTimer (void)
{
  int timer = 0;
  char T[3] = { 'T', ':', ' ' };
  char value[3] = { ' ', ' ', '\0' };
  mt_gotoXY (5, 65);
  sc_timerGet (&timer);
  sprintf (value, "%d", timer);
  if (timer < 10)
    value[1] = ' ';
  write (1, T, 3);
  write (1, value, 3);
}