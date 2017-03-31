#include "head/term.h"

int main()
{
	mt_setbgcolor(clr_blue);
	printf("LOL\n");
    mt_setbgcolor(clr_default);
    uint16_t y, x;
    mt_getscreensize(&y, &x);
    mt_gotoXY((uint16_t) (x / 2), (uint16_t) (y / 2));
    return 0;
}
