extern int RAM[];
extern int SIZE;

int
sc_memoryGet (int address, int *value)
{
  if (address >= SIZE || !value || address < 0)
    return -1;
  *value = RAM[address];
  return 0;
}