#include "head/asm.h"


int memory[100];

void memoryInit() {

    int i = 0;

    for (i = 0; i < 100; ++i) {

        memory[i] = 0;

    }

}

int memoryWrite(char *filename) {

    FILE *out = fopen(filename, "wb");

    if (out == NULL)

        return 1;

    fwrite(memory, sizeof(int), 100, out);

    fclose(out);

    return 0;

}


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

        command = 10;

    }

    if (strcmp(com, "WRITE") == 0) {

        command = 11;

    }

    if (strcmp(com, "LOAD") == 0) {

        command = 20;

    }

    if (strcmp(com, "STORE") == 0) {

        command = 21;

    }

    if (strcmp(com, "ADD") == 0) {

        command = 30;

    }

    if (strcmp(com, "SUB") == 0) {

        command = 31;

    }

    if (strcmp(com, "DIVIDE") == 0) {

        command = 32;

    }

    if (strcmp(com, "MUL") == 0) {

        command = 33;

    }

    if (strcmp(com, "JUMP") == 0) {

        command = 40;

    }

    if (strcmp(com, "JNEG") == 0) {

        command = 41;

    }

    if (strcmp(com, "JZ") == 0) {

        command = 42;

    }

    if (strcmp(com, "HALT") == 0) {

        command = 43;

    }

    if (strcmp(com, "=") == 0) {

        command = 0;

        memory[index - 1] = operand;

        return 0;

    }

    int e = sc_commandEncode(command, operand, &value);

    if (e == -1) {

        printf("ERROR\n");

        return -1;

    }

    memory[index - 1] = value;

    return 0;

}

int main(int args, char *argv[])
{

    //memoryInit();

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

    memoryWrite(fileNameOut);

    fclose(in);

    return 0;

}
