#include "MT.h"
#include "SC.h"
#include "BC.h"
#include <stdio.h>
#include <unistd.h>
#define MASK 0xF
char translate (int value);

void
printCommand (void)
{
  char buf[10];
  int icount_value, mem_value, sign, command, operand, str = 5, col = 91;
  sc_icounterGet (&icount_value);
  if (sc_memoryGet (icount_value, &mem_value) != 0)
    buf[0] = '!';
  else
    buf[0] = ' ';
  sc_commandDecode (mem_value, &sign, &command, &operand);
  buf[1] = sign ? '-' : '+';
  buf[2] = ' ';
  buf[4] = translate (command & MASK);
  command = command >> 4;
  buf[3] = translate (command & MASK);
  buf[5] = ' ';
  buf[6] = ':';
  buf[7] = ' ';
  buf[9] = translate (operand & MASK);
  operand = operand >> 4;
  buf[8] = translate (operand & MASK);
  
  bc_box(str - 1, col - 5, 1, 21, 7, 9, "Command", 1, 9);
  mt_gotoXY (str, col);
  write (1, buf, 10);
}