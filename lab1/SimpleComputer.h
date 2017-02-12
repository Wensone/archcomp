#ifndef simplcomp_h
#define simplcomp_h

#include <stdio.h>
#include <memory.h>
#include <math.h>

#define sizeArray 100

#define FLAG_P 0x1
#define FLAG_0 0x2
#define FLAG_M 0x4
#define FLAG_T 0x8
#define FLAG_E 0x10

int scmemory[sizeArray];
int Flags;

enum FLAGS{
	COMMAND_ERROR = -3,
	FILE_ERROR = -2,
	INCORRECT_MEMORY = -1,
	SUCCESS = 0
};

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

#endif // simplcomp_h
