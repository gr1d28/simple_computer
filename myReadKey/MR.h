#include <termios.h>
#ifndef MR
// struct termios
// {
//   tcflag_t c_iflag;
//   tcflag_t c_oflag;
//   tcflag_t c_lflag;
//   tcflag_t c_cflag;
//   tcflag_t c_cc[NCCS];

// };

typedef enum KEYS
{
  l = 0,
  s,
  i,
  r,
  t,
  ESC,
  F5,
  F6,
  up,
  down,
  right,
  left,
  minus,
  plus,
  ENTER
} keys;

#define MR
#endif

int rk_mytermsave (void);

int rk_mytermrestore (void);

int rk_readkey (keys *k);

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);

int rk_readvalue (int *value, int timeout);