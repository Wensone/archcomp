#include "head/terminal.h"

int main()
{
    if (init_data()) {
        fprintf(stderr, "init_data\n");
        return EXIT_FAILURE;
    }
    if (box_print()) {
        fprintf(stderr, "box_print\n");
        return EXIT_FAILURE;
    }

    if (memory_print(0, clr_green, clr_magenta)) {
        fprintf(stderr, "memory_print\n");
        return EXIT_FAILURE;
    };
    char FileMemory[16] = "MemData";
    signal(SIGUSR1, sigReset);
    signal(SIGALRM, sigGo);

    KEYS key = no_key;
    move(no_key);
    while (key != key_esc) {
        mt_gotoXY(1, 29);
        rk_readkey(&key);
        switch (key) {
            case (key_s) : {
//              read(STDIN_FILENO, FileMemory, 16);
                sc_memorySave(FileMemory);
                break;
            }
            case (key_l) : {
                //
                sc_memoryLoad(FileMemory);
                break;
            }
            case (key_r) : {
                //
                break;
            }
            case (keyt) : {
                break;
            }
            case (key_i) : {
                raise(SIGUSR1);
                break;
            }
            case (key_f5) : {
                mt_gotoXY(1, 29);
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                changeAccum();
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);
                if (printIO()) {
                    mt_clscr();
                    fprintf(stderr, "Bad request bu print queue\n");
                    return EXIT_FAILURE;
                }
                move((no_key));
                break;
            }
            case (key_f6) : {
                mt_gotoXY(1, 29);
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                changeCounter();
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);
                if (printIO()) {
                    mt_clscr();
                    fprintf(stderr, "Bad request bu print queue\n");
                    return EXIT_FAILURE;
                }
                move((no_key));
                break;
            }
            case (key_enter) : {
                mt_gotoXY((2 + (xy.y * 7)), (xy.x + 2));
                write(STDOUT_FILENO, "     ", 5);
                mt_gotoXY((2 + (xy.y * 7)), (xy.x + 2));
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                inp();
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);
                if (printIO()) {
                    mt_clscr();
                    fprintf(stderr, "Bad request bu print queue\n");
                    return EXIT_FAILURE;
                }
                move((no_key));
                break;
            }
            default : {
                move(key);
                break;
            }
        }
    }

    q_free();
    rk_mytermstore();
    mt_clscr();
    return 0;
}