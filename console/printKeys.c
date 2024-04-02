#include "BC.h"
#include "MT.h"
#include <unistd.h>

void
printKeys (void)
{
  bc_box (18, 76, 5, 30, 7, 9, "Keys", 1, 9);
  mt_gotoXY (19, 77);
  write (1, "l - load  s - save  i - reset", 30);
  mt_gotoXY (20, 77);
  write (1, "ESC - exit", 11);
  mt_gotoXY (21, 77);
  write (1, "ESC - exit", 11);
  mt_gotoXY (22, 77);
  write (1, "F5 - accumulator", 17);
  mt_gotoXY (23, 77);
  write (1, "F6 - instruction counter", 25);
}