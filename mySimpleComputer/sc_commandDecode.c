#define DEC_MASK 0x7F
int sc_commandDecode (int value, int * sign, int * command, int * operand)
{
    int res = value;
    if(!sign || !command || !operand)
        return -1;
    if((value >> 14) > 1)
        return -1;
    *operand = res & DEC_MASK;
    res = res >> 7;
    *command = res & DEC_MASK;
    *sign = res >> 7;
    return 0;
}