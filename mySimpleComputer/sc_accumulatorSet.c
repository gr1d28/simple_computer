extern unsigned int Accumulator;

int sc_accumulatorSet (int value)
{
    if(value >= 0x8000)
        return -1;
    Accumulator = value;
    return 0;
}