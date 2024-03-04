#include "console.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
extern int SIZE;

int
main ()
{
  int rows, cols, value;
  color fg = 1, bg = 0;
  if (!isatty (1))
    {
      printf ("Дескриптор не связан с файлом терминала\n");
      return -1;
    }
  if (mt_getscreensize (&rows, &cols) != 0)
    {
      printf ("Невозможно получить размер экрана терминала\n");
      return -1;
    }
  if (rows < 26 || cols < 100)
    {
      printf ("Недостаточный размер экрана терминала\n");
      return -1;
    }
  mt_clrscr ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_regInit ();
  for (int i = 0; i < SIZE; i++)
    {
      if (i == 4)
        printCell (4, 0, 7);
      else
        printCell (i, fg, bg);
    }
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  sc_memoryGet (4, &value);
  printDecodedCommand (value);
  printTerm (4, 0);
  return 0;
}