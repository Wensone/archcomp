#include "term.h"

uint8_t mt_setfgcolor(){

    return SUCCES;
}

uint8_t mt_setfgcolor(COLORS_TERM color){
    printf("\E[4%dm", color);
    if(color < clr_black || color > clr_default){
        return ERROR;
    }
    return SUCCESS;
}
