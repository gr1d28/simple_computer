#include <stdio.h>
extern int RAM[];
extern int SIZE;

int sc_memorySave (char * filename)
{
    FILE *fp = NULL;
    if((fp = fopen(filename, "wb")) == NULL)
    {
        fclose(fp);
        return -1;
    }
    
    if(fwrite(RAM, sizeof(int), SIZE, fp) != SIZE)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}