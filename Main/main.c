#include "head/terminal.h"

int main(int argc, char **argv)
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

    KEYS key = no_key;
    move(no_key);
    while (1) {
        mt_gotoXY(1, 29);
        rk_readkey(&key);
        switch (key) {
            case (key_s) : {
                mt_gotoXY(1, 29);
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                char *name = readString();
                if (!name) {
                    q_add("incorrect name file");
                    if (printIO()) {
                        mt_clscr();
                        fprintf(stderr, "Bad request bu print queue\n");
                        return EXIT_FAILURE;
                    }
                    move((no_key));
                    break;
                }
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);

                char buff[20 + strlen(name)];
                sprintf(buff, "Name file(s) : %s", name);
                q_add(buff);
                if (sc_memorySave(name)) {
                    sprintf(buff, "Cannot save : %s", name);
                    q_add(buff);
                };
                move((no_key));
                free(name);
                break;
            }
            case (key_l) : {
                mt_gotoXY(1, 29);
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                char *name = readString();
                if (!name) {
                    q_add("incorrect name file");
                    if (printIO()) {
                        mt_clscr();
                        fprintf(stderr, "Bad request bu print queue\n");
                        return EXIT_FAILURE;
                    }
                    move((no_key));
                    break;
                }
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);

                char buff[32 + strlen(name)];
                sprintf(buff, "Name file(l) : %s", name);
                q_add(buff);
                if (transl(name))
                    if (sc_memoryLoad(name)) {
                        sprintf(buff, "File no exist : %s", name);
                        q_add(buff);
                    };
                move((no_key));
                free(name);

                break;
            }
            case (key_r) : {
                sc_regSet(FLAG_T, 0);
                break;
            }
            case (keyt) : {
                sc_regSet(FLAG_T, 1);
                CU(0);
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

                move((no_key));
                break;
            }
        }
        if (move(key)) {
            q_add("You enter bad request, please clear");
        };
        if (printIO()) {
            mt_clscr();
            fprintf(stderr, "Bad request bu print queue\n");
            return EXIT_FAILURE;
        }
        if (key_esc == key) break;
    }
    q_free();
    //basic(argc, argv);
    asembler(argc, argv);
    mt_clscr();
    if (rk_mytermstore()) {
        fprintf(stderr, "Cannot restore\n");
    };
    return 0;
}