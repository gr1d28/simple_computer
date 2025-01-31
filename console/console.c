#include "console.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
extern int SIZE;
int address;
int last_address;
int numbers[36];
int size_of_numbers = 36;

void
signalhandlerusr (int signo)
{
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_regInit ();
  sc_timerInit ();
  sc_cacheInit ();
  for (int i = 0; i < SIZE; i++)
    {
      sc_memorySet (i, 0);
      printCell (i, 1, 0);
    }
}

void
fix_filename (char *file_name)
{
  int i = 0;
  while (file_name[i] != '\n')
    i++;
  file_name[i] = '\0';
}

int
main (int argc, char *argv[])
{
  int rows, cols, value;
  int fd;
  char *font_file_name = "font.bin";
  char file_name[50];
  int check_numbers = 0;
  address = 0;
  last_address = 0;
  color fg = 1, bg = 0;
  keys key = -1;
  struct itimerval ival, oval;
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
  sc_timerInit ();
  sc_cacheInit ();
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
  printBigCell (numbers, size_of_numbers, value, 0);
  printTimer ();
  printCache ();

  ival.it_interval.tv_sec = 0;
  ival.it_interval.tv_usec = 500000;
  ival.it_value.tv_sec = 0;
  ival.it_value.tv_usec = 500000;

  signal (SIGALRM, IRC);
  signal (SIGUSR1, signalhandlerusr);

  setitimer (ITIMER_REAL, &ival, &oval);

  rk_mytermsave ();
  rk_mytermregime (1, 0, 0, 1, 0);

  int step = 0;
  while (key != ESC)
    {
      rk_readkey (&key);
      // sc_regGet (4, &value);
      if (key == 4)
        {
          sc_regSet (4, 0);
          printFlags ();
          pause ();
          sc_timerGet (&value);
          while (value > 1)
            {
              pause ();
              sc_timerGet (&value);
            }
          if (value == 1)
            {
              pause ();
              pause ();
            }
          sc_timerGet (&value);
          while (value > 1)
            {
              pause ();
              sc_timerGet (&value);
            }
          if (value == 1)
            {
              pause ();
              pause ();
            }
          sc_regSet (4, 1);
          printFlags ();
          last_address = address;
          sc_memoryGet (address, &value);
          printBigCell (numbers, size_of_numbers, value, address);
          continue;
        }
      sc_regGet (4, &value);
      if (value == 0)
        continue;
      switch (key)
        {
        case 0:
          mt_gotoXY (26, 1);
          mt_delline ();
          write (1, "Введите имя файла для загрузки: ", 59);
          rk_mytermrestore ();
          read (1, file_name, 50);
          fix_filename (file_name);
          if (sc_memoryLoad (file_name) == -1)
            {
              mt_gotoXY (26, 1);
              mt_delline ();
              write (1, "Ошибка загрузки файла", 41);
            }
          else
            {
              mt_gotoXY (26, 1);
              mt_delline ();
            }
          sc_cacheInit ();
          for (int i = 0; i < SIZE; i++)
            printCell (i, fg, bg);
          printCell (address, 0, 7);
          printCounters ();
          printCommand ();
          sc_icounterGet (&value);
          sc_memoryGet (value, &value);
          printDecodedCommand (value);
          printCache ();
          rk_mytermregime (1, 0, 0, 1, 0);
          break;

        case 1:
          mt_gotoXY (26, 1);
          mt_delline ();
          write (1, "Введите имя файла для сохранения: ", 63);
          rk_mytermrestore ();
          read (1, file_name, 50);
          fix_filename (file_name);
          if (sc_memorySave (file_name) == -1)
            {
              mt_gotoXY (26, 1);
              mt_delline ();
              write (1, "Ошибка записи в файл", 38);
            }
          else
            {
              mt_gotoXY (26, 1);
              mt_delline ();
            }
          printCell (address, 0, 7);
          rk_mytermregime (1, 0, 0, 1, 0);
          break;

        case 2:
          raise (SIGUSR1);
          printCell (address, 0, 7);
          printAccumulator ();
          printFlags ();
          printCounters ();
          printCommand ();
          sc_memoryGet (address, &value);
          printDecodedCommand (value);
          // printTerm (address, 0);
          printBigCell (numbers, size_of_numbers, value, address);
          printTimer ();
          printCache ();
          break;

        case 3:
          sc_regGet (4, &value);

          if (value)
            {
              sc_regSet (4, 0);
              sc_regSet (5, 0);
              printFlags ();
              pause ();
              printCell (last_address, fg, bg);
              printCell (address, 0, 7);
              last_address = address;
              sc_memoryGet (address, &value);
              printBigCell (numbers, size_of_numbers, value, address);
            }
          else
            {
              alarm (0);
              sc_regSet (4, 1);
              printFlags ();
            }
          break;
        case 6:
          mt_gotoXY (26, 1);
          write (
              1,
              "Введите значение для аккумулятора формата \"+2F4C\" <= 0x3FFF",
              97);
          mt_gotoXY (2, 69);
          if (rk_readvalue (&value, 100) != 0)
            {
              sc_regSet (1, 1);
              printFlags ();
              break;
            }
          else
            {
              sc_regSet (1, 0);
              printFlags ();
            }
          sc_accumulatorSet (value);
          printAccumulator ();
          mt_gotoXY (26, 1);
          mt_delline ();
          break;

        case 7:
          mt_gotoXY (26, 1);
          write (1,
                 "Введите значение для счётчика команд формата \"+2F4C\" <= "
                 "0x3FFF",
                 102);
          mt_gotoXY (5, 79);
          if (rk_readvalue (&value, 100) != 0)
            {
              sc_regSet (1, 1);
              printFlags ();
              break;
            }
          else if (value < 0 || value > 127)
            {
              sc_regSet (3, 1);
              printFlags ();
              value = 0;
              break;
            }
          else
            {
              sc_regSet (1, 0);
              sc_regSet (3, 0);
              printFlags ();
            }
          last_address = address;
          address = value;
          sc_icounterSet (value);
          printCounters ();
          printCommand ();
          sc_memoryGet (address, &value);
          printCell (address, 0, 7);
          printCell (last_address, fg, bg);
          printBigCell (numbers, size_of_numbers, value, address);
          printDecodedCommand (value);
          mt_gotoXY (26, 1);
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
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size_of_numbers, value, address);
          sc_regGet (3, &value);
          if (value)
            {
              sc_regSet (3, 0);
              printFlags ();
            }
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
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size_of_numbers, value, address);
          sc_regGet (3, &value);
          if (value)
            {
              sc_regSet (3, 0);
              printFlags ();
            }
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
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size_of_numbers, value, address);
          sc_regGet (3, &value);
          if (value)
            {
              sc_regSet (3, 0);
              printFlags ();
            }
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
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size_of_numbers, value, address);
          sc_regGet (3, &value);
          if (value)
            {
              sc_regSet (3, 0);
              printFlags ();
            }
          break;

        case 14:
          mt_gotoXY (26, 1);
          write (1, "Введите значение формата \"+2F4C\" <= 0x3FFF", 65);
          mt_gotoXY (address / 10 + 2,
                     (address % 10) * 5 + (address % 10) + 2);
          if (rk_readvalue (&value, 100) != 0)
            {
              sc_regSet (1, 1);
              printFlags ();
              printCell (address, 0, 7);
              break;
            }
          else
            {
              sc_regSet (1, 0);
              printFlags ();
            }
          mt_gotoXY (26, 1);
          mt_delline ();
          sc_memorySet (address, value);
          if (sc_cacheValidate (address / 10) != 0)
            {
              int t = 10;
              sc_timerSet (t);
              printTimer ();
              while (t > 0)
                {
                  pause ();
                  sc_timerTick ();
                  printTimer ();
                  sc_timerGet (&t);
                }
              sc_cacheLoad (address / 10);
            }
          else
            sc_cacheSet (address, value);
          printCache ();
          printCell (address, 0, 7);
          printDecodedCommand (value);
          sc_icounterSet (address);
          printCounters ();
          printCommand ();
          printBigCell (numbers, size_of_numbers, value, address);
          mt_gotoXY (26, 1);
          mt_delline ();
          break;
        }
    }

  rk_mytermrestore ();
  mt_gotoXY (26, 1);
  mt_delline ();
  return 0;
}