#include "MT.h"
#include <sys/ioctl.h>

int
mt_getscreensize (int *rows, int *cols)
{
  winsize ws;
  if (ioctl (1, TIOCGWINSZ, &ws))
    return -1;
  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}