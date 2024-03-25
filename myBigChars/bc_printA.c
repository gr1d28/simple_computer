#include <unistd.h>
#include <string.h>

int bc_printA (char * str) 
{
  int size = strlen(str);
  char enter_buf[3] = {'\E', '(', '0'};
  char exit_buf[3] = {'\E', '(', 'B'};
  write(1, enter_buf, 3);
  size = write(1, str, size);
  write(1, exit_buf, 3);
  return size;
}