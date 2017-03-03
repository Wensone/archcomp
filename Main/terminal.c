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
        case ':': {
            bc_printbigchar(big + ADD, a, b, fg, bg);
            break;
        }
        case '-': {
            bc_printbigchar(big + AM, a, b, fg, bg);
            break;
        }
        default:
            mt_clscr();
            fprintf(stderr, "Incorrect char[%d]\n", x);
            rk_mytermstore();
            return -1;
    }
    return 0;
}

void memory_print(uint8_t cur, enum COLORS_TERM fg, enum COLORS_TERM bg) {
    uint16_t i, x, y;

    x = 2;
    y = 2;
    uint16_t data;
    char buf[] = {0, 0, 0, 0, 0};
    for (i = 0; i < 100; i++) {
        mt_gotoXY(x, y);
        y++;
        sc_memoryGet(i, &data);
        sprintf(buf, "+%04X", data);
        if ((cur ) == i) {
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

int init_data() {
    int fd = open("BIG_CHARS", O_RDONLY);
    if (fd == -1) {
        mt_clscr();
        fprintf(stderr, "Read Big_Chars\n");
        return -2;
    }
    int count;
    if (bc_bigcharread(fd, big, 19, &count) == ERROR) {
        fprintf(stderr, "Bad read BigChars\n");
        return -1;
    }
    xy.x = 0;
    xy.y = 0;
    return 0;
}

int print_BC(uint16_t symb, enum COLORS_TERM fg, enum COLORS_TERM bg) {
    uint8_t x = 2,
            y = 14;
    char hex[6];
    int i = 0;
    memset(hex, 0, 5);
    if ((symb >> 14) & 1) {// если дата
        symb &= ~(1 << 14); // убираем единицу
        if (symb >> 15) { // если есть минус
            symb &= ~(1 << 15); // убираем минус
            // print_BC('-', fg, bg); // рисуем его
            ++i;
            hex[0] = '-';
            sprintf(hex + 1, "%04d", symb); // минимум 4 символа + заполнить нулями если нет символов
        } else {
            sprintf(hex, "%05d", symb); // вывод с +0000
        }
    } else { // если команда
        uint8_t oper, val;
        sc_commandDecode(symb, &oper, &val); // декодируем инфу
        sprintf(hex, "%X:%X", oper, val); // приводим к типу и записываем в ячейку в таком виде
    }
    for ( ; i < 5; i++) { // отрисовка строки бигчарами
        if (-1 == print_char(hex[i], x, y, fg, bg)) {
            fprintf(stderr, "Bad print %d | %s\n", i, hex);
            exit(1);
        }
        x += 9;
    }
}

void move(KEYS key) {
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
    memory_print((uint8_t) (xy.x + (xy.y * 10)), clr_brown, clr_red);
}

uint8_t readInt(int size, uint8_t *oper, uint16_t *val) {
    char buff[size];
    for (int i = 0; i < size; i++) buff[i] = 0;
    int t = 0;

    for (int i = 0; buff[i - 1] != '\n'; i++) {
        read(STDIN_FILENO, (buff + i), 1);
        if (buff[i] == ':') t = i;
    }

    if (t) {
        *oper = (uint8_t) atoi(buff);
        *val = (uint16_t) atoi(buff + t + 1);
        // mt_gotoXY(40, 40);
        // printf("%d | %d", *oper, *val);
        return 1; // считали команду
    } else {
        if (buff[0] == '-') {
            *val = (uint16_t) atoi(buff + 1);
            *val |= 1 << 15;
        } else {
            *val = (uint16_t) atoi(buff);
        }
    }
    return 0;
}

uint8_t inp(){
    uint16_t val;
    uint8_t oper;
    if (readInt(8, &oper, &val)) { // если команда - закодировали
        sc_commandEncode(oper, (uint8_t) val, &val);
    } else if (1 & (val >> 14)) { // вышли ли за границы
        return 1;
    } else { // ставим, что это у нас дата
        val |= 1 << 14;
    }
    sc_memorySet((uint8_t) (xy.x + xy.y * 10), val); // записали в текущую ячейку
    return 0;

}
