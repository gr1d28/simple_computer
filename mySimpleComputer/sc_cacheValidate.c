extern int CACHE[][12];

//проверка присутствия строки в кэше
int
sc_cacheValidate (int str_num)
{
  for (int i = 0; i < 5; i++)
    {
      if (CACHE[i][0] == str_num)
        return 0;
    }
  return -1;
}