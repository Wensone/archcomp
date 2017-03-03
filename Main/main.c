#include "terminal.h"

int main()
{
    rk_mytermsave();
    rk_mytermregime(0, 0, 1, 0, 1);
    box_print();
    memory_print(0, clr_green, clr_magenta);
    init_data();

    KEYS key = no_key;
    uint8_t x = 0, y = 0;
    while (ERROR != rk_readkey(&key) && key != key_esc) {
        switch (key) {
            case (key_up) : {
                if (x == 0 && y == 0) break;
                if (x == 0) {
                    x = 9;
                    y--;
                } else {
                    x--;
                }
                break;
            }
            case (key_down) : {
                if (x == 9 && y == 9) break;
                if (x == 9) {
                    x = 0;
                    y++;
                } else {
                    x++;
                }
                break;
            }
            case (key_left) : {
                if (y == 0) break;
                y--;
                break;
            }
            case (key_right) : {
                if (y == 9) break;
                y++;
                break;
            }
            default : {
                break;
            }
        }
        memory_print((uint8_t) (x + (y * 10)), clr_brown, clr_red);
    }
    rk_mytermstore();
    return 0;
}