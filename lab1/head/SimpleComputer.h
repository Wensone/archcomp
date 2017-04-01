#ifndef simplcomp_h
#define simplcomp_h

/*|15|14|13|12|11|10|9|8|7|6|5|4|3|2|1|0
 *|+/-|data/command|...*/

#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 100
/*ETM0P*/
#define FLAG_P 0x1
#define FLAG_0 0x2
#define FLAG_M 0x4
#define FLAG_T 0x8
#define FLAG_E 0x10

int ram[SIZE];
int Flags;
unsigned int counter;
int accumulator;


int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);
int sc_setData(int, int*);
int sc_getData(int, int*);
int isData(int c);
int setAccum(int v);
int getAccum();
int IncCount();
int getCount();
int zeroCount();
int setCounter(int v);

#endif // simplcomp_h
