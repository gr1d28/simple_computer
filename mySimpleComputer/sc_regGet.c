extern char REG;

int
sc_regGet (int registers, int * value)
{
	int ans = 0;
	if (registers > 5 || registers <= 0 || !value)
		return -1;
	
	switch (registers)
		{
		case 1:
			ans = (REG >> 4) & 0x1;
			break;
		case 2:
			ans = (REG >> 3) & 0x1;
			break;
		case 3:
			ans = (REG >> 2) & 0x1;
			break;
		case 4:
			ans = (REG >> 1) & 0x1;
			break;
		case 5:
			ans = REG & 0x1;
			break;
	
		default:
			break;
		}

	*value = ans;
	return 0;
}