#include "MR.h"
#include <unistd.h>

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios tc_on;
  if (tcgetattr (1, &tc_on) != 0)
    return -1;
  if (regime) // regime == 1 - неканоничный
    {
      tc_on.c_lflag &= ~(ICANON);

      if (echo)
        tc_on.c_lflag &= ~(ECHO);
      else
        tc_on.c_lflag |= (ECHO);

      if (sigint)
        tc_on.c_lflag &= ~(ISIG);
      else
        tc_on.c_lflag |= (ISIG);

      tc_on.c_cc[VMIN] = vmin;
      tc_on.c_cc[VTIME] = vtime;
    }
  else
    tc_on.c_lflag |= ICANON;

  return (tcsetattr (1, TCSANOW, &tc_on));
}