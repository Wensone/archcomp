#ifndef GRAPH_H
#define GRAPH_H

#include "../../lab2/head/term.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

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
    A9 = 18, AA = 20, AB = 22, AC = 24, AD = 26, AE = 28, AF = 30, APlus = 32, AM = 34, ADD = 36
};

int bc_printA(const char *);

int bc_box(int, int, int, int);

int bc_printbigchar(int *ch, int x, int y,
                    enum COLORS_TERM fg, enum COLORS_TERM bg);

int bc_setbigcharpos(int *, int, int, int);

int bc_getbigcharpos(int *, int, int, int *);

int bc_bigcharwrite(int, int *, int);

int bc_bigcharread(int, int *, int, int *);

#endif // GRAPH_H
