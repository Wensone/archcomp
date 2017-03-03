#ifndef TERM_H
#define TERM_H

#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum ERROR_TERM {
	ERROR_TERM = -1,
	SUCCESS_TERM = 0
};

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

uint8_t mt_clscr();
uint8_t mt_gotoXY(uint16_t, uint16_t);
uint8_t mt_getscreensize(uint16_t *, uint16_t *);
uint8_t mt_setfgcolor(enum COLORS_TERM);
uint8_t	mt_setbgcolor(enum COLORS_TERM);

#endif // TERM_H
