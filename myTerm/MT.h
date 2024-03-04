typedef struct WS
{
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
} winsize;

typedef enum CL
{
  black = 0,
  red,
  green,
  yellow,
  blue,
  purple,
  l_blue,
  white,
  grey
} color;

int mt_clrscr (void);

int mt_delline (void);

int mt_getscreensize (int *rows, int *cols);

int mt_gotoXY (int str, int col);

int mt_setbgcolor (color cl);

int mt_setcursorvisible (int value);

int mt_setdefaultcolor (void);

int mt_setfgcolor (color cl);