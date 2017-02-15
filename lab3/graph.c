#include "graph.h"

uint8_t bc_printA(const char *str){
    printf("\E(0%s\E(B", str);

    return SUCCESS;
}

uint8_t bc_box(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    uint16_t row;
    uint16_t col;

    mt_getscreensize(&row, &col);

    if((x1 < 0) || (y1 < 0) || (x2 < 0) || (y2 < 0) || ((x1 + x2) > col)
        || ((y1 + y2)) > row) {
        return ERROR;
    }
    // X
    for(int i = 1; (x1 + i) < (x1 + x2) - 1; i++) {
        if(mt_gotoXY(x1 + i, y1)) return ERROR;
        bc_printA(CHAR_HOR);
        if(mt_gotoXY(x1 + i, y1 + y2 - 1)) return ERROR;
        bc_printA(CHAR_HOR);
    }
    // y
    for(int i = 1; (y1 + i) < (y1 + y2) - 1; i++) {
        mt_gotoXY(x1, (y1 +i));
        bc_printA(CHAR_VERT);
        mt_gotoXY((x1 + x2) - 1, (y1 + i));
        bc_printA(CHAR_VERT);
    }

    mt_gotoXY(x1, y1);
    bc_printA(CHAR_TL);
    mt_gotoXY((x1 + x2) - 1, y1);
    bc_printA(CHAR_TR);

    mt_gotoXY(x1, y1 + y2 - 1);
    bc_printA(CHAR_DL);
    mt_gotoXY(x1 + x2 - 1, y1 + y2 - 1);
    bc_printA(CHAR_DR);



    return SUCCESS;
}
