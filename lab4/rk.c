//
// Created by direnol on 24.02.17.
//


#include "rk.h"

uint8_t rk_readkey(KEYS *key) {
    int n;
    char read_key[7];

    memset(read_key, 0, sizeof(read_key));
    if ((n = (int) read(0, read_key, 6)) < 0) {
        perror("read");
        return ERROR;
    } else {
        if (read_key[0] == 't')
            *key = keyt;
        if (read_key[0] == 'r')
            *key = key_r;
        if (read_key[0] == 'c')
            *key = key_c;
        if (read_key[0] == 's')
            *key = key_s;
        if (read_key[0] == 'l')
            *key = key_l;
        if (read_key[0] == 'i')
            *key = key_i;
        if (read_key[0] == '\n')
            *key = key_enter;
        if (read_key[0] == '\033')
            *key = key_esc;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == '1') && (read_key[3] == '5') &&
            (read_key[4] == '~'))
            *key = key_f5;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == '1') && (read_key[3] == '7') &&
            (read_key[4] == '~'))
            *key = key_f6;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == 'C'))
            *key = key_right;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == 'D'))
            *key = key_left;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == 'A'))
            *key = key_up;
        if ((read_key[0] == '\033') && (read_key[1] == '[') && (read_key[2] == 'B'))
            *key = key_down;
    }
    return SUCCESS;
}

uint8_t rk_mytermsave() {
    return 0;
}

uint8_t rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
    struct termios tcset;
    if ((regime < 0) || (vtime < 0)||(vmin<0) || (echo < 0) || (sigint < 0))
        return ERROR;//если не поступили параметры

    tcgetattr(0, &tcset);
    if (regime)
        tcset.c_lflag |= ICANON;
    else
        tcset.c_lflag &= ~ICANON;/* Режимы дисц. линии связи (Канонический построчный ввод) */

    if (echo)
        tcset.c_lflag |= ECHO;
    else
        tcset.c_lflag &= ~ECHO;//ECHO Разрешить отображение вводимых символов на экране

    if (sigint)
        tcset.c_lflag |= ISIG;
    else
        tcset.c_lflag &= ~ISIG;//обработка клавиш прирывания,ISIG Разрешить обработку прерываний

    tcsetattr(0, TCSAFLUSH, &tcset);
    return SUCCESS;
}
