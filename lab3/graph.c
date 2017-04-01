#include "head/graph.h"

int bc_printA(const char *str)
{
    if (write(1, ENTER_ALT_MODE, strlen(ENTER_ALT_MODE)) < 0)
        return EXIT_FAILURE;
    if (write(1, str, strlen(str)) < 0)
        return EXIT_FAILURE;
    if (write(1, EXIT_ALT_MODE, strlen(EXIT_ALT_MODE)) < 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    int row;
    int col;

    if (mt_getscreensize(&row, &col))
        return EXIT_FAILURE;

    if ((x1 < 0) || (y1 < 0) || (x2 < 0) || (y2 < 0) || ((x1 + x2) > col)
        || ((y1 + y2)) > row) {
        return EXIT_FAILURE;
    }
    // X
    for (int i = 1; (x1 + i) < (x1 + x2) - 1; i++) {
        if (mt_gotoXY((x1 + i), y1)) return EXIT_FAILURE;
        if (bc_printA(CHAR_HOR)) return EXIT_FAILURE;
        if (mt_gotoXY((x1 + i), (y1 + y2 - 1))) return EXIT_FAILURE;
        if (bc_printA(CHAR_HOR)) return EXIT_FAILURE;
    }
    //
    for (int i = 1; (y1 + i) < (y1 + y2) - 1; i++) {
        if (mt_gotoXY(x1, (y1 + i))) return EXIT_FAILURE;
        if (bc_printA(CHAR_VERT)) return EXIT_FAILURE;
        if (mt_gotoXY(((x1 + x2) - 1), (y1 + i))) return EXIT_FAILURE;
        if (bc_printA(CHAR_VERT)) return EXIT_FAILURE;
    }

    if (mt_gotoXY(x1, y1)) return EXIT_FAILURE;
    if (bc_printA(CHAR_TL)) return EXIT_FAILURE;
    if (mt_gotoXY(((x1 + x2) - 1), y1)) return EXIT_FAILURE;
    if (bc_printA(CHAR_TR)) return EXIT_FAILURE;

    if (mt_gotoXY(x1, (int) (y1 + y2 - 1))) return EXIT_FAILURE;
    if (bc_printA(CHAR_DL)) return EXIT_FAILURE;
    if (mt_gotoXY((x1 + x2 - 1), (int) (y1 + y2 - 1))) return EXIT_FAILURE;
    if (bc_printA(CHAR_DR)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int bc_printbigchar(int *ch, int x, int y,
                    enum COLORS_TERM fg, enum COLORS_TERM bg)
{
    int maxx, maxy;
    if (mt_getscreensize(&maxy, &maxx)) return EXIT_FAILURE;

    int rows = 8, cols = 8;
    if ((x < 0) || (y < 0) || (fg < 0) || (fg > clr_default) || (bg < 0) ||
        (bg > clr_default) || ((x + cols) > maxx) || ((y + rows)) > maxy) {
        return EXIT_FAILURE;
    }
    if (mt_setbgcolor(bg)) return EXIT_FAILURE;
    if (mt_setfgcolor(fg)) return EXIT_FAILURE;
    int c;
    for (int i = 0; i < rows; i++) {
        if (mt_gotoXY(x, y + i)) return EXIT_FAILURE;
        for (int j = 0; j < cols; j++) {
            if (bc_getbigcharpos(ch, j, i, &c)) return EXIT_FAILURE;
            if (bc_printA((c == 1) ? (ACS_CKBOARD) : (" "))) return EXIT_FAILURE;
        }
    }
    if (mt_setbgcolor(clr_default)) return EXIT_FAILURE;
    if (mt_setfgcolor(clr_default)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int bc_setbigcharpos(int *ch, int x, int y, int value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
        return EXIT_FAILURE;

    pos = ((y <= 3) ? 0 : 1);
    y %= 4;
    if (value == 0)
        ch[pos] &= ~(1 << (y * 8 + x));
    else
        ch[pos] |= 1 << (y * 8 + x);

    return EXIT_SUCCESS;
}

int bc_getbigcharpos(int *ch, int x, int y, int *value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return EXIT_FAILURE;

    pos = (y <= 3) ? 0 : 1;
    y %= 4;
    *value = ((ch[pos] >> (y * 8 + x)) & 0x1);

    return EXIT_SUCCESS;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
    int n, cnt, err;

    err = (int) read(fd, &n, sizeof(int));
    if (err == -1)
        return EXIT_FAILURE;
    cnt = (int) read(fd, big, need_count * sizeof(int) * 2);
    if (cnt == -1)
        return EXIT_FAILURE;
    *count = cnt / (sizeof(int) * 2);
    return EXIT_SUCCESS;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
    int err;

    err = (int) write(fd, &count, sizeof(int));
    if (err == -1)
        return EXIT_FAILURE;
    err = (int) write(fd, big, count * (sizeof(int)) * 2);
    if (err == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
