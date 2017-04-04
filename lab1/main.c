#include "head/SimpleComputer.h"

void print(int i, int n)
{
    for (; i < n; i++)
        printf("%d ", ram[i]);
}

int main()
{
    if (sc_memoryLoad("asd")) perror("((");
    return 0;
}
