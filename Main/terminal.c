#include "terminal.h"

int box_print()
{
    if (mt_clscr()) return EXIT_FAILURE;

    if (bc_box(1, 1, 70, 12)) return EXIT_FAILURE;
    if (mt_gotoXY(30, 1)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Memory", 6)) return EXIT_FAILURE;

    if (bc_box(72, 1, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(77, 1)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Accumulator", 11)) return EXIT_FAILURE;

    if (bc_box(72, 4, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(73, 4)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "InstructionCounter", 18)) return EXIT_FAILURE;

    if (bc_box(72, 7, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(77, 7)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Operation", 9)) return EXIT_FAILURE;

    if (bc_box(72, 10, 20, 3)) return EXIT_FAILURE;
    if (mt_gotoXY(79, 10)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Flags", 5)) return EXIT_FAILURE;

    if (bc_box(1, 13, 46, 10)) return EXIT_FAILURE; // big chars


    if (bc_box(47, 13, 45, 10)) return EXIT_FAILURE;
    if (mt_gotoXY(49, 13)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Keys", 4)) return EXIT_FAILURE;

    if (mt_gotoXY(48, 14)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "l - load", 8)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 15)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "s - save", 8)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 16)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "r - run", 7)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 17)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "t - step", 8)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 18)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "i - reset", 9)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 19)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "F5 - accumulator", 16)) return EXIT_FAILURE;
    if (mt_gotoXY(48, 20)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "F6 - InstructionCounter", 23)) return EXIT_FAILURE;

    if (mt_gotoXY(1, 23)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, "Input\\Output:", 14)) return EXIT_FAILURE;

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
    int i, x, y;
    char buff[6];
    int data;
    if (sc_memoryGet((xy.x + xy.y * 10), &data)) return EXIT_FAILURE;
    if (mt_gotoXY(79, 2)) return EXIT_FAILURE;
    sprintf(buff, "%04d", data);
    if (write(STDOUT_FILENO, buff, strlen(buff)))
        return EXIT_FAILURE;

    sprintf(buff, "%04d", counter);
    if (mt_gotoXY(79, 5)) return EXIT_FAILURE;
    if (write(STDOUT_FILENO, buff, strlen(buff))) return EXIT_FAILURE;

    x = 2;
    y = 2;
    char buf[] = {0, 0, 0, 0, 0};
    for (i = 0; i < 100; i++) {
        mt_gotoXY(x, y);
        y++;
        sc_memoryGet(i, &data);
        sprintf(buf, "+%04X", data);
//        printf("+%0*X\n", 4, ram[i - 1]);
        if ((cur) == i) {
            mt_setfgcolor(fg);
            mt_setbgcolor(bg);

            write(STDOUT_FILENO, buf, strlen(buf));
            print_BC(data, clr_cyan, clr_black);

            mt_setfgcolor(clr_default);
            mt_setbgcolor(clr_default);
        } else {
            write(STDOUT_FILENO, buf, strlen(buf));
        }
        if (((i + 1) % 10) == 0) {
            x += 7;
            y = 2;
        }
    }
}

int init_data()
{
    int fd = open("../lab3/BIG_CHARS", O_RDONLY);
    if (fd == -1) {
        mt_clscr();
        fprintf(stderr, "Read Big_Chars\n");
        return -2;
    }
    int count;
    if (bc_bigcharread(fd, big, 19, &count)) {
        fprintf(stderr, "Bad read BigChars\n");
        return -1;
    }
    if (count != 19) exit(22);
    xy.x = 0;
    xy.y = 0;

    counter = 0;
    accumulator = 0;
    sc_regInit();
    sc_memoryInit();

    rk_mytermsave();
    rk_mytermregime(0, 0, 1, 0, 1);
    return 0;
}

int print_BC(int symb, enum COLORS_TERM fg, enum COLORS_TERM bg)
{
    int x = 2,
            y = 14;
    char hex[6];
    memset(hex, 0, 6);
    if (isData(symb)) {
        if (sc_getData(symb, &symb)) return EXIT_FAILURE;
        sprintf(hex, "%05d", symb);
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
}

int readInt(int size, int *oper, int *val)
{
    char buff[size];
    for (int i = 0; i < size; i++) buff[i] = 0;
    int t = 0;

    for (int i = 0; buff[i - 1] != '\n'; i++) {
        read(STDIN_FILENO, (buff + i), 1);
        if (buff[i] == ':') t = i;
    }

    if (t) {
        *oper = atoi(buff);
        *val = atoi(buff + t + 1);
        mt_gotoXY(40, 40);
//        printf("%d | %d", *oper, *val);
        return 1;
    } else {
        if (buff[0] == '-') {
            *val = atoi(buff + 1);
            *val |= 1 << 15;
        } else {
            *val = atoi(buff);
        }
    }
//   printf("%s\n", buff);
    return 0;
}

int inp()
{
    int val;
    int oper;
    if (readInt(8, &oper, &val)) {
        sc_commandEncode(oper, val, &val);
    } else if (val > 9999) {
        return 1;
    } else {
        val |= 1 << 14;
    }
    sc_memorySet(xy.x + xy.y * 10, val);
    return 0;

}

int getMem(int x)
{

    return 0;
}

