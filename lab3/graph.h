#ifndef GRAPH_H
#define GRAPH_H

#include "../lab2/term.h"
#include <string.h>

#define ACS_CKBOARD 'a'
#define CHAR_DR "j"
#define CHAR_DL "m"
#define CHAR_TR "k"
#define CHAR_TL "l"
#define CHAR_VERT "x"
#define CHAR_HOR "q"

#define ENTER_ALT_MODE "\E(0"
#define EXIT_ALT_MODE "\E(B"

uint8_t bc_printA(const char*);
uint8_t bc_box(uint16_t, uint16_t, uint16_t, uint16_t);
uint8_t bc_printbigchar(uint32_t* ch, uint16_t x, uint16_t y,
	 					enum COLORS_TERM fg, enum COLORS_TERM bg);
uint8_t bc_setbigcharpos(uint32_t*, uint8_t, uint8_t, uint8_t);
uint8_t bc_getbigcharpos(uint32_t*, uint8_t, uint8_t, uint8_t*);
uint8_t bc_bigcharwrite(int, uint32_t*, int);
uint8_t bc_bigcharread(int, uint32_t*, int, int*);

#endif // GRAPH_H
