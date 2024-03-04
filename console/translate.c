char
translate (int value)
{
  char ans = '\0';
  switch (value)
    {
    case 0:
      ans = '0';
      break;
    case 1:
      ans = '1';
      break;
    case 2:
      ans = '2';
      break;
    case 3:
      ans = '3';
      break;
    case 4:
      ans = '4';
      break;
    case 5:
      ans = '5';
      break;
    case 6:
      ans = '6';
      break;
    case 7:
      ans = '7';
      break;
    case 8:
      ans = '8';
      break;
    case 9:
      ans = '9';
      break;
    case 10:
      ans = 'A';
      break;
    case 11:
      ans = 'B';
      break;
    case 12:
      ans = 'C';
      break;
    case 13:
      ans = 'D';
      break;
    case 14:
      ans = 'E';
      break;
    case 15:
      ans = 'F';
      break;
    }
  return ans;
}