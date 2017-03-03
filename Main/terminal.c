#include "terminal.h"

int box_print() {
    mt_clscr();

    bc_box(1, 1, 70, 12);
    mt_gotoXY(30, 1);
    write(STDOUT_FILENO, "Memory", 6);

    bc_box(72, 1, 20, 3);
    mt_gotoXY(77, 1);
    write(STDOUT_FILENO, "Accumulator", 11);

    bc_box(72, 4, 20, 3);
    mt_gotoXY(73, 4);
    write(STDOUT_FILENO, "InstructionCounter", 18);

    bc_box(72, 7, 20, 3);
    mt_gotoXY(77, 7);
    write(STDOUT_FILENO, "Operation", 9);

    bc_box(72, 10, 20, 3);
    mt_gotoXY(79, 10);
    write(STDOUT_FILENO, "Flags", 5);

    bc_box(1, 13, 46, 10); // big chars


    bc_box(47, 13, 45, 10);
    mt_gotoXY(49, 13);
    write(STDOUT_FILENO, "Keys", 4);

    mt_gotoXY(48, 14);
    write(STDOUT_FILENO, "l - load", 8);
    mt_gotoXY(48, 15);
    write(STDOUT_FILENO, "s - save", 8);
    mt_gotoXY(48, 16);
    write(STDOUT_FILENO, "r - run", 7);
    mt_gotoXY(48, 17);
    write(STDOUT_FILENO, "t - step", 8);
    mt_gotoXY(48, 18);
    write(STDOUT_FILENO, "i - reset", 9);
    mt_gotoXY(48, 19);
    write(STDOUT_FILENO, "F5 - accumulator", 16);
    mt_gotoXY(48, 20);
    write(STDOUT_FILENO, "F6 - InstructionCounter", 23);

    mt_gotoXY(1, 23);
    write(STDOUT_FILENO, "Input\\Output:", 14);

    mt_gotoXY(30, 15);
}

int print_char(char x, uint8_t a, uint8_t b, enum COLORS_TERM fg, enum COLORS_TERM bg) {
    switch (x) {
        case ('0'): {
            bc_printbigchar(big + A0, a, b, fg, bg);
            break;
        }
        case ('1'): {
            bc_printbigchar(big + A1, a, b, fg, bg);
            break;
        }
        case ('2'): {
            bc_printbigchar(big + A2, a, b, fg, bg);
            break;
        }
        case ('3'): {
            bc_printbigchar(big + A3, a, b, fg, bg);
            break;
        }
        case ('4'): {
            bc_printbigchar(big + A4, a, b, fg, bg);
            break;
        }
        case ('5'): {
            bc_printbigchar(big + A5, a, b, fg, bg);
            break;
        }
        case ('6'): {
            bc_printbigchar(big + A6, a, b, fg, bg);
            break;
        }
        case ('7'): {
            bc_printbigchar(big + A7, a, b, fg, bg);
            break;
        }
        case ('8'): {
            bc_printbigchar(big + A8, a, b, fg, bg);
            break;
        }
        case ('9'): {
            bc_printbigchar(big + A9, a, b, fg, bg);
            break;
        }
        case ('A'): {
            bc_printbigchar(big + AA, a, b, fg, bg);
            break;
        }
        case ('B'): {
            bc_printbigchar(big + AB, a, b, fg, bg);
            break;
        }
        case ('C'): {
            bc_printbigchar(big + AC, a, b, fg, bg);
            break;
        }
        case ('D'): {
            bc_printbigchar(big + AD, a, b, fg, bg);
            break;
        }
        case ('E'): {
            bc_printbigchar(big + AE, a, b, fg, bg);
            break;
        }
        case ('F'): {
            bc_printbigchar(big + AF, a, b, fg, bg);
            break;
        }
        case '+': {
            bc_printbigchar(big + APlus, a, b, fg, bg);
            break;
        }
        case '\0': {
            bc_printbigchar(big + A0, a, b, fg, bg);
            break;
        }
        default:
            mt_clscr();
            fprintf(stderr, "Incorrect char[%d]\n", x);
            return -1;
    }
    return 0;
}

void memory_print(uint8_t cur, enum COLORS_TERM fg, enum COLORS_TERM bg) {
    uint16_t i, x, y;

    x = 2;
    y = 2;
    char buf[5];
    for (i = 0; i < 100; i++) {
        mt_gotoXY(x, y);
        y++;
        sprintf(buf, "+%04X", ram[i]);
//        printf("+%0*X\n", 4, ram[i - 1]);
        if ((cur ) == i) {
            mt_setfgcolor(fg);
            mt_setbgcolor(bg);
            write(STDOUT_FILENO, buf, strlen(buf));
            print_BC(ram[i], clr_cyan, clr_black);
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

int init_data() {
    int fd = open("BIG_CHARS", O_RDONLY);
    if (fd == -1) {
        mt_clscr();
        fprintf(stderr, "Read Big_Chars\n");
        return -2;
    }
    int count;
    if (bc_bigcharread(fd, big, 17, &count) == ERROR) {
        fprintf(stderr, "Bad read BigChars\n");
        return -1;
    }
    return 0;
}

int print_BC(uint32_t symb, enum COLORS_TERM fg, enum COLORS_TERM bg) {
    uint8_t x = 2,
            y = 14;
    char hex[5];
//    memset(hex, 48, 5);
    sprintf(hex, "%05d", symb);
    for (int i = 0; i < 5; i++) {
        if (-1 == print_char(hex[i], x, y, fg, bg)) {
            fprintf(stderr, "Bad print %s\n", hex);
            exit(1);
        }
        x += 9;
    }
}

