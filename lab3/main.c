#include "graph.h"

int main(){
    uint16_t x = -1, y = -1;
    if (mt_getscreensize(&y, &x)) return 21;
    //bc_printA("qqqqq\n");
    printf("[%d|%d]", x, y);
    if (bc_box(x / 4, y / 4, 20, 10)) return 22;
	uint32_t big[2];
	big[0] = 0x18242424;
    big[1] = 0x1C042418;
	bc_setbigcharpos(big, 0, 1, 1);
    bc_setbigcharpos(big, 1, 1, 1);
    bc_setbigcharpos(big, 2, 7, 1);
    bc_setbigcharpos(big, 3, 5, 1);
    bc_setbigcharpos(big, 3, 6, 1);
    bc_setbigcharpos(big, 3, 7, 1);
	bc_printbigchar(big, x / 4 + 1, y / 4 + 1, clr_cyan, clr_green);


    return 0;
}
