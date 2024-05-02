extern int CACHE[][12];
extern int RAM[];
extern int SIZE;

//выгружает строку из кэша в RAM (строка остается в кэше)
int
sc_cacheStore (int str_num)
{
  if ((str_num * 10) > SIZE)
    return -1;
  int str_this = -1;
  for (int i = 0; i < 5; i++) //поиск строки
    {
      if (CACHE[i][0] == str_num)
        {
          str_this = i;
          break;
        }
    }
  if (str_this == -1)
    return -1;
  CACHE[str_this][1]++;
  for (int i = 2; i < 12; i++) //выгрузка значений из кэша в RAM
    {
      if ((str_num * 10 + i - 2) >= SIZE)
        break;
      RAM[str_num * 10 + i - 2] = CACHE[str_this][i];
    }
  return 0;
}