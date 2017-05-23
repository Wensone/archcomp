#ifndef ARCH_TERMINAL_H
#define ARCH_TERMINAL_H

#include "../../lab1/head/SimpleComputer.h"
#include "../../lab2/head/term.h"
#include "../../lab3/head/graph.h"
#include "../../lab4/head/rk.h"
#include <signal.h>
#include <sys/time.h>
#include "basic.h"

struct itimerval nval;
struct {
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

int printOperation();

int changeAccum();

int changeCounter();

/* my space; DON'T TOUCH */

int IOcorrect(char *);

int checkData(char *);

int checkCom(char *);

/* my space; DON'T TOUCH */

void CU(int signo);

int ALU(int operand, int value);

void  sigReset(int signo);

char *readString();

int transl(char *com);

int READ(int v);

int WRITE(int v);

int LOAD(int v);

int STORE(int v);

int cADD(int v);

int SUB(int v);

int DIVIDE(int v);

int MUL(int v);

int JUMP(int v);

int JNEG(int v);

int JZ(int v);

int HALT(int v);

int NOT(int v);

int AND(int v);

int OR(int v);

int XOR(int v);

int JNS(int v);

int JC(int v);

int JNC(int v);

int JP(int v);

int JNP(int v);

int CHL(int v);

int SHR(int v);

#endif //ARCH_TERMINAL_H
