#include "head/rk.h"

int main()
{
    struct termios s;
    tcgetattr(STDIN_FILENO,  &s);
    if (rk_mytermsave()) {
        fprintf(stderr, "Save\n");
        tcsetattr(STDIN_FILENO, TCSANOW, &s);
        return 1;
    }
    rk_mytermregime(0, 0, 1, 0, 1);
    KEYS num = no_key;
    char k = '4';
    do {
        rk_readkey(&num);
        printf("%d\n", num);
    } while (num != no_key);

    //write(STDOUT_FILENO, &k, sizeof(k));



    if (rk_mytermstore()) {
        fprintf(stderr, "Store\n");
        tcsetattr(STDIN_FILENO, TCSANOW, &s);
        return 1;
    }
    return 0;
}