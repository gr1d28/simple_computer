extern int CACHE[][12];
extern int SIZE;

int
sc_cacheGet (int address, int *value,
             int print) //Записывает в value одно значение из кэша по адресу
{
  if (address < 0 || address >= SIZE || !value)
    return -1;
  int str = address / 10;
  int col = address - str * 10 + 2;
  for (int i = 0; i < 5; i++)
    {
      if (CACHE[i][0] == str)
        {
          *value = CACHE[i][col];
          if (print == 0)
            CACHE[i][1]++;
          return 0;
        }
    }
  return -1;
}