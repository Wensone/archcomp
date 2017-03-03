//
// Created by direnol on 24.02.17.
//


#include <fcntl.h>
#include "rk.h"

enum ERRORS rk_readkey(KEYS *key) {
    char read_key[7];
    *key = no_key;
    memset(read_key, 0, sizeof(read_key));
    if (((int) read(STDIN_FILENO, read_key, 6)) < 0) {
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
        if (read_key[0] == '\033' && read_key[1] == 0)
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

enum ERRORS rk_mytermsave() {
    struct termios opt;
    int file = creat("TermSet", 0644);
    if (file == -1) {
        fprintf(stderr, "Cannot create TermSet\n");
        close(file);
        return ERROR;
    }
    tcgetattr(STDIN_FILENO, &opt);
    if (write(file, &opt, sizeof(opt)) < 1) {
        fprintf(stderr, "Cannot write TermSet\n");
        close(file);
        return ERROR;
    }
    close(file);
    return SUCCESS;
}

enum ERRORS rk_mytermstore()
{
    struct termios opt;
    int file = open("TermSet", O_RDONLY);
    if (file == -1) {
        fprintf(stderr, "Cannot open TermSet\n");
        close(file);
        return ERROR;
    }
    if (read(file, &opt, sizeof(opt)) < 1) {
        fprintf(stderr, "Cannot read TermSet\n");
        close(file);
        return ERROR;
    }
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &opt)) {
        close(file);
        fprintf(stderr, "Set\n");
        return ERROR;
    }
    close(file);
    return SUCCESS;
}

enum ERRORS rk_mytermregime(int regime, cc_t vtime, cc_t vmin, int echo, int sigint) {
    struct termios tcset;
    if ((regime < 0) || (vtime < 0) || (vmin < 0) || (echo < 0) || (sigint < 0))
        return ERROR;//если не поступили параметры

    tcgetattr(STDIN_FILENO, &tcset);
    if (regime) {
        tcset.c_lflag |= ICANON;
    } else {
        tcset.c_lflag &= ~ICANON;
        tcset.c_cc[VMIN] = vmin;
        tcset.c_cc[VTIME] = vtime;
    }/* Режимы дисц. линии связи (Канонический построчный ввод) */


    if (echo)
        tcset.c_lflag |= ECHO;
    else
        tcset.c_lflag &= ~ECHO;//ECHO Разрешить отображение вводимых символов на экране

    if (sigint)
        tcset.c_lflag |= ISIG;
    else
        tcset.c_lflag &= ~ISIG;//обработка клавиш прирывания,ISIG Разрешить обработку прерываний

    tcsetattr(STDIN_FILENO, TCIFLUSH, &tcset);

    return SUCCESS;
}
