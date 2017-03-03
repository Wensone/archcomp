#ifndef ARCH_TERMINAL_H
#define ARCH_TERMINAL_H

#include "../lab1/SimpleComputer.h"
#include "../lab2/term.h"
#include "../lab3/graph.h"
#include "../lab4/rk.h"

uint32_t big[17 * 2];

int init_data();
int box_print();
int print_char(char x, uint8_t a, uint8_t b, enum COLORS_TERM fg, enum COLORS_TERM bg);
void memory_print(uint8_t, enum COLORS_TERM, enum COLORS_TERM);
int print_BC(uint32_t symb, enum COLORS_TERM fg, enum COLORS_TERM bg);

#endif //ARCH_TERMINAL_H
