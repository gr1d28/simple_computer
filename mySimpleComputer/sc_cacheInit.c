extern int CACHE[][12];

int
sc_cacheInit (void)
{
  for (int i = 0; i < 5; i++)
    {
      CACHE[i][0] = -1;
      for (int j = 1; j < 12; j++)
        CACHE[i][j] = 0;
    }
  return 0;
}