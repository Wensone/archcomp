#ifndef ARCH_TERMINAL_H
#define ARCH_TERMINAL_H

#include "../lab1/head/SimpleComputer.h"
#include "../lab2/head/term.h"
#include "../lab3/head/graph.h"
#include "../lab4/head/rk.h"

struct coord {
    int x;
    int y;
} xy;

int big[19 * 2];
char *qIO[5];

int init_data();

int box_print();

int print_char(char x, int a, int b, enum COLORS_TERM fg, enum COLORS_TERM bg);

int memory_print(int, enum COLORS_TERM, enum COLORS_TERM);

int print_BC(int symb, enum COLORS_TERM fg, enum COLORS_TERM bg);

int readInt(int size, int *val);

int move(KEYS);

int inp();

int printAccum();

int printCount();

int printFLAGS();

int q_add(char *message);

void q_free();

int printIO();


/* my space; DON'T TOUCH */

int IOcorrect(char *);

int checkData(char *);

int checkCom(char *);

/* my space; DON'T TOUCH */

#endif //ARCH_TERMINAL_H
