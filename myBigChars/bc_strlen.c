#define MASK1 0x80
#define MASK2 0xc0
#define MASK3 0xe0
#define MASK4 0xf0
#define MASK5 0xf8

int bc_strlen (char * str)
{
  if(!str)
    return 0;

  if(str[0] & MASK1 == 0)
    return 1;
  
  if(str[0] & MASK3 == MASK2)
  {
    if(str[1] & MASK2 == MASK1)
      return 2;
    return 0;
  }

  if(str[0] & MASK4 == MASK3)
  {
    for(int i = 1; i < 3; i++)
    {
      if(str[i] & MASK2 != MASK1)
        return 0;
    }
    return 3;
  }
  if(str[0] & MASK5 == MASK4)
  {
    for(int i = 1; i < 4; i++)
    {
      if(str[i] & MASK2 != MASK1)
        return 0;
    }
    return 4;
  }
  return 0;
}