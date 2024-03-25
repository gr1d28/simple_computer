#ifndef MT
#include "MT.h"
#define MT
#endif

int bc_getbigcharpos (int *big, int x, int y, int *value);

int bc_bigcharwrite (int fd, int *big, int count);

int bc_bigcharread (int fd, int *big, int need_count, int *count);

int bc_box (int x1, int y1, int x2, int y2, color box_fg, color box_bg,
            char *header, color header_fg, color header_bg);

int bc_printA (char *str);

int bc_printbigchar (int *big, int x, int y, color bg, color fg);

int bc_setbigcharpos (int *big, int x, int y, int value);

int bc_strlen (char *str);

char trans (int value);

int rev_trans (char c);