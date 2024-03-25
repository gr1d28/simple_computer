int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int byte = 8, xb = 0, mask = 0x1, ans = 0;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;
  if (x >= 0 && x <= 3)
    {
      mask = mask << x * byte + y;
      ans = big[0] & mask;
    }
  else
    {
      mask = mask << (x - 4) * byte + y;
      ans = big[1] & mask;
    }
  *value = ans;
  return 0;
}