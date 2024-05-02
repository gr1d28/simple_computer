extern int CACHE[][12];
extern int SIZE;

int sc_cacheSet (int address,
                 int value) //устанавливает значение в кэше по адресу в value
{
  if (address < 0 || address >= SIZE)
    return -1;
  int str = address / 10;
  int col = address - str * 10 + 2;
  for (int i = 0; i < 5; i++)
    {
      if (CACHE[i][0] == str)
        {
          CACHE[i][col] = value;
          CACHE[i][1]++;
          return 0;
        }
    }
  return -1;
}