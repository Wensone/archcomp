#include "terminal.h"

int main()
{
    if (box_print()) {
        fprintf(stderr, "box_print\n");
        return EXIT_FAILURE;
    }

    if (memory_print(0, clr_green, clr_magenta)) {
        fprintf(stderr, "memory_print\n");
        return EXIT_FAILURE;
    };
    if (init_data()) {
        fprintf(stderr, "init_data\n");
        return EXIT_FAILURE;
    }
    char FileMemory[16] = "MemData";

    KEYS key = no_key;
    while (key != key_esc) {
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
                //
                break;
            }
            case (key_i) : {
                mt_clscr();
                box_print();
                memory_print(0, clr_green, clr_magenta);
                counter = 0;
                sc_regInit();
                xy.x = xy.y = 0;
                break;
            }
            case (key_f5) : {
                //
                break;
            }
            case (key_f6) : {
                //
                break;
            }
            case (key_enter) : {
                mt_gotoXY((uint16_t) (2 + (xy.y * 7)), (uint16_t) (xy.x + 2));
                write(STDOUT_FILENO, "     ", 5);
                mt_gotoXY((uint16_t) (2 + (xy.y * 7)), (uint16_t) (xy.x + 2));
                rk_mytermregime(1, 0, 0, 1, 1);
                mt_setfgcolor(clr_blue);

                if (inp()) {
                    mt_gotoXY(1, 24);
                    write(STDOUT_FILENO, "ERROR READ", 10);
                    rk_mytermregime(0, 0, 1, 0, 1);
                    mt_setfgcolor(clr_default);
                    mt_clscr();
                    box_print();
                    memory_print((uint8_t) (xy.x + xy.y * 10), clr_green, clr_magenta);
                    mt_gotoXY(1, 24);
                    write(STDOUT_FILENO, "ERROR READ", 10);
                    break;
                }
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);
                move((no_key));
                break;
            }
            default : {
                move(key);
                break;
            }
        }
    }

    rk_mytermstore();
    return 0;
}