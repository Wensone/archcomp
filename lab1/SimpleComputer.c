#include "head/SimpleComputer.h"

int sc_memoryInit()
{
    memset(ram, 0, SIZE * sizeof(int));
    return EXIT_SUCCESS;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address >= SIZE)
        return EXIT_FAILURE;

    *(ram + address) = value;
    return EXIT_SUCCESS;
}

int sc_memoryGet(int address, int *value)
{
    if (address < 0 || address >= SIZE)
        return EXIT_FAILURE;

    *value = *(ram + address);

    return EXIT_SUCCESS;
}

int sc_memorySave(char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (!file) EXIT_FAILURE;

    fwrite(ram, sizeof(int), SIZE, file);

    fclose(file);
    return EXIT_SUCCESS;
}

int sc_memoryLoad(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file) return EXIT_FAILURE;

    fread(ram, sizeof(int), SIZE, file);

    fclose(file);
    return EXIT_SUCCESS;
}

int sc_regInit()
{
    Flags = 0x0;
    return EXIT_SUCCESS;
}

int sc_regSet(int reg, int value)
{
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
        (reg != FLAG_T) && (reg != FLAG_0)) {
        return EXIT_FAILURE;
    }
    if ((value < 0) || (value > 1)) {
        return EXIT_FAILURE;
    }

    if (value == 0) {
        Flags &= !reg;
    } else {
        Flags |= reg;
    }
    return EXIT_SUCCESS;
}

int sc_regGet(int reg, int *value)
{
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
        (reg != FLAG_T) && (reg != FLAG_0)) {
        return EXIT_FAILURE;
    }
    *value = (Flags & reg);
    //*value >>= (int)log2((double) reg);
    return EXIT_SUCCESS;
}

int sc_commandEncode(int command, int operand, int *value)
{
    if (command < 0 || command > 127 || operand < 0 || operand > 127) {
        return EXIT_FAILURE;
    }
    int temp = 0x00;
    temp |= command;
    temp <<= 7;
    temp |= operand;
    *value = temp;

    return EXIT_SUCCESS;
}

int sc_commandDecode(int value, int *command, int *operand)
{
    if (value >> 14 != 0x0) {
        return EXIT_FAILURE;
    }
    *command = (value >> 7);
    *operand = (value & 0177);
    return EXIT_SUCCESS;
}

int sc_setData(int Data, int *dest)
{
    if (abs(Data) >> 15 || abs(Data) >> 14 || abs(Data) > 0x3FFF) {
        return EXIT_FAILURE;
    }
    *dest = abs(Data);
    if (Data < 0) {
        *dest |= (1 << 15);
    }
    *dest |= (1 << 14);
    return EXIT_SUCCESS;
}

int sc_getData(int dest, int *Data)
{
    if (!((dest) >> 14)) {
        return EXIT_FAILURE;
    }

    *Data = dest;
    *Data &= ~(1 << 14);
    if ((dest) >> 15) {
        *Data &= ~(1 << 15); // инвертация в случае 1 на 16-м разряде
        *Data = ~(*Data) + 1;
    }
    return EXIT_SUCCESS;
}

int isData(int c)
{
    return (c >> 14);
}

int setAccum(int v)
{
    if (!isData(v)) return EXIT_FAILURE;
    accumulator = v;
    return EXIT_SUCCESS;
}

int getAccum()
{
    return accumulator;
}

int IncCount()
{
    if (counter == 99)
        return EXIT_FAILURE;
    ++counter;
    return EXIT_SUCCESS;
}

int zeroCount()
{
    counter = 0;
    return EXIT_SUCCESS;
}

int getCount()
{
    return counter;
}

int setCounter(int v)
{
    if (v < 0)
        return EXIT_FAILURE;
    counter = (unsigned int) v;
    return EXIT_SUCCESS;
}

