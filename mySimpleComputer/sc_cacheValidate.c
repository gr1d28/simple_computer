extern int CACHE[][12];

int sc_cacheValidate (int str_num) //проверка присутствия строки в кэше
{
  for (int i = 0; i < 5; i++)
    {
      if (CACHE[i][0] == str_num)
        return 0;
    }
  return -1;
}