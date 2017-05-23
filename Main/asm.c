#include "head/asm.h"


int parsLine(char *line)
{

    //sc_memoryInit();

    int index = 0;

    int command = 0;

    int operand = 0;

    int value = 0;

    int i = 0;

    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0') {

        index = index * 10 + (line[i] - '0');

        ++i;

    }

    ++i;

    char com[10];

    int j = 0;

    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0') {

        com[j] = line[i];

        ++j;

        ++i;

    }

    com[j] = '\0';

    ++i;

    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0') {

        if (line[i] != '+')

            operand = operand * 10 + (line[i] - '0');

        ++i;

    }

    if (strcmp(com, "READ") == 0) {

        command = 0x10;

    }

    if (strcmp(com, "WRITE") == 0) {

        command = 0x11;

    }

    if (strcmp(com, "LOAD") == 0) {

        command = 0x20;

    }

    if (strcmp(com, "STORE") == 0) {

        command = 0x21;

    }

    if (strcmp(com, "ADD") == 0) {

        command = 0x30;

    }

    if (strcmp(com, "SUB") == 0) {

        command = 0x31;

    }

    if (strcmp(com, "DIVIDE") == 0) {

        command = 0x32;

    }

    if (strcmp(com, "MUL") == 0) {

        command = 0x33;

    }

    if (strcmp(com, "JUMP") == 0) {

        command = 0x40;

    }

    if (strcmp(com, "JNEG") == 0) {

        command = 0x41;

    }

    if (strcmp(com, "JZ") == 0) {

        command = 0x42;

    }

    if (strcmp(com, "HALT") == 0) {

        command = 0x43;

    }

    if (strcmp(com, "=") == 0) {

        command = 0x0;
        sc_setData(operand, &operand);

        ram[index] = operand;

        return 0;

    }

    int e = sc_commandEncode(command, operand, &value);

    if (e == -1) {

        printf("ERROR\n");

        return -1;

    }

    ram[index] = value;

    return 0;

}

int asembler(int args, char *argv[])
{

    sc_memoryInit();

    char *fileNameIn = malloc(sizeof(char) * 20);

    char *fileNameOut = malloc(sizeof(char) * 20);

    if (args < 3) {

        printf("Error: need more arguments\n");

        return -1;

    }

    strcpy(fileNameIn, argv[1]);

    strcpy(fileNameOut, argv[2]);

    FILE *in = fopen(fileNameIn, "r");

    char buf[50];

    int f = 0;

    while (!feof(in)) {

        int i = 0;

        for (i = 0;; ++i) {

            buf[i] = fgetc(in);

            if (feof(in)) {

                f = 1;

                break;

            }

            if (buf[i] == '\n') {

                buf[i] = '\0';

                break;

            }

        }

        if (!f) {

            parsLine(buf);

        }

    }

    sc_memorySave(fileNameOut);

    fclose(in);

    return 0;

}
