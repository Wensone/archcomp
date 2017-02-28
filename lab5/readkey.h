#ifndef READKEY_H
#define READKEY_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

/*
    tcflag_t c_iflag;      // режимы ввода
    tcflag_t c_oflag;      // режимы вывода
    tcflag_t c_cflag;      // режимы управления
    tcflag_t c_lflag;      // режимы локали
    cc_t c_cc[NCCS];       // управляющие символы
*/
enum KEYS {
    KEY_l,
    KEY_s,
    KEY_r,
    KEY_t,
    KEY_i,
    KEY_q,
    KEY_f5,
    KEY_f6,
    KEY_up,
    KEY_down,
    KEY_left,
    KEY_right,
    KEY_enter,
    KEY_other
};

int rk_readkey(enum KEYS *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif // READKEY_H
