#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "head/basic.h"

#define REM 5
#define LET 6
#define ERR -1
#define REOP 18

char *asProg = NULL;
char memory[100];
int memNumb[100];
FILE *out = NULL;
int numLine = 0;
int wait = -1;
int numWait = -1;
long int jp;

int calculation(char *operation, int start, int end)
{
    int signs = 0;
    int prioritySigns = 0;
    char masSig[] = {'0', '0', '0', '0', '0'};
    int numbSig[] = {-1, -1, -1, -1, -1};
    int i = 0;
    int pos = 81;
    int posSum = 71;
    int *chiss = malloc(sizeof(int) * 100);
    for (i = 0; i < 100; ++i) {
        chiss[i] = -1;
    }

    for (pos = 81; pos <= 100; ++pos) {
        if (memory[pos] == '0') break;
    }

    for (i = start; i < end; ++i) {
        if (operation[i] == '*'
            || operation[i] == '/'
            || operation[i] == '+'
            || operation[i] == '-') {
            if (operation[i] == '*' || operation[i] == '/')
                prioritySigns++;
            masSig[signs] = operation[i];
            numbSig[signs] = i;
            signs++;
        }
    }
    int numSgs = signs;

    while (numSgs != 0) {

        for (i = 0; i < signs; ++i) {
            if (prioritySigns != 0) {
                if (masSig[i] == '*' || masSig[i] == '/') {
                    int pred = 0;
                    int fol = 0;
                    int k = 0;
                    int op = 0;
                    int cl = 0;
                    for (k = start; k < numbSig[i]; ++k) {
                        if (operation[k] == '(')
                            op++;
                        if (operation[k] == ')')
                            cl++;
                    }
                    if (op != cl) {
                        numSgs--;
                        continue;
                    }

                    for (k = 80; k < 100; ++k) {
                        if (memory[k] == operation[numbSig[i] - 1])
                            pred = k;
                        if (memory[k] == operation[numbSig[i] + 1])
                            fol = k;
                    }
                    if (operation[numbSig[i] - 1] == ')') {
                        pred = posSum;
                        posSum++;
                    }
                    if (operation[numbSig[i] + 1] == '(') {
                        fol = posSum;
                        posSum++;
                    }
                    if (operation[numbSig[i] - 1] == 'x') {
                        for (k = numbSig[i] - 1; k > start; --k) {
                            if (operation[k] != 'x') {
                                int r = operation[k] - '0';
                                r += (operation[k - 1] - '0') * 10;
                                pred = r;
                                break;
                            }
                        }
                    }
                    if (operation[numbSig[i] + 1] == 'x') {
                        for (k = numbSig[i] + 1; k < end; ++k) {
                            if (operation[k] != 'x') {
                                int r = (operation[k] - '0') * 10;
                                r += (operation[k + 1] - '0');
                                fol = r;
                                break;
                            }
                        }
                    }
                    if (operation[numbSig[i] - 1] >= '0' && operation[numbSig[i] - 1] <= '9') {
                        int r = 0;
                        for (k = numbSig[i] - 1; k >= start; --k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                        }
                        for (k++; k <= end; ++k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                            r = r * 10 + (operation[k] - '0');
                        }
                        if (chiss[r] != -1) {
                            pred = chiss[r];
                        } else {
                            for (k = 60; k < 100; ++k) {
                                if (memory[k] == '0') break;
                            }
                            fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                    (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                            chiss[r] = k;
                            pred = k;
                            memory[k] = 'q';
                        }

                    }
                    if (operation[numbSig[i] + 1] >= '0' && operation[numbSig[i] + 1] <= '9') {
                        int r = 0;
                        for (k = numbSig[i] + 1; k <= end; ++k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                            r = r * 10 + (operation[k] - '0');
                        }
                        if (chiss[r] != -1) {
                            fol = chiss[r];
                        } else {
                            for (k = 60; k < 100; ++k) {
                                if (memory[k] == '0') break;
                            }
                            fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                    (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                            chiss[r] = k;
                            fol = k;
                            memory[k] = 'q';
                        }
                    }
                    fprintf(out, "%c%c LOAD %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (pred / 10) + '0', (char) (pred % 10) + '0');
                    memory[numLine] = 'q';
                    numLine++;
                    if (masSig[i] == '*') {
                        fprintf(out, "%c%c MUL %c%c\n", (char) (numLine / 10) + '0',
                                (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                        memory[numLine] = 'q';
                        numLine++;
                    } else {
                        fprintf(out, "%c%c DIVIDE %c%c\n", (char) (numLine / 10) + '0',
                                (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                        memory[numLine] = 'q';
                        numLine++;
                    }
                    if (operation[numbSig[i] + 1] == '(') {
                        for (k = i + 1; k < signs; ++k) {
                            if (operation[numbSig[k] + 2] == ')')
                                break;
                        }
                        i = k;
                    }
                    while (masSig[i + 1] == '*' || masSig[i + 1] == '/') {
                        i++;
                        for (k = 80; k < 100; ++k) {
                            if (memory[k] == operation[numbSig[i] + 1])
                                fol = k;
                        }
                        if (operation[numbSig[i] + 1] == '(') {
                            fol = posSum;
                            posSum++;
                        }
                        if (operation[numbSig[i] + 1] >= '0' && operation[numbSig[i] + 1] <= '9') {
                            int r = 0;
                            for (k = numbSig[i] + 1; k <= end; ++k) {
                                if (operation[k] < '0' || operation[k] > '9') {
                                    break;
                                }
                                r = r * 10 + (operation[k] - '0');
                            }
                            if (chiss[r] != -1) {
                                fol = chiss[r];
                            } else {
                                for (k = 60; k < 100; ++k) {
                                    if (memory[k] == '0') break;
                                }
                                fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                        (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                                chiss[r] = k;
                                fol = k;
                                memory[k] = 'q';
                            }
                        }
                        if (operation[numbSig[i] + 1] == 'x') {
                            for (k = numbSig[i] + 1; k < end; ++k) {
                                if (operation[k] != 'x') {
                                    int r = (operation[k] - '0') * 10;
                                    r += (operation[k + 1] - '0');
                                    fol = r;
                                    break;
                                }
                            }
                        }
                        if (masSig[i] == '*') {
                            fprintf(out, "%c%c MUL %c%c\n", (char) (numLine / 10) + '0',
                                    (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                            memory[numLine] = 'q';
                            numLine++;
                        } else {
                            fprintf(out, "%c%c DIVIDE %c%c\n", (char) (numLine / 10) + '0',
                                    (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                            memory[numLine] = 'q';
                            numLine++;
                        }
                        prioritySigns--;
                        numSgs--;

                    }
                    fprintf(out, "%c%c STORE %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (pos / 10) + '0', (char) (pos % 10) + '0');
                    memory[numLine] = 'q';
                    numLine++;
                    prioritySigns--;
                    numSgs--;
                    pos++;
                    if (prioritySigns == 0) {
                        i = 0;
                        pos = 81;
                    }
                }
            } else {
                if (masSig[i] == '+' || masSig[i] == '-') {
                    int pred = 0;
                    int fol = 0;
                    int k = 0;
                    int op = 0;
                    int cl = 0;
                    for (k = start; k < numbSig[i]; ++k) {
                        if (operation[k] == '(')
                            op++;
                        if (operation[k] == ')')
                            cl++;
                    }
                    if (op != cl) {
                        numSgs--;
                        continue;
                    }
                    //printf("%c%c%c%c--------------------\n", operation[numbSig[i] - 2], operation[numbSig[i] - 1],
                      //     operation[numbSig[i]], operation[numbSig[i] + 1]);

                    for (k = 80; k < 100; ++k) {
                        if (memory[k] == operation[numbSig[i] - 1])
                            pred = k;
                        if (memory[k] == operation[numbSig[i] + 1])
                            fol = k;
                    }

                    if (operation[numbSig[i] - 1] == ')') {
                        pred = posSum;
                        posSum++;
                    }
                    if (operation[numbSig[i] + 1] == '(') {
                        fol = posSum;
                        posSum++;
                    }
                    if (operation[numbSig[i] - 1] == 'x') {
                        for (k = numbSig[i] - 1; k > start; --k) {
                            if (operation[k] != 'x') {
                                int r = operation[k] - '0';
                                r += (operation[k - 1] - '0') * 10;
                                pred = r;
                                break;
                            }
                        }
                    }
                    if (operation[numbSig[i] + 1] == 'x') {
                        for (k = numbSig[i] + 1; k < end; ++k) {
                            if (operation[k] != 'x') {
                                int r = (operation[k] - '0') * 10;
                                r += (operation[k + 1] - '0');
                                fol = r;
                                break;
                            }
                        }
                    }
                    if (operation[numbSig[i] - 1] >= '0' && operation[numbSig[i] - 1] <= '9') {
                        int r = 0;
                        for (k = numbSig[i] - 1; k >= start; --k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                        }
                        for (k++; k <= end; ++k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                            r = r * 10 + (operation[k] - '0');
                        }
                        if (chiss[r] != -1) {
                            pred = chiss[r];
                        } else {
                            for (k = 60; k < 100; ++k) {
                                if (memory[k] == '0') break;
                            }
                            fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                    (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                            chiss[r] = k;
                            pred = k;
                            memory[k] = 'q';
                        }

                    }
                    if (operation[numbSig[i] + 1] >= '0' && operation[numbSig[i] + 1] <= '9') {
                        int r = 0;
                        for (k = numbSig[i] + 1; k <= end; ++k) {
                            if (operation[k] < '0' || operation[k] > '9') {
                                break;
                            }
                            r = r * 10 + (operation[k] - '0');
                        }
                        if (chiss[r] != -1) {
                            fol = chiss[r];
                        } else {
                            for (k = 60; k < 100; ++k) {
                                if (memory[k] == '0') break;
                            }
                            fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                    (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                            chiss[r] = k;
                            fol = k;
                            memory[k] = 'q';
                        }
                    }
                    if (i - 1 >= 0) {
                        if (masSig[i - 1] == '*' || masSig[i - 1] == '/') {
                            pred = pos;
                            pos++;
                        }
                    }
                    if (i + 1 < 5) {
                        if (masSig[i + 1] == '*' || masSig[i + 1] == '/') {
                            fol = pos;
                            pos++;
                        }
                    }
                    fprintf(out, "%c%c LOAD %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (pred / 10) + '0', (char) (pred % 10) + '0');
                    memory[numLine] = 'q';
                    numLine++;
                    if (masSig[i] == '+') {
                        fprintf(out, "%c%c ADD %c%c\n", (char) (numLine / 10) + '0',
                                (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                        memory[numLine] = 'q';
                        numLine++;
                    } else {
                        fprintf(out, "%c%c SUB %c%c\n", (char) (numLine / 10) + '0',
                                (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                        memory[numLine] = 'q';
                        numLine++;
                    }
                    numSgs--;
                    if (operation[numbSig[i] + 1] == '(') {
                        for (k = i + 1; k < signs; ++k) {
                            if (operation[numbSig[k] + 2] == ')')
                                break;
                        }
                        i = k;
                    }
                    i++;

                    while (i < signs) {
                        if (masSig[i] == '+' || masSig[i] == '-') {
                            for (k = 80; k < 100; ++k) {
                                if (memory[k] == operation[numbSig[i] + 1])
                                    fol = k;
                            }
                            if (operation[numbSig[i] + 1] == '(') {
                                fol = posSum;
                                posSum++;
                            }
                            if (operation[numbSig[i] + 1] == 'x') {
                                for (k = numbSig[i] + 1; k < end; ++k) {
                                    if (operation[k] != 'x') {
                                        int r = (operation[k] - '0') * 10;
                                        r += (operation[k + 1] - '0');
                                        fol = r;
                                        break;
                                    }
                                }
                            }
                            if (operation[numbSig[i] + 1] >= '0' && operation[numbSig[i] + 1] <= '9') {
                                int r = 0;
                                for (k = numbSig[i] + 1; k <= end; ++k) {
                                    if (operation[k] < '0' || operation[k] > '9') {
                                        break;
                                    }
                                    r = r * 10 + (operation[k] - '0');
                                }
                                if (chiss[r] != -1) {
                                    fol = chiss[r];
                                } else {
                                    for (k = 60; k < 100; ++k) {
                                        if (memory[k] == '0') break;
                                    }
                                    fprintf(out, "%c%c = +%c%c\n", (char) (k / 10) + '0',
                                            (char) (k % 10) + '0', (char) (r / 10) + '0', (char) (r % 10) + '0');
                                    chiss[r] = k;
                                    fol = k;
                                    memory[k] = 'q';
                                }
                            }
                            if (i + 1 < 6) {
                                if (masSig[i + 1] == '*' || masSig[i + 1] == '/') {
                                    fol = pos;
                                    pos++;
                                }
                            }
                            if (masSig[i] == '+') {
                                fprintf(out, "%c%c ADD %c%c\n", (char) (numLine / 10) + '0',
                                        (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                                memory[numLine] = 'q';
                                numLine++;
                            } else {
                                fprintf(out, "%c%c SUB %c%c\n", (char) (numLine / 10) + '0',
                                        (char) (numLine % 10) + '0', (char) (fol / 10) + '0', (char) (fol % 10) + '0');
                                memory[numLine] = 'q';
                                numLine++;
                            }
                            numSgs--;
                        }
                        i++;
                    }
                }
            }
        }
    }
    int l = 0;

    for (l = start; l < end; ++l) {
        if (operation[l] == '=') {
            if (signs == 0) {
                int g = 0;

                for (g = 80; g < 100; g++) {
                    if (memory[g] == operation[l - 1]) {
                        break;
                    }
                }
                if (operation[l + 1] >= '0' && operation[l + 1] <= '9') {
                    fprintf(out, "%c%c = +%c%c\n", (char) (g / 10) + '0',
                            (char) (g % 10) + '0', operation[l + 1], operation[l + 2]);
                    return 0;
                } else {
                    int h = 0;

                    for (h = 80; h < 100; ++h) {
                        if (memory[h] == operation[l + 1]) {
                            break;
                        }
                    }
                    fprintf(out, "%c%c LOAD %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (h / 10) + '0', (char) (h % 10) + '0');
                    numLine++;
                    fprintf(out, "%c%c STORE %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (g / 10) + '0', (char) (g % 10) + '0');
                    numLine++;
                    return 0;
                }
            }

            int g = 0;

            for (g = 80; g < 100; g++) {
                if (memory[g] == operation[l - 1]) {
                    fprintf(out, "%c%c STORE %c%c\n", (char) (numLine / 10) + '0',
                            (char) (numLine % 10) + '0', (char) (g / 10) + '0', (char) (g % 10) + '0');
                    memory[numLine] = 'q';
                    numLine++;
                }
            }
            return 0;
        }
    }

    for (l = 71; l < 100; ++l) {
        if (memory[l] == '0') {
            posSum = l;
            memory[l] = 'q';
            break;
        }
    }
    fprintf(out, "%c%c STORE %c%c\n", (char) (numLine / 10) + '0',
            (char) (numLine % 10) + '0', (char) (posSum / 10) + '0', (char) (posSum % 10) + '0');
    memory[numLine] = 'q';
    numLine++;
    return posSum;
}

int determCommand(char *com)
{

    if (strcmp(com, "REM") == 0) {

        return REM;

    }

    if (strcmp(com, "INPUT") == 0) {

        return _READ;

    }

    if (strcmp(com, "OUTPUT") == 0) {

        return _WRITE;

    }

    if (strcmp(com, "GOTO") == 0) {

        return _JUMP;

    }

    if (strcmp(com, "IF") == 0) {

        return _JNEG;

    }

    if (strcmp(com, "LET") == 0) {

        return LET;

    }

    if (strcmp(com, "END") == 0) {

        return _HALT;

    }

    return ERR;

}

int _parsLine(char *line)
{

    int index = 0;

    int i = 0;

    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

        index = index * 10 + (line[i] - '0');

        ++i;

    }

    if (index == wait) {

        long int pos = ftell(out);

        fseek(out, jp, 0);

        fprintf(out, "%c%c JUMP %c%c\n", (char)(numWait / 10) + '0',

                (char)(numWait % 10) + '0', (char)(numLine / 10) + '0', (char)(numLine % 10) + '0');

        fseek(out, pos, 0);

        wait = -1;

        numWait = -1;

    }

    ++i;

    char com[10];

    int j = 0;

    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

        com[j] = line[i];

        ++j;

        ++i;

    }

    com[j] = '\0';

    ++i;

    j = 0;

    char *operation = NULL;

    char *comIf = NULL;

    char *opIf = NULL;

    if (strcmp(com, "END") != 0) {

        operation = malloc(sizeof(char) * 20);

        while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

            operation[j] = line[i];

            ++j;

            ++i;

        }

        operation[j] = '\0';

        ++i;

        if (strcmp(com, "IF") == 0) {

            comIf = malloc(sizeof(char) * 10);

            opIf = malloc(sizeof(char) * 20);

            j = 0;

            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

                comIf[j] = line[i];

                ++j;

                ++i;

            }

            ++i;

            comIf[j] = '\0';

            j = 0;

            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

                opIf[j] = line[i];

                ++j;

                ++i;

            }

            opIf[j] = '\0';

        }

    }

    int command = determCommand(com);

    if (command == ERR) {

        printf("ERROR: unknoun command\n");

        return -1;

    }

    switch (command) {

        case REM:

            break;

        case _READ:

            memNumb[numLine] = index;

            for (i = 91; i <= 100; ++i) {

                if (memory[i] == '0') {

                    memory[i] = operation[0];

                    break;

                }

            }

            fprintf(out, "%c%c READ %c%c\n", (char) (numLine / 10) + '0',

                    (char) (numLine % 10) + '0', (char) (i / 10) + '0', (char) (i % 10) + '0');

            memory[numLine] = 'q';

            numLine++;

            break;

        case _WRITE:

            memNumb[numLine] = index;

            for (i = 91; i <= 100; ++i) {

                if (memory[i] == operation[0]) {

                    break;

                }

            }

            fprintf(out, "%c%c WRITE %c%c\n", (char) (numLine / 10) + '0',

                    (char) (numLine % 10) + '0', (char) (i / 10) + '0', (char) (i % 10) + '0');

            memory[numLine] = 'q';

            numLine++;

            break;

        case _JUMP:

            memNumb[numLine] = index;

            i = 0;

            int n = 0;

            while (operation[i] != '\0') {

                n = n * 10 + (operation[i] - '0');

                ++i;

            }

            if (n > index) {

                jp = ftell(out);

                wait = n;

                fprintf(out, "00 JUMP 00\n");

                numWait = numLine;

                memory[numLine] = 'q';

                numLine++;

                break;

            }

            for (i = 0; i < 100; ++i) {

                if (memNumb[i] == n)

                    break;

            }

            fprintf(out, "%c%c JUMP %c%c\n", (char)(numLine / 10) + '0',

                    (char)(numLine % 10) + '0', (char)(i / 10) + '0', (char)(i % 10) + '0');

            memory[numLine] = 'q';

            numLine++;

            break;

        case _JNEG:

            memNumb[numLine] = index;

            int one = 0;

            int two = 0;

            for (i = 80; i < 100; ++i) {

                if (memory[i] == operation[0]) {

                    one = i;

                    break;

                }

            }

            if (operation[2] >= '0' && operation[2] <= '9') {

                for (i = 60; i < 100; ++i) {

                    if (memory[i] == '0') {

                        two = i;

                        break;

                    }

                }

                fprintf(out, "%c%c = +%c%c\n", (char) (two / 10) + '0',

                        (char) (two % 10) + '0', operation[2], operation[3]);

                memory[two] = 'q';

            } else {

                for (i = 80; i < 100; ++i) {

                    if (memory[i] == operation[2]) {

                        two = i;

                        break;

                    }

                }

            }

            if (operation[1] == '>') {

                fprintf(out, "%c%c LOAD %c%c\n", (char) (numLine / 10) + '0',

                        (char) (numLine % 10) + '0', (char) (two / 10) + '0', (char) (two % 10) + '0');

                memory[numLine] = 'q';

                numLine++;

                fprintf(out, "%c%c SUB %c%c\n", (char) (numLine / 10) + '0',

                        (char) (numLine % 10) + '0', (char) (one / 10) + '0', (char) (one % 10) + '0');

                memory[numLine] = 'q';

                numLine++;

            } else {

                fprintf(out, "%c%c LOAD %c%c\n", (char) (numLine / 10) + '0',

                        (char) (numLine % 10) + '0', (char) (one / 10) + '0', (char) (one % 10) + '0');

                memory[numLine] = 'q';

                numLine++;

                fprintf(out, "%c%c SUB %c%c\n", (char) (numLine / 10) + '0',

                        (char) (numLine % 10) + '0', (char) (two / 10) + '0', (char) (two % 10) + '0');

                memory[numLine] = 'q';

                numLine++;

            }

            int pos = 0;

            for (i = 40; i < 100; ++i) {

                if (memory[i] == '0') {

                    pos = i;

                    break;

                }

            }

            fprintf(out, "%c%c JNEG %c%c\n", (char) (numLine / 10) + '0',

                    (char) (numLine % 10) + '0', (char) (pos / 10) + '0', (char) (pos % 10) + '0');

            memory[numLine] = 'q';

            numLine++;

            int oldLine = numLine;

            numLine = pos;

            int q = 0;

            i = 0;

            while (q < 3) {

                if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {

                    q++;

                }

                i++;

            }

            line[i - 3] = (char) (index / 10) + '0';

            line[i - 2] = (char) (index % 10) + '0';

            int reop = _parsLine(line + i - 3);

            fprintf(out, "%c%c JUMP %c%c\n", (char) (numLine / 10) + '0',

                    (char) (numLine % 10) + '0', (char) (oldLine / 10) + '0', (char) (oldLine % 10) + '0');

            memory[oldLine] = 'q';

            memory[numLine] = 'q';

            numLine = oldLine;

            break;

        case LET:

            memNumb[numLine] = index;

            int f = 1;

            for (i = 50; i < 100; ++i) {

                if (memory[i] == operation[0])

                    f = 0;

            }

            if (f) {

                for (i = 91; i <= 100; ++i) {

                    if (memory[i] == '0') {

                        memory[i] = operation[0];

                        break;

                    }

                }

            }

            j = 0;

            int op = 0;

            int cl = 0;

            int NUMB_SCOB = 1;

            while (operation[j] != '\0') {

                if (operation[j] == '(')

                    NUMB_SCOB++;
                ++j;

            }

            int *scobOpen = malloc(sizeof(int) * NUMB_SCOB);

            int *scobClose = malloc(sizeof(int) * NUMB_SCOB);

            while (operation[j] != '\0') {

                if (operation[j] == '(') {

                    scobOpen[op] = j;

                    op++;

                }

                if (operation[j] == ')') {

                    scobClose[cl] = j;

                    cl++;

                }

                j++;

            }

            if (op != cl) {

                printf("ERROR: BREKITS");

                return -1;

            }

            int k = 0;

            int ps = 0;

            for (k = op - 1; k >= 0; --k) {

                ps = calculation(operation, scobOpen[k] + 1, scobClose[k] - 1);

                operation[scobOpen[k]] = 'x';

                operation[scobOpen[k] + 1] = (char) (ps / 10) + '0';

                operation[scobOpen[k] + 2] = (char) (ps % 10) + '0';

                for (i = scobOpen[k] + 3; i <= scobClose[k]; ++i) {

                    operation[i] = 'x';

                }

            }

            calculation(operation, 0, j - 1);

            break;

        case _HALT:

            fprintf(out, "%c%c HALT 00\n", (char) (numLine / 10) + '0',

                    (char) (numLine % 10) + '0');

            memory[numLine] = 'q';

            numLine++;

            break;

    }

    return 0;

}

int basic(int args, char *argv[])
{

    if (args < 3) {

        printf("Error: need more arguments\n");

        return -1;

    }

    int i = 0;

    for (i = 0; i < 100; ++i) {

        memory[i] = '0';

        memNumb[i] = 0;

    }

    char *fileNameIn = malloc(sizeof(char) * 20);

    char *fileNameOut = malloc(sizeof(char) * 20);

    asProg = malloc(sizeof(char) * 500);

    strcpy(fileNameIn, argv[1]);

    strcpy(fileNameOut, argv[2]);

    FILE *in = fopen(fileNameIn, "r");

    out = fopen(fileNameOut, "w+");

    if (in == NULL) {

        printf("ERROR: Can not open file\n");

    }

    char *buf = malloc(sizeof(char) * 50);

//int i = 0;

    while (!feof(in)) {

        fgets(buf, 50, in);

        int reop = _parsLine(buf);

        if (reop == REOP) {

            fclose(in);

            fopen(fileNameIn, "r");

        }

        if (reop == ERR) {

            return -1;

        }

    }

    fclose(in);

    fclose(out);

    return 0;

}