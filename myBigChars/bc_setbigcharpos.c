int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  int byte = 8, xb = 0, mask = 0x1;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;
  if (x >= 0 && x <= 3)
    {
      mask = mask << x * byte + y;
      if (value)
        big[0] = big[0] | mask;
      else
        big[0] = big[0] & ~(mask);
    }
  else
    {
      mask = mask << (x - 4) * byte + y;
      if (value)
        big[1] = big[1] | mask;
      else
        big[1] = big[1] & ~(mask);
    }
  return 0;
}