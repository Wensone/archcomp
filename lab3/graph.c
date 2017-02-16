#include "graph.h"

uint8_t bc_printA(const char *str){
	printf("\E(0%s\E(B", str);
	/*write(1, ENTER_ALT_MODE, strlen(ENTER_ALT_MODE));
	write(1, str, strlen(str));
	write(1, EXIT_ALT_MODE, strlen(EXIT_ALT_MODE));
	*/
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

uint8_t bc_printbigchar(uint32_t* ch, uint16_t x, uint16_t y,
	 					enum COLORS_TERM fg, enum COLORS_TERM bg)
{
	uint16_t maxx, maxy;
	mt_getscreensize(&maxy, &maxx);

	uint8_t rows = 8, cols = 8;
	if((x < 0) || (y < 0) || (fg < 0) || (fg > clr_default) || (bg < 0) ||
	 	(bg > clr_default) || ((x + cols) > maxx) || ((y + rows)) > maxy) {
        return ERROR;
    }
	char s[cols];
	s[cols - 1] = '\0';
	for (uint8_t i = 0; i < rows; i++) {
		uint8_t current = i & 0x4;
		uint8_t bit;
		for (uint8_t j = 0; j < cols; j++) {
			bit = (ch[current] >> ((i % 4) * 8 + j)) & 1;
			if (bit == 0)
				s[j] = ' ';
			else
				s[j] = ACS_CKBOARD;
		}
		mt_gotoXY(x, y + i);
		bc_printA(s);
	}
	return SUCCESS;
}

uint8_t bc_setbigcharpos(uint32_t *ch, uint8_t x, uint8_t y, uint8_t value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
		return ERROR;

	pos = (y <= 3) ? 0 : 1;
	y %= 4;
	if (value == 0)
		ch[pos] &= ~(1 << (y * 8 + x));
	else
		ch[pos] |= 1 << (y * 8 + x);

	return SUCCESS;
}

uint8_t bc_getbigcharpos(uint32_t *ch, uint8_t x, uint8_t y, uint8_t *value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
		return ERROR;

	pos = (y <= 3) ? 0 : 1;
	y %= 4;
	*value = (ch[pos] >> (y * 8 + x)) & 0x1;

	return SUCCESS;
}

uint8_t bc_bigcharread(int fd, uint32_t *big, int need_count, int *count)
{
	int n, cnt, err;

	err = read(fd, &n, sizeof(n));
	if (err == -1 || (err != sizeof(n)))
		return ERROR;
	cnt = read(fd, big, need_count * sizeof(uint32_t) * 2);
	if (cnt == -1)
		return ERROR;
	*count = cnt / (sizeof(int) * 2);

	return SUCCESS;
}

uint8_t bc_bigcharwrite(int fd, uint32_t *big, int count)
{
	int err;

	err = write(fd, &count, sizeof(count));
	if (err == -1)
		return ERROR;
	err = write(fd, big, count * (sizeof(uint32_t)) * 2);
	if (err == -1)
		return ERROR;

	return 0;
}
