extern char REG;
#define MASK1 0x1
#define MASK2 0x2
#define MASK3 0x4
#define MASK4 0x8
#define MASK5 0x10

int
sc_regSet (int registers, int value)
{
	char ans = 0x0;
	if (registers > 5 || registers <= 0)
		return -1;
	switch (registers)
		{
		case 1:
			ans = MASK1;
			break;
		case 2:
			ans = MASK2;
			break;
		case 3:
			ans = MASK3;
			break;
		case 4:
			ans = MASK4;
			break;
		case 5:
			ans = MASK5;
			break;
	
		default:
			break;
		}
	if (value)
		REG = REG | ans;
	else
		REG = REG & ~(ans);
	
	return 0;
}