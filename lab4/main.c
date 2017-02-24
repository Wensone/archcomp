#include "rk.h"

int main()
{
    KEYS k;
    rk_readkey(&k);
    printf("=====>\n");
    printf("%d", k);
    return 0;
}