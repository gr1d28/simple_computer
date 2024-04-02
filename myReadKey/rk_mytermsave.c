#include "MR.h"
#include <stdio.h>
#include <unistd.h>

int
rk_mytermsave (void)
{
  struct termios tc_saved;
  FILE *fp = NULL;
  if (tcgetattr (1, &tc_saved) != 0)
    return -1;
  if ((fp = fopen ("termsettings", "wb")) == NULL)
    return -1;
  fwrite (&tc_saved, sizeof (tc_saved), 1, fp);
  fclose (fp);
  return 0;
}