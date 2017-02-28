//
// Created by direnol on 24.02.17.
//

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#ifndef ARCH_RK_H
#define ARCH_RK_H

enum ERRORS {
    ERROR = -1,
    SUCCESS
};

typedef enum keys {
    keyt,
    key_f5,
    key_f6,
    key_c,
    key_up,
    key_down,
    key_left,
    key_right,
    key_esc,
    key_enter,
    key_l,
    key_i,
    key_s,
    key_r,
    no_key
} KEYS;

enum ERRORS rk_readkey(KEYS *);

enum ERRORS rk_mytermsave();

enum ERRORS rk_mytermstore();

enum ERRORS rk_mytermregime(int regime, cc_t vtime, cc_t vmin, int echo, int sigint);

#endif //ARCH_RK_H
