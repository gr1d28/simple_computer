extern unsigned int time;
int
sc_timerSet (int value)
{
  if (value < 0)
    return -1;
  time = value;
  return 0;
}