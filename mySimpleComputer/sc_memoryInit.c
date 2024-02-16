extern int SIZE;
extern int RAM[];

int sc_memoryInit (void)
{
    for(int i = 0; i < SIZE; i++)
        RAM[i] = 0;
    return 0;
}