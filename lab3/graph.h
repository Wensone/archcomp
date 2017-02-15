#ifndef GRAPH_H
#define GRAPH_H

#include "../lab2/term.h"

#define CHAR_BOX "a" //BOXCHAR_REC "a"
#define CHAR_DR "j"//BOXCHAR_BR "j"
#define CHAR_DL "m"//BOXCHAR_BL "m"
#define CHAR_TR "k"//BOXCHAR_TR "k"
#define CHAR_TL "l"
#define CHAR_VERT "x"
#define CHAR_HOR "q"

uint8_t bc_printA(const char*);
uint8_t bc_box(uint16_t, uint16_t, uint16_t, uint16_t);
uint8_t bc_printbigchar(int*, int, int, enum COLORS_TERM, enum COLORS_TERM);
uint8_t bc_setbigcharpos(int*, int, int, int );
uint8_t bc_getbigcharpos(int*, int, int, int*);
uint8_t bc_bigcharwrite(int, int*, int);
uint8_t bc_bigcharread(int, int*, int, int*);

#endif // GRAPH_H
