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
  char file_name[20];
  int numbers[size];
  int check_numbers = 0;
  color fg = 1, bg = 0;
  keys key = -1;
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
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_regInit ();
  for (int i = 0; i < SIZE; i++)
    {
      sc_memorySet (i, 0);
      printCell (i, fg, bg);
    }
  printCell (0, 0, 7);
  bc_box (1, 1, 13, 60, 7, 9, "RAM", 1, 9);
  printKeys ();
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  sc_memoryGet (0, &value);
  printDecodedCommand (value);
  printTerm (0, 0);
  printBigCell (numbers, size, value, 0);

  rk_mytermsave ();
  rk_mytermregime (1, 0, 0, 1, 0);

  int address = 0, last_address = 0;
  while (key != ESC)
    {
      rk_readkey (&key);
      switch (key)
        {
        case 0:
          mt_gotoXY (25, 1);
          mt_delline ();
          write (1, "Введите имя файла для загрузки: ", 59);
          rk_mytermrestore ();
          read (1, file_name, 20);
          if (sc_memoryLoad (file_name) == -1)
            {
              mt_gotoXY (25, 1);
              mt_delline ();
              write (1, "Ошибка загрузки файла", 41);
            }
          else
            {
              mt_gotoXY (25, 1);
              mt_delline ();
            }
          for (int i = 0; i < SIZE; i++)
            printCell (i, fg, bg);
          printCell (address, 0, 7);
          printCounters ();
          printCommand ();
          sc_icounterGet (&value);
          sc_memoryGet (value, &value);
          printDecodedCommand (value);
          rk_mytermregime (1, 0, 0, 1, 0);
          break;

        case 1:
          mt_gotoXY (25, 1);
          mt_delline ();
          write (1, "Введите имя файла для сохранения: ", 63);
          rk_mytermrestore ();
          read (1, file_name, 20);
          if (sc_memorySave (file_name) == -1)
            {
              mt_gotoXY (25, 1);
              mt_delline ();
              write (1, "Ошибка записи в файл", 38);
            }
          else
            {
              mt_gotoXY (25, 1);
              mt_delline ();
            }
          printCell (address, 0, 7);
          rk_mytermregime (1, 0, 0, 1, 0);
          break;

        case 2:
          sc_accumulatorInit ();
          sc_icounterInit ();
          sc_memoryInit ();
          sc_regInit ();
          for (int i = 0; i < SIZE; i++)
            {
              sc_memorySet (i, 0);
              printCell (i, fg, bg);
            }
          printCell (address, 0, 7);
          printAccumulator ();
          printFlags ();
          printCounters ();
          printCommand ();
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printTerm (address, 0);
          printBigCell (numbers, size, value, address);
          break;

        case 6:
          mt_gotoXY (25, 1);
          write (
              1,
              "Введите значение для аккумулятора формата \"+2F4C\" <= 0x3FFF",
              97);
          mt_gotoXY (2, 69);
          rk_readvalue (&value, 100);
          sc_accumulatorSet (value);
          printAccumulator ();
          mt_gotoXY (25, 1);
          mt_delline ();
          break;

        case 7:
          mt_gotoXY (25, 1);
          write (1,
                 "Введите значение для счётчика команд формата \"+2F4C\" <= "
                 "0x3FFF",
                 102);
          mt_gotoXY (5, 79);
          rk_readvalue (&value, 100);
          sc_icounterSet (value);
          printCounters ();
          printCommand ();
          sc_memoryGet (value, &value);
          printDecodedCommand (value);
          mt_gotoXY (25, 1);
          mt_delline ();
          break;

        case 8:
          if (address < 10)
            {
              if (address <= 7)
                address += 120;
              else
                address += 110;
            }
          else
            address -= 10;
          printCell (last_address, fg, bg);
          last_address = address;
          printCell (address, 0, 7);
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printTerm (address, 0);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size, value, address);
          break;

        case 9:
          if (address >= 118)
            {
              if (address >= 120)
                address -= 120;
              else
                address -= 110;
            }
          else
            address += 10;
          printCell (last_address, fg, bg);
          last_address = address;
          printCell (address, 0, 7);
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printTerm (address, 0);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size, value, address);
          break;

        case 10:
          if ((address % 10) == 9)
            address -= 9;
          else
            address += 1;
          printCell (last_address, fg, bg);
          last_address = address;
          printCell (address, 0, 7);
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printTerm (address, 0);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size, value, address);
          break;

        case 11:
          if ((address % 10) == 0)
            address += 9;
          else
            address -= 1;
          printCell (last_address, fg, bg);
          last_address = address;
          printCell (address, 0, 7);
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          printTerm (address, 0);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size, value, address);
          break;

        case 14:
          mt_gotoXY (25, 1);
          write (1, "Введите значение формата \"+2F4C\" <= 0x3FFF", 65);
          mt_gotoXY (address / 10 + 2,
                     (address % 10) * 5 + (address % 10) + 2);
          rk_readvalue (&value, 100);
          mt_gotoXY (25, 1);
          mt_delline ();
          sc_memorySet (address, value);
          printCell (address, 0, 7);
          printDecodedCommand (value);
          printTerm (address, 1);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size, value, address);
          mt_gotoXY (25, 1);
          mt_delline ();
          break;
        }
    }

  rk_mytermrestore ();
  mt_delline ();

  return 0;
}