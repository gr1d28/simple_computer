#include "pr01.h"
#include "SC.h"

int
main ()
{
  int c = 0, ans = -1;
  if (sc_memoryInit () != 0)
    {
      printf ("Ошибка инициализации оперативной памяти\n");
      return 0;
    }
  if (sc_accumulatorInit () != 0)
    {
      printf ("Ошибка инициализации аккумулятора\n");
      return 0;
    }
  if (sc_icounterInit () != 0)
    {
      printf ("Ошибка инициализации счетчика команд\n");
      return 0;
    }
  if (sc_regInit () != 0)
    {
      printf ("Ошибка инициализации регистра флагов\n");
      return 0;
    }

  for (int i = 0; i < 10; i++)
    {
      if (sc_memorySet ((rand () % SIZE), rand () % 0x8000) != 0)
        printf ("Ошибка при инициализации памяти\n");
    }

  for (int i = 0; i < SIZE; i++)
    {
      if (i % 10 == 0)
        printf ("\n");
      printf ("%d ", RAM[i]);
    }
  printf ("\n");

  if (sc_memorySet (22, 0x8400) != 0)
    printf ("Недопустимое значение памяти\n");

  printFlags ();
  sc_regSet (1, 1);
  sc_regSet (2, 1);
  sc_regSet (4, 1);
  printFlags ();

  if (sc_regSet (6, 1) != 0)
    printf ("Некорректное значение флагов\n");
  printFlags ();

  sc_accumulatorSet (106);
  printAccumulator ();

  if (sc_accumulatorSet (0x9000) != 0)
    printf ("Некорректное значение аккумулятора\n");
  printAccumulator ();

  sc_icounterSet (4);
  printCounters ();

  if (sc_icounterSet (0x9000) != 0)
    printf ("Некорректное значение счетчика команд\n");
  printCounters ();

  c = 102;
  ans = -1;
  sc_memoryGet (c, &ans);
  printf ("Значение ячейки памяти с адресом %d: %d\n", c, ans);

  ans = -1;
  sc_accumulatorGet (&ans);
  printf ("Значение аккумулятора: %d\n", ans);

  ans = 0;
  if (sc_commandEncode (0, 0x33, 0x59, &ans) != 0)
    printf ("Ошибка при кодировании команды\n");
  else
    printDecodedCommand (ans);
  printf ("%d\n", ans);

  return 0;
}