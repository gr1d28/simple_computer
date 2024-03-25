#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "BC.h"
#include "font.h"

int font()
{
  int size = 18;
  int mas[36] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, E, F, plus, minus};
  int fd = open("font.bin",  O_CREAT | O_WRONLY, S_IRWXU);
  bc_bigcharwrite(fd, mas, 18);
  close(fd);
  return 0;
}