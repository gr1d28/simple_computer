#include <unistd.h>
int
mt_clrscr (void)
{
  int clrscr = 7, setcrs = 6;
  if (write (1, "\E[H\E[2J", clrscr) != clrscr)
    return -1;
  if (write (1, "\E[1;1H", setcrs) != setcrs)
    return -1;
  return 0;
}