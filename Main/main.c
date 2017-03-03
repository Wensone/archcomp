#include "terminal.h"

int main()
{
    //rk_mytermsave();
//    rk_mytermregime(0, 0, 1, 0, 1);
//    box_print();
//    memory_print(0, clr_green, clr_magenta);
    init_data();
//    sc_memorySet(77, 0x13);
//    char FileMemory[16] = "MemData";
    /*KEYS key = no_key;
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
                sc_memoryInit();
                accumulator = 0;
                counter = 0;
                sc_regInit();
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
                rk_mytermregime(0, 0, 1, 1, 1);
                mt_setfgcolor(clr_blue);

                if (inp()) {
                    mt_gotoXY(1, 24);
                    write(STDOUT_FILENO, "ERROR READ", 10);
                    break;
                }
                mt_setfgcolor(clr_default);
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            }
            default : {
                move(key);
                break;
            }
        }
    }*/

    int8_t a;
    uint16_t b, c;
    xy.y = xy.x = 0;
    readInt(8, &a, &b);
//    print_BC((22) | (1 << 14) | (1 << 15), clr_blue, clr_black);
//    rk_mytermstore();
    return 0;
}