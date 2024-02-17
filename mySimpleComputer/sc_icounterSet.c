extern unsigned int Icounter;

int
sc_icounterSet (int value)
{
  if (value >= 0x8000)
    return -1;
  Icounter = value;
  return 0;
}