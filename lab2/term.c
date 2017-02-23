#include <memory.h>
#include "term.h"

uint8_t mt_clscr(){
    char clear[] = "\E[H\E[2J";
	write(STDOUT_FILENO, clear, strlen(clear));
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

uint8_t mt_gotoXY(uint16_t x, uint16_t y)
{
	uint16_t rows;
    uint16_t cols;
	if (mt_getscreensize(&rows, &cols)) {
		return ERROR;
	}

	if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
	   	char gotoxy[] = "\E[%d;%dH";
        if (sprintf(gotoxy, gotoxy, y, x) > 0) {
            if (write(STDOUT_FILENO, gotoxy, strlen(gotoxy)) == -1) {
                return ERROR;
            }
            return SUCCESS;
        };
	   	return ERROR;
 	}
	return ERROR;
}

uint8_t mt_setfgcolor(enum COLORS_TERM color){

    if(color < clr_black || color > clr_default){
        return ERROR;
    }

    char buf[15];
    sprintf(buf, "\E[3%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1)
        return ERROR;
    return SUCCESS;
}

uint8_t mt_setbgcolor(enum COLORS_TERM color){
    if(color < clr_black || color > clr_default){
        return ERROR;
    }

    char buf[15];
    sprintf(buf, "\E[4%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1)
        return ERROR;

    return SUCCESS;
}
