extern unsigned int time;
int
sc_timerGet (int *value)
{
  if (!value)
    return -1;
  *value = time;
  return 0;
}