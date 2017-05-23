#ifndef COMPUTER_BASIC
#define COMPUTER_BASIC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rpn.h"
#include "asm.h"

struct b_label {
	int label;
	int pos;
};

struct memory_t {
	int is_val;
	int command;
	int operand;
};

enum keywords {
	KEYW_REM = 1,
	KEYW_INPUT = 2,
	KEYW_OUTPUT = 3,
	KEYW_GOTO = 4,
	KEYW_IF = 5,
	KEYW_LET = 6,
	KEYW_END = 7,
	KEYW_PRINT = 8,
	KEYW_E = -1
};

enum code_command {
    _READ = 0x10,
    _WRITE = 0x11,
    _LOAD = 0x20,
    _STORE = 0x21,
    _ADD = 0x30,
    _SUB = 0x31,
    _DIVIDE = 0x32,
    _MUL = 0x33,
    _JUMP = 0x40,
    _JNEG = 0x41,
    _JZ = 0x42,
    _HALT = 0x43,
    _NOT = 0x51,
    _AND = 0x52,
    _OR = 0x53,
    _XOR = 0x54,
    _JNS = 0x55,
    _JC = 0x56,
    _JNC = 0x57,
    _JP = 0x58,
    _JNP = 0x59,
    _CHL = 0x60,
    _SHR = 0x61
};

int basic(int argc, char *argv[]);

int parse_line(char *str, int key_w);

void rpn_pars(char *rpn, int val);

int get_cache_addr(int n);

void add_code(int command, int operand);

int add_const(int n);

int get_var_addr(char c);

int is_value(char *str);

int srt_is_empty(char *str);

char *cpy_token(char *token, char *str);

int is_delim(char c);

int get_keyword_code(char *str);

char *get_label_and_keyw(char *str, int *label, char *keyword);

int find_label(int label);

void saveAsm(FILE *file);


#endif