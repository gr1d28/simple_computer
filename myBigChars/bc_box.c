#include "BC.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define LEFT_UP "l"
#define RIGHT_UP "k"
#define LEFT_DOWN "m"
#define RIGHT_DOWN "j"
#define HORIZONTAL "q"
#define VERTICAL "x"

int
bc_box (int x1, int y1, int x2, int y2, color box_fg, color box_bg,
        char *header, color header_fg, color header_bg)
{
  int size = strlen (header);
  int start_header;
  if (size <= y2)
    {
      start_header = (y2 - size) / 2 + y1 + 1;
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (x1, start_header);
      write (1, header, size);
    }
  else
    return -1;
  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  mt_gotoXY (x1, y1);
  write (1, "\E(0", 3);
  write (1, LEFT_UP, 1);
  for (int i = 0; i < (start_header - y1 - 1); i++)
    write (1, HORIZONTAL, 1);
  mt_gotoXY (x1, start_header + size);
  for (int i = 0; i < y2 - ((y2 - size) / 2 + size); i++)
    write (1, HORIZONTAL, 1);
  write (1, RIGHT_UP, 1);
  for (int i = 1; i < x2 + 1; i++)
    {
      mt_gotoXY (x1 + i, y1);
      write (1, VERTICAL, 1);
      mt_gotoXY (x1 + i, y1 + y2 + 1);
      write (1, VERTICAL, 1);
    }
  mt_gotoXY (x1 + x2 + 1, y1);
  write (1, LEFT_DOWN, 1);
  for (int i = 1; i < y2 + 1; i++)
    write (1, HORIZONTAL, 1);
  write (1, RIGHT_DOWN, 1);
  mt_setdefaultcolor ();
  write (1, "\E(B", 3);
  return 0;
}