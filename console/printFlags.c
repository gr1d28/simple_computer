#include <stdio.h>
extern char REG;

void printFlags (void)
{
    char flags = REG;
    char names[5] = { 'E', 'T', 'M', '0', 'P'};
    for(int i = 4; i >= 0; i--)
    {
        if(((flags >> i) & 0x1) == 1)
            printf("%c", names[i]);
        else
            printf("_");
    }
    printf("\n");
}