extern int RAM[];
extern int SIZE;

int sc_memorySet (int address, int value)
{
    if(address >= SIZE)
        return -1;
    RAM[address] = value;
    return 0;
}