#include "term.h"

uint8_t mt_clscr(){
	printf("\E[H\E[2J");
	return SUCCESS;
}

uint8_t mt_getscreensize(uint16_t *rows, uint16_t *cols)
{
    struct winsize ws;

    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)){
        *rows = ws.ws_row;
        *cols = ws.ws_col;

        return SUCCESS;
    }

    return ERROR;
}

uint8_t mt_gotoXY(int x, int y)
{
	uint8_t rows;
    uint8_t cols;
	if (mt_getscreensize(&rows, &cols)) {
		return ERROR;
	}
	if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
	   	printf("\E[%d;%dH", y, x);
	   	return SUCCESS;
 	}
	return ERROR;
}

uint8_t mt_setfgcolor(COLORS_TERM color){
    printf("\E[3%dm");
    if(color < clr_black || color > clr_default){
        return ERROR;
    }

    return SUCCESS;
}

uint8_t mt_setbgcolor(COLORS_TERM color){
    printf("\E[4%dm", color);
    if(color < clr_black || color > clr_default){
        return ERROR;
    }

    return SUCCESS;
}
