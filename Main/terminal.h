#ifndef ARCH_TERMINAL_H
#define ARCH_TERMINAL_H

#include "../lab1/SimpleComputer.h"
#include "../lab2/term.h"
#include "../lab3/graph.h"
#include "../lab4/rk.h"

struct coord {
    uint8_t x;
    uint8_t y;
}xy;

uint32_t big[17 * 2];

int init_data();
int box_print();
int print_char(char x, uint8_t a, uint8_t b, enum COLORS_TERM fg, enum COLORS_TERM bg);
void memory_print(uint8_t, enum COLORS_TERM, enum COLORS_TERM);
int print_BC(uint16_t symb, enum COLORS_TERM fg, enum COLORS_TERM bg);
uint8_t readInt(int size, uint8_t *oper, uint16_t *val);
void move(KEYS);
uint8_t inp();

#endif //ARCH_TERMINAL_H
