#include "console.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
extern int SIZE;

int
main (int argc, char *argv[])
{
  int rows, cols, value;
  int size = 18 * 2, fd;
  char *font_file_name = "font.bin";
  int numbers[size];
  int check_numbers = 0;
  color fg = 1, bg = 0;
  mt_clrscr ();
  if (!isatty (1))
    {
      write (2, "Дескриптор не связан с файлом терминала\n", 75);
      return -1;
    }
  if (mt_getscreensize (&rows, &cols) != 0)
    {
      write (2, "Невозможно получить размер экрана терминала\n", 84);
      return -1;
    }
  if (rows < 26 || cols < 100)
    {
      write (2, "Недостаточный размер экрана терминала\n", 73);
      return -1;
    }
  if (argc == 2)
    {
      fd = open (argv[1], O_RDONLY);
      if (fd == -1)
        {
          write (2, "Не удалось открыть указанный файл шрифтов\n", 79);
          return -1;
        }
    }
  else
    {
      font ();
      fd = open (font_file_name, O_RDONLY);
      if (fd == -1)
        {
          write (2, "Не удалось открыть файл font.bin\n", 54);
          return -1;
        }
    }

  bc_bigcharread (fd, numbers, 18, &check_numbers);
  close (fd);
  // printBigCell(numbers, size, 15);
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_regInit ();
  for (int i = 0; i < SIZE; i++)
    {
      sc_memorySet (i, i);
      if (i == 4)
        printCell (4, 0, 7);
      else
        printCell (i, fg, bg);
    }
  bc_box (1, 1, 13, 60, 7, 9, "RAM", 1, 9);
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  sc_memoryGet (4, &value);
  printDecodedCommand (value);
  printTerm (4, 0);
  int k = 1;
  for (int i = 4; i < SIZE; i++)
    {
      printTerm (i, 0);
      printCell (i, 0, 7);
      printCell (i - 1, fg, bg);
      sc_memoryGet (i, &value);
      printDecodedCommand (value);
      printBigCell (numbers, size, value, i);
      sc_icounterSet (k);
      printCounters ();
      printCommand ();
      k++;
      sleep (1);
    }
  return 0;
}