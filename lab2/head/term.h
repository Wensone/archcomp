#ifndef TERM_H
#define TERM_H

#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

enum COLORS_TERM {
	clr_black,
	clr_red,
	clr_green,
	clr_brown,
	clr_blue,
	clr_magenta,
	clr_cyan,
	clr_light_blue,
	clr_default = 9
};

int mt_clscr();
int mt_gotoXY(int, int);
int mt_getscreensize(int *, int *);
int mt_setfgcolor(enum COLORS_TERM);
int	mt_setbgcolor(enum COLORS_TERM);

#endif // TERM_H
