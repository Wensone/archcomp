#include <memory.h>
#include "head/term.h"

int mt_clscr(){
    char clear[] = "\E[H\E[2J";
	write(STDOUT_FILENO, clear, strlen(clear));
	return EXIT_SUCCESS;
}

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize ws;

    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)){
        *rows = ws.ws_row;
        *cols = ws.ws_col;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int mt_gotoXY(int x, int y)
{
	int rows;
    int cols;
	if (mt_getscreensize(&rows, &cols)) {
		return EXIT_FAILURE;
	}

	if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
	   	char gotoxy[] = "\E[%d;%dH";
        if (sprintf(gotoxy, gotoxy, y, x) > 0) {
            if (write(STDOUT_FILENO, gotoxy, strlen(gotoxy)) == -1) {
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        };
	   	return EXIT_FAILURE;
 	}
	return EXIT_FAILURE;
}

int mt_setfgcolor(enum COLORS_TERM color){

    if(color < clr_black || color > clr_default){
        return EXIT_FAILURE;
    }

    char buf[15];
    sprintf(buf, "\E[3%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int mt_setbgcolor(enum COLORS_TERM color){
    if(color < clr_black || color > clr_default){
        return EXIT_FAILURE;
    }

    char buf[15];
    sprintf(buf, "\E[4%dm", color);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
