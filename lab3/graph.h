#ifndef GRAPH_H
#define GRAPH_H

#include "../lab2/term.h"
#include <string.h>

#define ACS_CKBOARD "a"
#define CHAR_DR "j"
#define CHAR_DL "m"
#define CHAR_TR "k"
#define CHAR_TL "l"
#define CHAR_VERT "x"
#define CHAR_HOR "q"

#define ENTER_ALT_MODE "\E(0"
#define EXIT_ALT_MODE "\E(B"

enum _ASCII {
    A0 = 0, A1 = 2, A2 = 4, A3 = 6, A4 = 8, A5 = 10, A6 = 12, A7 = 14, A8 = 16,
    A9 = 18, AA = 20, AB = 22, AC = 24, AD = 26, AE= 28, AF = 30, APlus = 32
};

enum ERROR_TERM bc_printA(const char*);
enum ERROR_TERM bc_box(uint16_t, uint16_t, uint16_t, uint16_t);
enum ERROR_TERM bc_printbigchar(uint32_t* ch, uint16_t x, uint16_t y,
	 					enum COLORS_TERM fg, enum COLORS_TERM bg);
enum ERROR_TERM bc_setbigcharpos(uint32_t*, uint8_t, uint8_t, uint8_t);
enum ERROR_TERM bc_getbigcharpos(uint32_t*, uint8_t, uint8_t, uint8_t*);
enum ERROR_TERM bc_bigcharwrite(int, uint32_t*, int);
enum ERROR_TERM bc_bigcharread(int, uint32_t*, int, int*);

#endif // GRAPH_H
