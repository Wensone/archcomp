#ifndef simplcomp_h
#define simplcomp_h

#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>

#define SIZE 100

#define FLAG_P 0x1
#define FLAG_0 0x2
#define FLAG_M 0x4
#define FLAG_T 0x8
#define FLAG_E 0x10

uint16_t ram[SIZE];
uint16_t Flags;

enum ERROR_SC{
	COMMAND_ERROR = -3,
	FILE_ERROR = -2,
	INCORRECT_MEMORY = -1,
	SUCCESS = 0
};

uint8_t sc_memoryInit();
uint8_t sc_memorySet(uint8_t, uint16_t);
uint8_t sc_memoryGet(uint8_t, uint16_t*);
uint8_t sc_memorySave(char*);
uint8_t sc_memoryLoad(char*);
uint8_t sc_regInit();
uint8_t sc_regSet(uint8_t, uint8_t);
uint8_t sc_regGet(uint8_t, uint8_t*);
uint8_t sc_commandEncode(uint8_t, uint8_t, uint16_t*);
uint8_t sc_commandDecode(uint16_t, uint8_t*, uint8_t*);

#endif // simplcomp_h
