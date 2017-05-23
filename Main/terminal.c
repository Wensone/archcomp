#include "head/terminal.h"

int box_print()
{
    if (mt_clscr()) return EXIT_FAILURE;

    if (bc_box(1, 1, 70, 12)) return EXIT_FAILURE;
    if (mt_gotoXY(30, 1)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Memory", 6) < 0) return EXIT_FAILURE;

    if (bc_box(72, 1, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(77, 1)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Accumulator", 11) < 0) return EXIT_FAILURE;

    if (bc_box(72, 4, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(73, 4)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "InstructionCounter", 18) < 0) return EXIT_FAILURE;

    if (bc_box(72, 7, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(77, 7)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Operation", 9) < 0) return EXIT_FAILURE;

    if (bc_box(72, 10, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(79, 10)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Flags", 5) < 0) return EXIT_FAILURE;

    if (bc_box(1, 13, 46, 10)) return EXIT_FAILURE; // big chars


    if (bc_box(47, 13, 45, 10)) return EXIT_FAILURE;
    if (mt_gotoXY(49, 13)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Keys", 4) < 0) return EXIT_FAILURE;

    if (mt_gotoXY(48, 14)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "l - load", 8) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 15)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "s - save", 8) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 16)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "r - run", 7) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 17)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "t - step", 8) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 18)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "i - reset", 9) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 19)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "F5 - accumulator", 16) < 0) return EXIT_FAILURE;
    if (mt_gotoXY(48, 20)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "F6 - InstructionCounter", 23) < 0) return EXIT_FAILURE;

    if (mt_gotoXY(1, 23)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Input\\Output:", 14) < 0) return EXIT_FAILURE;

    if (mt_gotoXY(30, 15)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int print_char(char x, int a, int b, enum COLORS_TERM fg, enum COLORS_TERM bg)
{
    switch (x) {
        case ('0'): {
            if (bc_printbigchar(big + A0, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('1'): {
            if (bc_printbigchar(big + A1, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('2'): {
            if (bc_printbigchar(big + A2, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('3'): {
            if (bc_printbigchar(big + A3, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('4'): {
            if (bc_printbigchar(big + A4, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('5'): {
            if (bc_printbigchar(big + A5, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('6'): {
            if (bc_printbigchar(big + A6, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('7'): {
            if (bc_printbigchar(big + A7, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('8'): {
            if (bc_printbigchar(big + A8, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('9'): {
            if (bc_printbigchar(big + A9, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('A'): {
            if (bc_printbigchar(big + AA, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('B'): {
            if (bc_printbigchar(big + AB, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('C'): {
            if (bc_printbigchar(big + AC, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('D'): {
            if (bc_printbigchar(big + AD, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('E'): {
            if (bc_printbigchar(big + AE, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ('F'): {
            if (bc_printbigchar(big + AF, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case '+': {
            if (bc_printbigchar(big + APlus, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case '\0': {
            if (bc_printbigchar(big + A0, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case ':': {
            if (bc_printbigchar(big + ADD, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        case '-': {
            if (bc_printbigchar(big + AM, a, b, fg, bg)) return EXIT_FAILURE;
            break;
        }
        default:
            if (mt_clscr()) return EXIT_FAILURE;
            fprintf(stderr, "Incorrect char[%d]\n", x);
            rk_mytermstore();
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int memory_print(int cur, enum COLORS_TERM fg, enum COLORS_TERM bg)
{
    if (printAccum()) return EXIT_FAILURE;
    if (printCount()) return EXIT_FAILURE;
    if (printFLAGS()) return EXIT_FAILURE;
    int i, x, y;
    int data;

    x = 2;
    y = 2;
    char buf[] = {0, 0, 0, 0, 0, 0, 0};
    for (i = 0; i < 100; i++) {
        if (mt_gotoXY(x, y)) return EXIT_FAILURE;
        y++;
        if (sc_memoryGet(i, &data)) return EXIT_FAILURE;
        if (isData(data)) {
            sprintf(buf, "%05X", data);
        } else {
            sprintf(buf, "+%04X", data);
        }

        if ((cur) == i || i == counter) {
            if (i == cur) {
                if (mt_setfgcolor(fg)) return EXIT_FAILURE;
                if (mt_setbgcolor(bg)) return EXIT_FAILURE;
            } else if (i == counter) {
                if (mt_setfgcolor(clr_black)) return EXIT_FAILURE;
                if (mt_setbgcolor(clr_blue)) return EXIT_FAILURE;
            }

            if (write(STDOUT_FILENO, buf, strlen(buf)) < 0) return EXIT_FAILURE;

            if (mt_setfgcolor(clr_default)) return EXIT_FAILURE;
            if (mt_setbgcolor(clr_default)) return EXIT_FAILURE;
            if (x != 65) {
                if (write(STDOUT_FILENO, "  ", 2) < 0) return EXIT_FAILURE;
            }
            if (cur == i)
                if (print_BC(data, clr_cyan, clr_black)) return EXIT_FAILURE;
            printOperation();
        } else {
            if (write(STDOUT_FILENO, buf, strlen(buf)) < 0) return EXIT_FAILURE;
            if (x != 65) {
                if (write(STDOUT_FILENO, "  ", 2) < 0) return EXIT_FAILURE;
            }
        }
        if (((i + 1) % 10) == 0) {
            x += 7;
            y = 2;
        }
    }
    printAccum();
    return EXIT_SUCCESS;
}

int init_data()
{

    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 80000;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 80000;

    signal(SIGUSR1, sigReset);
    signal(SIGALRM, CU);
    setitimer(ITIMER_REAL, &nval, NULL);

    int fd = open("../lab3/BIG_CHARS", O_RDONLY);
    if (fd == -1) {
        if (mt_clscr()) return EXIT_FAILURE;
        fprintf(stderr, "Read Big_Chars\n");
        return EXIT_FAILURE;
    }
    int count;
    if (bc_bigcharread(fd, big, 19, &count)) {
        fprintf(stderr, "Bad read BigChars\n");
        return EXIT_FAILURE;
    }
    if (count != 19) exit(22);
    xy.x = 0;
    xy.y = 0;

    zeroCount();
    if (sc_setData(0, &accumulator)) return EXIT_FAILURE;
    if (sc_regInit()) return EXIT_FAILURE;
    if (sc_memoryInit()) return EXIT_FAILURE;

    if (rk_mytermsave()) return EXIT_FAILURE;
    if (rk_mytermregime(0, 0, 1, 0, 1)) return EXIT_FAILURE;

    memset(qIO, 0x0, 5);
    sc_regSet(FLAG_T, 1);

    return EXIT_SUCCESS;
}

int print_BC(int symb, enum COLORS_TERM fg, enum COLORS_TERM bg)
{
    int x = 2,
            y = 14;
    char hex[6];
    memset(hex, 0, 6);
    if (isData(symb)) {
        if (sc_getData(symb, &symb)) return EXIT_FAILURE;
        sprintf(hex, "%05X", abs(symb));
        if (symb < 0) hex[0] = '-';
    } else {
        int oper, val;
        if (sc_commandDecode(symb, &oper, &val)) return EXIT_FAILURE;
        sprintf(hex, "%02X:%02X", oper, val);
    }
    for (int i = 0; i < 5; i++) {
        if (print_char(hex[i], x, y, fg, bg)) {
            fprintf(stderr, "Bad print %d | %s\n", i, hex);
            exit(1);
        }
        x += 9;
    }
    return EXIT_SUCCESS;
}

int move(KEYS key)
{
    switch (key) {
        case (key_up) : {
            if (xy.x == 0 && xy.y == 0) break;
            if (xy.x == 0) {
                xy.x = 9;
                xy.y--;
            } else {
                xy.x--;
            }
            break;
        }
        case (key_down) : {
            if (xy.x == 9 && xy.y == 9) break;
            if (xy.x == 9) {
                xy.x = 0;
                xy.y++;
            } else {
                xy.x++;
            }
            break;
        }
        case (key_left) : {
            if (xy.y == 0) break;
            xy.y--;
            break;
        }
        case (key_right) : {
            if (xy.y == 9) break;
            xy.y++;
            break;
        }
        default : {
            break;
        }
    }
    if (memory_print((xy.x + (xy.y * 10)), clr_brown, clr_red)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int readInt(int size, int *val)
{
    char buff[64 + size];
    memset(buff, 0, (size_t) (64 + size));
    int t = 0;

    for (int i = 0; i < (size + 64); i++) {
        read(STDIN_FILENO, (buff + i), 1);

        if (buff[i] == ':') t = i;

        if (buff[i] == '\n') {
            buff[i] = '\0';
            break;
        }

    }

    if (IOcorrect(buff)) {
        char err[256];
        sprintf(err, "Error read : %s", buff);
        if (q_add(err)) exit(11);
        return EXIT_FAILURE;
    }
    int operation, value;
    if (t) {
        buff[t] = '\0';

        sscanf(buff, "%X", &(operation));
        sscanf((buff + t + 1), "%X", &(value));
        buff[t] = ':';

        if (sc_commandEncode(operation, value, val)) {
            char err[256];
            sprintf(err, "Error read[c] : %s", buff);
            if (q_add(err)) exit(11);
            return EXIT_FAILURE;
        }
    } else {
        sscanf(buff, "%d", val);
        if (sc_setData((*val), val)) {
            char err[256];
            sprintf(err, "Error read[d] : %s", buff);
            if (q_add(err)) exit(11);
            return EXIT_FAILURE;
        }
    }

    char *io = malloc(9 + strlen(buff));
    strcpy(io, "Write : ");
    strcat(io, buff);
    if (q_add(io)) exit(11);
    free(io);

    return EXIT_SUCCESS;
}

int inp()
{
    int val;
    if (readInt(20, &val)) {
        return EXIT_FAILURE;
    }
    if (sc_memorySet(xy.x + xy.y * 10, val)) return EXIT_FAILURE;
    return EXIT_SUCCESS;

}

int printAccum()
{
    char buff[7];
    int ac;
    if (sc_getData(getAccum(), &ac)) return EXIT_FAILURE;
    sprintf(buff, "%05d", ac);
    if (mt_gotoXY(79, 2)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, buff, strlen(buff)) < 0) return EXIT_FAILURE;
    return 0;
}

int printCount()
{
    char buff[6];
    sprintf(buff, "%04d", getCount());
    if (mt_gotoXY(79, 5)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, buff, strlen(buff)) < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/*ETM0P*/
int printFLAGS()
{
    char freg[] = "- - - - -";
    int reg;
    if (sc_regGet(FLAG_E, &reg)) return EXIT_FAILURE;
    if (reg) freg[0] = 'E';

    if (sc_regGet(FLAG_T, &reg)) return EXIT_FAILURE;
    if (reg) freg[2] = 'T';
    if (sc_regGet(FLAG_M, &reg)) return EXIT_FAILURE;
    if (reg) freg[4] = 'M';
    if (sc_regGet(FLAG_0, &reg)) return EXIT_FAILURE;
    if (reg) freg[6] = '0';
    if (sc_regGet(FLAG_P, &reg)) return EXIT_FAILURE;
    if (reg) freg[8] = 'P';
    if (mt_gotoXY(77, 11)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, freg, strlen(freg)) < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int q_add(char *message)
{
    if (!message)
        return EXIT_FAILURE;

    if (*(qIO + 4) == NULL) free(*(qIO + 4));
    for (int i = 4; i > 0; --i) {
        *(qIO + i) = *(qIO + i - 1);
    }
    *qIO = malloc(strlen(message) + 1);
    if (!(*qIO))
        return EXIT_FAILURE;

    strcpy(*qIO, message);
    return EXIT_SUCCESS;
}

void q_free()
{
    for (int i = 0; i < 5; ++i) {
        if (*(qIO + i)) free(*(qIO + i));
        qIO[i] = NULL;
    }
}

int printIO()
{
    if (mt_gotoXY(1, 24)) return EXIT_FAILURE;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (mt_gotoXY(1 + j, 24 + i)) return EXIT_FAILURE;
            if (write(STDOUT_FILENO, " ", 1) < 0) return EXIT_FAILURE;
        }
    }
    for (int i = 4; i >= 0; --i) {
        if (mt_gotoXY(1, 24 + i)) return EXIT_FAILURE;
        if (*(qIO + i))
            if (write(STDOUT_FILENO, *(qIO + i), strlen(*(qIO + i))) < 0) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* my space; DON'T TOUCH */

int IOcorrect(char *str)
{
    int data = checkData(str);
    int com = checkCom(str);
    return (data * com);
}

int checkData(char *str)
{
    if (!strlen(str)) return EXIT_FAILURE;

    if (str[0] == '-') {
        if (strlen(str) > 6) return EXIT_FAILURE;

        for (int i = 1; i < strlen(str); i++) {
            if (str[i] < '0' || str[i] > '9') return EXIT_FAILURE;
        }
    } else {
        if (strlen(str) > 5) return EXIT_FAILURE;

        for (int i = 0; i < strlen(str); i++) {
            if (str[i] < '0' || str[i] > '9') return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int checkCom(char *str)
{
    if (strlen(str) > 5) return EXIT_FAILURE;

    int dt = 0;
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ':') {
            dt = i;
            str[i] = '\0';
            ++k;
        }
    }
    if (k != 1) return EXIT_FAILURE;
    if ((strlen(str) == 0) || (strlen(str) > 2)) return EXIT_FAILURE;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') &&
            (str[i] < 'A' && str[i] > 'F'))
            return EXIT_FAILURE;
    }

    if ((strlen(str + dt + 1) == 0) || (strlen(str + dt + 1) > 2)) return EXIT_FAILURE;
    for (int i = dt + 1; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') &&
            (str[i] < 'A' || str[i] > 'F'))
            return EXIT_FAILURE;
    }
    str[dt] = ':';

    return EXIT_SUCCESS;
}

int printOperation()
{
    int operation = -1;
    if (sc_memoryGet(xy.x + xy.y * 10, &operation)) return EXIT_FAILURE;
    if (isData(operation)) return EXIT_SUCCESS;

    int a, b;
    if (sc_commandDecode(operation, &a, &b)) return EXIT_SUCCESS;
    char o[6];
    sprintf(o, "%02X:%02X", a, b);

    if (mt_gotoXY(79, 8)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, o, strlen(o)) < 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int changeAccum()
{
    int new_accumulator;
    if (readInt(10, &new_accumulator)) {
        return EXIT_FAILURE;
    }
    if (isData(new_accumulator) == 0) {
        char err[] = "Err_a";
        for (int i = 0; i < 5; ++i) {
            qIO[0][i] = err[i];
        }
        return EXIT_FAILURE;
    }
    setAccum(new_accumulator);
    return EXIT_SUCCESS;
}

int changeCounter()
{
    int new_counter;
    if (readInt(10, &new_counter)) {
        return EXIT_FAILURE;
    }
    if (isData(new_counter) == 0) {
        char err[] = "Err_i";
        for (int i = 0; i < 5; ++i) {
            qIO[0][i] = err[i];
        }
        return EXIT_FAILURE;
    }
    if (sc_getData(new_counter, &new_counter)) return EXIT_FAILURE;
    if (setCounter(new_counter)) exit(11);
    return EXIT_SUCCESS;
}

void CU(int signo)
{
    int t;
    sc_regGet(FLAG_T, &t);
    if (t && signo == SIGALRM) {
//        memory_print(counter, clr_green, clr_black);
        return;
    }
    int command, operand;
    int cur_mem;



    if (sc_memoryGet(getCount(), &cur_mem)) {
        sc_regSet(FLAG_M, 1);
        signal(SIGALRM, SIG_IGN);
        sc_regSet(FLAG_T, 1);
        memory_print(counter, clr_green, clr_black);
        return;
    }
    if (sc_commandDecode(cur_mem, &command, &operand)) {
        sc_regSet(FLAG_E, 1);
        signal(SIGALRM, SIG_IGN);
        sc_regSet(FLAG_T, 1);
        memory_print(counter, clr_green, clr_black);
        return;
    }
    if ((operand < 0) && (operand >= SIZE)) {
        sc_regSet(FLAG_M, 1);
        signal(SIGALRM, SIG_IGN);
        sc_regSet(FLAG_T, 1);
        memory_print(counter, clr_green, clr_black);
        return;
    }

    if (((command >= 0x30) && (command <= 0x33)) || ((command >= 0x60) && (command <= 61))) {
        if (ALU(command, operand)) {
            sc_regSet(FLAG_T, 1);
            sc_regSet(FLAG_E, 1);
        }
    } else {
        switch (command) {
            case 0x10: //* READ *//*
                if (READ(operand)) { sc_regSet(FLAG_T, 1); }
                break;

            case 0x11: //* WRITE *//*
                if (WRITE(operand)) { sc_regSet(FLAG_T, 1); }
                break;

            case 0x20: //* LOAD *//*
                if (LOAD(operand)) { sc_regSet(FLAG_T, 1); }
                break;

            case 0x21: //* STORE *//*
                if (STORE(operand)) { sc_regSet(FLAG_T, 1); }
                break;

            case 0x40: //* JUMP *//*
                if (JUMP(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;

            case 0x41: //* JNEG *//*
                if (JNEG(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;

            case 0x42: //* JZ *//*
                if (JZ(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;

            case 0x43: //* HALT *//*
                if (HALT(operand)) { sc_regSet(FLAG_T, 1); }
                break;

            case 0x55 : // JNS
                if (JNS(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;
            case 0x56 : // JC
                if (JC(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;
            case 0x57: // JNC
                if (JNC(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;
            case 0x58 : // JP
                if (JP(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;
            case 0x59: // JNP
                if (JNP(operand)) { sc_regSet(FLAG_T, 1); }
                else --counter;
                break;
            default:
                sc_regSet(FLAG_E, 1);
                sc_regSet(FLAG_T, 1);
                break;
        }
    }
    if (IncCount()) {
        sc_regSet(FLAG_M, 1);
        sc_regSet(FLAG_T, 1);
    }
    memory_print(counter, clr_green, clr_black);
    //sc_regGet(FLAG_T, &t);
    //if (t) {
    //  signal(SIGALRM, SIG_IGN);
    // }
}


void sigReset(int signo)
{
    mt_clscr();
    init_data();
    box_print();
    memory_print(0, clr_brown, clr_red);
    q_free();
}

char *readString()
{
    char *str = NULL;
    str = calloc(32, sizeof(char));
    if (!str) return NULL;

    for (int i = 0; i < 31; ++i) {
        if (read(STDIN_FILENO, (str + i), sizeof(char)) < 0) return NULL;
        if ((*(str + i)) == '\n') {
            *(str + i) = '\0';
            break;
        }
    }
    //check incorrect
    if (strlen(str) == 0) {
        free(str);
        return NULL;
    }
    return str;
}

int checkFile(char *str)
{
    if (strlen(str) > 254) return EXIT_FAILURE;

    // /, \, ?, <, >, *, \ |
    char a[8] = {'/', '\\', '?', '<', '>', '*', '|', '\''};

    int strl = (int) strlen(str);
    for (int i = 0; i < strl; i++) {
        for (int j = 0; j < 8; j++) {
            if (str[i] == a[j]) return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/* my space; DON'T TOUCH */

int ALU(int command, int operand)
{
    int tmp;

    switch (command) {
        case 0x30: /* ADD */
            if (cADD(operand)) return EXIT_FAILURE;
            break;

        case 0x31: /* SUB */
            if (SUB(operand)) return EXIT_FAILURE;
            break;

        case 0x33: /* MUL */
            if (MUL(operand)) return EXIT_FAILURE;
            break;

        case 0x32: /* DIV */
            if (DIVIDE(operand)) return EXIT_FAILURE;
            break;
        case 0x51:
            if (NOT(operand)) return EXIT_FAILURE;
            break;
        case 0x52:
            if (AND(operand)) return EXIT_FAILURE;
            break;
        case 0x53:
            if (OR(operand)) return EXIT_FAILURE;
            break;
        case 0x54:
            if (XOR(operand)) return EXIT_FAILURE;
            break;
        case 0x60:
            if (CHL(operand)) return EXIT_FAILURE;
            break;
        case 0x61:
            if (SHR(operand)) return EXIT_FAILURE;
            break;
        default:
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
    м - выход за границы
    0 - деление на 0
    п - переполнение
*/

/* Ввод\вывод */
int WRITE(int v) {
    int val;
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (!isData(val)) {
        return EXIT_FAILURE;
    }

    sc_getData(val, &val);
    char str[16];
    sprintf(str, "Out : %d", val);
    q_add(str);
    printIO();

    return EXIT_SUCCESS;
}

int READ(int v) {
    int val;
    mt_gotoXY(1, 29);
    write(STDOUT_FILENO, "Please, enter : ", 16);
    rk_mytermregime(1, 0, 0, 1, 1);
    if (readInt(8, &val)) {
        sc_regSet(FLAG_P, 1);
        rk_mytermregime(0, 0, 1, 0, 1);
        return EXIT_FAILURE;
    }
    rk_mytermregime(0, 0, 1, 0, 1);

    sc_memorySet(v, val);

    return EXIT_SUCCESS;
}

/* Операции загрузки\выгрузки в аккумулятор */
int LOAD(int v) {
    if (sc_memoryGet(v, &accumulator))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int STORE(int v) {
    if (sc_memorySet(v, getAccum())) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* Арифметика */
int cADD(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (!isData(getAccum())) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }

    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val += tmp_get_acc;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
    if ((val & 1)) {
        sc_regSet(FLAG_PF, 0);
    } else {
        sc_regSet(FLAG_PF, 1);
    }

    return EXIT_SUCCESS;
}

int SUB(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }

    val = tmp_get_acc - val;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
    if ((val & 1)) {
        sc_regSet(FLAG_PF, 0);
    } else {
        sc_regSet(FLAG_PF, 1);
    }
    return EXIT_SUCCESS;
}

int DIVIDE(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }
    if (!val) {
        sc_regSet(FLAG_0, 1);
        sc_regSet(FLAG_T, 1);
        return EXIT_SUCCESS;
    }

    val = tmp_get_acc / val;
    sc_setData(val, &accumulator);
    if ((val & 1)) {
        sc_regSet(FLAG_PF, 0);
    } else {
        sc_regSet(FLAG_PF, 1);
    }
    return EXIT_SUCCESS;
}

int MUL(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }

    val = tmp_get_acc * val;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
    if ((val & 1)) {
        sc_regSet(FLAG_PF, 0);
    } else {
        sc_regSet(FLAG_PF, 1);
    }
    return EXIT_SUCCESS;
}

/* ЦУ */
int JUMP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }

    counter = (unsigned) v;

    return EXIT_SUCCESS;
}

int JNEG(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }


    if (tmp_get_acc < 0)
        counter = (unsigned) v;
    else ++counter;

    return EXIT_SUCCESS;
}

int JZ(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }


    if (tmp_get_acc == 0)
        counter = (unsigned) v;
    else ++counter;

    return EXIT_SUCCESS;
}

int HALT(int v) {
    char str[32];
    sprintf(str, "Exit");
    q_add(str);

    sc_regSet(FLAG_T, 1);
    printIO();

    return EXIT_SUCCESS;
}

/* УЗЕРС */
int NOT(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_SUCCESS;
    }

    tmp_get_acc = ~tmp_get_acc;
    sc_memorySet(v, tmp_get_acc);

    return EXIT_SUCCESS;
}

int AND(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_SUCCESS;
    }

    int tmp_get_dat;
    if (sc_memoryGet(v, &tmp_get_dat))
        return EXIT_FAILURE;

    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }


    tmp_get_acc = tmp_get_acc & tmp_get_dat;

    if (sc_setData(tmp_get_acc, &accumulator)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int OR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_SUCCESS;
    }

    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);

    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }


    tmp_get_acc = tmp_get_acc | tmp_get_dat;

    if (sc_setData(tmp_get_acc, &accumulator)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

int XOR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_SUCCESS;
    }

    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);

    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }


    tmp_get_acc = tmp_get_acc ^ tmp_get_dat;

    if (sc_setData(tmp_get_acc, &accumulator)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

int JNS(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_FAILURE;
    }

    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);

    if (tmp_get_acc > 0)
        counter = (unsigned) v;
    else ++counter;

    return EXIT_SUCCESS;
}

int JC(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }

    int tmp_get_flg;
    if (sc_regGet(FLAG_P, &tmp_get_flg)) {
        return EXIT_FAILURE;
    }
    if (tmp_get_flg)
        counter = (unsigned) v;
    else
        ++counter;

    return EXIT_SUCCESS;
}

int JNC(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }

    int tmp_get_flg;
    if (sc_regGet(FLAG_P, &tmp_get_flg)) {
        return EXIT_FAILURE;
    }
    if (!tmp_get_flg)
        counter = (unsigned) v;
    else ++counter;

    return EXIT_SUCCESS;
}

int JP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int t;
    sc_regGet(FLAG_PF, &t);
    if (t)
        counter = (unsigned) v;
    else
        ++counter;

    return EXIT_SUCCESS;
}

int JNP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int t;
    sc_regGet(FLAG_PF, &t);
    if (!t)
        counter = (unsigned) v;
    else
        ++counter;

    return EXIT_SUCCESS;
}

int CHL(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }

    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);

    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }

    tmp_get_dat <<= 1;

    if (sc_setData(tmp_get_dat, &accumulator)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int SHR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }

    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);

    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }

    tmp_get_dat >>= 1;

    if (sc_setData(tmp_get_dat, &accumulator)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int transl(char *com)
{
    char *tok  = strtok(com, " ");
    char *argv[8];
    int argc = 0;
    while(tok != NULL) {
        argv[argc] = tok;
        ++argc;
        tok = strtok(NULL, " ");
    }
    if (strcmp(argv[0], "sat") == 0) {
        asembler(argc, argv);
    } else if (strcmp(argv[0], "bas") == 0) {
        basic(argc, argv);
    } else return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

