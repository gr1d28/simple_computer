int
sc_commandValidate (int command)
{
  if (command == 0x0 || command == 0x1 || command == 0xA || command == 0xB
      || command == 0x14 || command == 0x15)
    return 0;
  else if (command >= 0x1E && command <= 0x21)
    return 0;
  else if (command >= 0x28 && command <= 0x2B)
    return 0;
  else if (command >= 0x33 && command <= 0x4C)
    return 0;
  else
    return -1;
}