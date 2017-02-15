#include "graph.h"

int main(){
    uint16_t x = -1, y = -1;
    if (mt_getscreensize(&y, &x)) return 21;
    //bc_printA("qqqqq\n");
    printf("[%d|%d]", x, y);
    if (bc_box(x / 4, y / 4, 20, 10)) return 22;

    return 0;
}
