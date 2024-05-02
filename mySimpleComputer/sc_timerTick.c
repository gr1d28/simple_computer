extern unsigned int time;
int
sc_timerTick (void)
{
  if (time == 0)
    return -1;
  time--;
  return 0;
}