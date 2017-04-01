#include "terminal.h"

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
    char buf[] = {0, 0, 0, 0, 0};
    for (i = 0; i < 100; i++) {
        if (mt_gotoXY(x, y)) return EXIT_FAILURE;
        y++;
        if (sc_memoryGet(i, &data)) return EXIT_FAILURE;
        sprintf(buf, "+%04X", data);
        if ((cur) == i) {
            if (mt_setfgcolor(fg)) return EXIT_FAILURE;
            if (mt_setbgcolor(bg)) return EXIT_FAILURE;

            if (write(STDOUT_FILENO, buf, strlen(buf)) < 0) return EXIT_FAILURE;
            if (print_BC(data, clr_cyan, clr_black)) return EXIT_FAILURE;

            if (mt_setfgcolor(clr_default)) return EXIT_FAILURE;
            if (mt_setbgcolor(clr_default)) return EXIT_FAILURE;
        } else {
            if (write(STDOUT_FILENO, buf, strlen(buf)) < 0) return EXIT_FAILURE;
        }
        if (((i + 1) % 10) == 0) {
            x += 7;
            y = 2;
        }
    }
    return EXIT_SUCCESS;
}

int init_data()
{
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

    counter = 0;
    accumulator = 0;
    if (sc_regInit()) return EXIT_FAILURE;
    if (sc_memoryInit()) return EXIT_FAILURE;

    if (rk_mytermsave()) return EXIT_FAILURE;
    if (rk_mytermregime(0, 0, 1, 0, 1)) return EXIT_FAILURE;
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

int printAccum()
{
    char buff[6];
    sprintf(buff, "%04d", getAccum());
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

/* my space; DON'T TOUCH */

int IOcorrect(char *str) {
	int data = checkData(str);
	int com = checkCom(str);

	return (data & com);
}

int checkData(char *str) {
	if (strlen(str) == 1) return EXIT_FAILURE;

	if (str[0] == '-') {
		if (strlen(str) > 6) return EXIT_FAILURE;

		for (int i = 1; i < strlen(str); i++) {
			if (str[i] < '0' && str[i] > '9') return EXIT_FAILURE;
		}
	} else if (str[0] >= '0' && str[0] <= '9') {
		if (strlen(str) > 5) return EXIT_FAILURE;

		for (int i = 1; i < strlen(str); i++) {
			if (str[i] < '0' && str[i] > '9') return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}


int checkCom(char *str) {
	if (strlen(str) > 5) return EXIT_FAILURE;

	if (str[0] < '0' && str[0] > '9') return EXIT_FAILURE;
	if (str[1] < '0' && str[1] > '9') return EXIT_FAILURE;
	if (str[2] != ':') return EXIT_FAILURE;
	if (str[3] < '0' && str[3] > '9') return EXIT_FAILURE;
	if (str[4] < '0' && str[4] > '9') return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/* my space; DON'T TOUCH */
