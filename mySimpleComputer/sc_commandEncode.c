int sc_commandEncode (int sign, int command, int operand, int * value)
{
    int res = 0;
    if(operand >= 0x80 || command >= 0x80 || (sign != 0 && sign != 1) || !value)
        return -1;
    res = sign;
    res = res << 7;
    res = res + command;
    res = res << 7;
    res = res + operand;

    *value = res;
    return 0;
}