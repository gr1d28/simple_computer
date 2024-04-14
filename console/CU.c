#include "console.h"
#include <stdio.h>
#include <unistd.h>
extern char translate (int value);
extern int address;
extern int last_address;

void
CU (void)
{
  int value, command, operand, sign, k;
  char buf_address[5];
  value = sign = command = operand = k = 0;
  buf_address[4] = '\0';
  buf_address[3] = ' ';
  buf_address[2] = '>';
  sc_icounterGet (&value);
  sc_memoryGet (value, &value);
  // if(sc_commandValidate(value) != 0)
  // {
  //   sc_regSet(4, 1);
  //   printFlags();
  //   return;
  // }
  if (sc_commandDecode (value, &sign, &command, &operand) != 0)
    {
      sc_regSet (4, 1);
      printFlags ();
      return;
    }

  k = operand;
  buf_address[1] = translate (k & 0xF);
  k = k >> 4;
  buf_address[0] = translate (k & 0xF);

  if (command >= 0x1E && command <= 0x21)
    {
      ALU (command, operand);
      return;
    }

  switch (command)
    {
    case 0x0:
      // printTerm(operand, 0);
      break;

    case 0x1:
      printTerm (operand, 0);
      mt_gotoXY (26, 1);
      write (1, "Беляев Егор Ильич, группа ИВ-221", 56);
      break;

    case 0x0A:
      buf_address[2] = '<';
      write (1, buf_address, 4);
      if (rk_readvalue (&value, 100) != 0)
        value = 0;
      sc_memorySet (operand, value);
      printCell (operand, 1, 0);
      printTerm (operand, 1);
      // last_address = address;
      // address = operand;
      break;

    case 0x0B:
      printTerm (operand, 0);
      // last_address = address;
      // address = operand;
      break;

    case 0x14:
      sc_memoryGet (operand, &value);
      printTerm (operand, 0);
      sc_accumulatorSet (value);
      printAccumulator ();
      // last_address = address;
      // address = operand;
      break;

    case 0x15:
      sc_accumulatorGet (&value);
      sc_memorySet (operand, value);
      printCell (operand, 1, 0);
      printTerm (operand, 1);
      // last_address = address;
      // address = operand;
      break;

    case 0x28:
      printTerm (operand, 0);
      last_address = address;
      address = operand - 1;
      break;

    case 0x29:
      sc_accumulatorGet (&value);
      if ((value >> 14))
        {
          printTerm (operand, 0);
          last_address = address;
          address = operand - 1;
        }
      break;

    case 0x2A:
      sc_accumulatorGet (&value);
      value = value & 0x3FFF;
      if (value == 0)
        {
          printTerm (operand, 0);
          last_address = address;
          address = operand - 1;
        }
      break;

    case 0x2B:
      sc_regSet (4, 1);
      printFlags ();
      // printTerm(operand, 0);
      break;

    case 0x37:
      sc_accumulatorGet (&value);
      if (value >> 14 == 0)
        {
          printTerm (operand, 0);
          last_address = address;
          address = operand;
        }
      break;

    case 0x3D:
      sc_memoryGet (operand, &value);
      value = value >> 1;
      sc_memorySet (operand, value);
      printTerm (operand, 1);
      break;

    default:
      sc_regSet (5, 1);
      sc_regSet (4, 1);
      printFlags ();
    }
}

// 000101000000001