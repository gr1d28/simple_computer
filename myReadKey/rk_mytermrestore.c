#include "MR.h"
#include <stdio.h>
#include <unistd.h>

int
rk_mytermrestore (void)
{
  struct termios tc_saved;
  FILE *fp = NULL;
  if ((fp = fopen ("termsettings", "rb")) == NULL)
    return -1;
  fread (&tc_saved, sizeof (tc_saved), 1, fp);
  if (tcsetattr (1, TCSANOW, &tc_saved) != 0)
    return -1;
  fclose (fp);
  return 0;
}