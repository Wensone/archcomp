#ifndef ARCH_ASM_H
#define ARCH_ASM_H

#include <stdio.h>
#include <string.h>

#include "../../lab1/head/SimpleComputer.h"

#define ERR_ARG1 -1
#define ERR_ARG2 -2
#define ERR_ARG3 -3
#define ERR_FEW -4
#define ERR_MANY -5
#define EMPTY_STR 1

int str2sc_word(char *str, int *value);

int str2command(char *str);

int pars_line(char *str, int *addr, int *value);

void print_error(char *line, int line_cnt, int err);

int test_argv_(char *argv[]);

int asembler(int argc, char *argv[]);

#endif //ARCH_ASM_H
