extern unsigned int Accumulator;

int sc_accumulatorGet (int * value)
{
    if(!value)
        return -1;
    *value = Accumulator;
    return 0;
}