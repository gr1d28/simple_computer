extern unsigned int Icounter;

int sc_icounterGet (int * value)
{
    if(!value)
        return -1;
    *value = Icounter;
    return 0;
}