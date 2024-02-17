#include <stdio.h>
extern int RAM[];
extern int SIZE;

int
sc_memoryLoad (char *filename)
{
  FILE *fp = NULL;
  int buf[SIZE];
  if ((fp = fopen (filename, "wb")) == NULL)
    {
      fclose (fp);
      return -1;
    }
    
  if (fread (buf, sizeof (int), SIZE, fp) != SIZE)
    {
      fclose (fp);
      return -1;
    }

  for (int i = 0; i < SIZE; i++)
    RAM[i] = buf[i];
  fclose (fp);
  return 0;
}