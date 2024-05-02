extern int CACHE[][12];
extern int RAM[];
extern int SIZE;

//загружает строку из RAM в кэш
int
sc_cacheLoad (int str_num)
{
  if ((str_num * 10) > SIZE)
    return -1;
  int min_count = CACHE[0][1], str_min = 0, str_this = -1;
  if (CACHE[0][0] == str_num)
    return -1;
  for (int i = 1; i < 5; i++) //определение строки с минимальным обращением
    {
      if (CACHE[i][0] == str_num)
        return -1;
      if (CACHE[i][1] < min_count)
        {
          min_count = CACHE[i][1];
          str_min = i;
        }
    }
  str_this = CACHE[str_min][0];
  if (str_this != -1)
    {
      for (int i = 2; i < 12; i++) //выгрузка старой строки(если она есть)
        {
          if ((str_this * 10 + i - 2) >= SIZE)
            break;
          RAM[str_this * 10 + i - 2] = CACHE[str_min][i];
        }
    }
  CACHE[str_min][0] = str_num;
  CACHE[str_min][1] = 1;
  for (int i = 2; i < 12; i++) //загрузка новой строки
    {
      if ((str_num * 10 + i - 2) >= SIZE)
        {
          CACHE[str_min][i] = 0;
          continue;
        }
      CACHE[str_min][i] = RAM[str_num * 10 + i - 2];
    }
  return 0;
}