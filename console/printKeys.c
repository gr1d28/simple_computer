#include "BC.h"
#include "MT.h"
#include <unistd.h>

void
printKeys (void)
{
  bc_box (19, 79, 5, 30, 7, 9, "Keys", 2, 7);
  mt_gotoXY (20, 80);
  write (1, "l - load  s - save  i - reset", 30);
  mt_gotoXY (21, 80);
  write (1, "r - run   t - step", 19);
  mt_gotoXY (22, 80);
  write (1, "ESC - exit", 11);
  mt_gotoXY (23, 80);
  write (1, "F5 - accumulator", 17);
  mt_gotoXY (24, 80);
  write (1, "F6 - instruction counter", 25);
}