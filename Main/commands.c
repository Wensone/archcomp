#include "head/commands.h"

int ALU(int command, int operand)
{
    int tmp;

    switch (command) {
        case 0x30: /* ADD */
            accumulator += sc_memory[operand];
            break;

        case 0x31: /* SUB */
            if (((sc_memory[operand] >> 14) & 1) == 1)
                tmp = sc_memory[operand] | (~0x7FFF);
            else
                tmp = sc_memory[operand];
            accumulator -= tmp;
            if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
                accumulator &= 0x7FFF;
            }
            break;

        case 0x33: /* MUL */
            accumulator *= sc_memory[operand];
            break;

        case 0x32: /* DIV */
            if (sc_memory[operand] != 0)
                accumulator /= sc_memory[operand];
            else {
                sc_regSet(FLAG_DIVISION, 1);
                return -1;
            }
            break;
    }
    if ((accumulator & 1) == 0)
        sc_regSet(FLAG_ODD, 0);
    else
        sc_regSet(FLAG_ODD, 1);
    if ((accumulator > 0x7FFF) || (accumulator < 0)) {
        accumulator &= 0x7FFF;
        sc_regSet(FLAG_OVERFLOW, 1);
    }
    else
        sc_regSet(FLAG_OVERFLOW, 0);
    sc_regSet(FLAG_ODD, accumulator & 1);
    return 0;
}

void CU()
{
    int command, operand;
    int flag, read_suc;

    if (inst_counter >= MEMSIZE) {
        sc_regSet(FLAG_OUTMEM, 1);
        sc_regSet(FLAG_INTERRUPT, 1);
        return;
    }
    if (sc_commandDecode(sc_memory[inst_counter], &command, &operand) != 0) {
        sc_regSet(FLAG_COMMAND, 1);
        sc_regSet(FLAG_INTERRUPT, 1);
        return;
    }
    if ((operand < 0) && (operand >= MEMSIZE)) {
        sc_regSet(FLAG_COMMAND, 1);
        sc_regSet(FLAG_INTERRUPT, 1);
        return;
    }
    if ((command >= 0x30) && (command <= 0x33)) {
        if (ALU(command, operand) != 0)
            sc_regSet(FLAG_INTERRUPT, 1);
    }
    else {
        switch (command) {
            case 0x10: /* READ */
                do {
                    read_suc = read_mcell(operand);
                } while(read_suc != 0);
                break;

            case 0x11: /* WRITE */
                write_used = 1;
                write_val = sc_memory[operand];
                break;

            case 0x20: /* LOAD */
                accumulator = sc_memory[operand];
                break;

            case 0x21: /* STORE */
                sc_memory[operand] = accumulator;
                break;

            case 0x40: /* JUMP */
                inst_counter = operand - 1;
                break;

            case 0x41: /* JNEG */
                if (((accumulator >> 14) & 1) == 1)
                    inst_counter = operand - 1;
                break;

            case 0x42: /* JZ */
                if (accumulator == 0)
                    inst_counter = operand - 1;
                break;

            case 0x43: /* HALT */
                sc_regSet(FLAG_INTERRUPT, 1);
                break;

            case 0x59: /* JNP */
                sc_regGet(FLAG_ODD, &flag);
                if (flag == 1)
                    inst_counter = operand - 1;
                break;
        }
    }
}