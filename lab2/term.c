#include "term.h"

uint8_t mt_clscr()
{
	printf("\E[H\E[2J");
	return SUCCES;
}

uint8_t mt_getscreensize(uint16_t *rows, uint16_t *cols)
{
	struct winsize ws;
	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
		*rows = (uint16_t) ws.ws_row;
		*col = (uint16_t) ws.ws_col;
		return SUCCES;
	}
	return ERROR_TERM;
}

uint8_t mt_gotoXY(int x, int y)
{
	uint8_t rows, cols;
	if (mt_getscreensize(&rows, &cols)) {
		return ERROR_TERM;
	}
	if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
	   	printf("\E[%d;%dH", y, x);
	   	return SUCCES;
 	}
	return ERROR_TERM;

}
