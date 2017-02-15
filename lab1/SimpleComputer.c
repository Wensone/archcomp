#include "SimpleComputer.h"

uint8_t sc_memoryInit(){
	int i = 0;
	for(i = 0; i < SIZE; i++){
		*(ram + i) = 0 + i;
	}
	return SUCCESS;
}

uint8_t sc_memorySet(uint8_t address, uint16_t value){
	if(address < 0 || address >= SIZE)
		return INCORRECT_MEMORY;

	*(ram + address) = value;

	return SUCCESS;
}

uint8_t sc_memoryGet(uint8_t address, uint16_t *value){
	if(address < 0 || address >= SIZE)
		return INCORRECT_MEMORY;

	*value = *(ram + address);

	return SUCCESS;
}

uint8_t sc_memorySave(char *filename){
	FILE *file = fopen(filename, "wb");
	if(!file) FILE_ERROR;

	fwrite(ram, sizeof(int), SIZE, file);

	fclose(file);
	return SUCCESS;
}

uint8_t sc_memoryLoad(char *filename){
	FILE *file = fopen(filename, "rb");
	if(!file) return FILE_ERROR;

	fread(ram, sizeof(int), SIZE, file);

	fclose(file);
	return SUCCESS;
}

uint8_t sc_regInit(){
	Flags = 0;
	return SUCCESS;
}

uint8_t sc_regSet(uint8_t reg, uint8_t value) {
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
            (reg != FLAG_T) && (reg != FLAG_0)) {
        return INCORRECT_MEMORY;
    }
    if ((value < 0) || (value >  1) ) {
        return  COMMAND_ERROR;
    }

    if (value == 0) {
        Flags &= !reg;
    } else {
        Flags &= reg;
    }
    return SUCCESS;

}

uint8_t sc_regGet(uint8_t reg, uint8_t *value) {
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
        (reg != FLAG_T) && (reg != FLAG_0)  ) {
        return COMMAND_ERROR;
    }
    *value = (int) (Flags & reg);
    //*value >>= (int)log2((double) reg);
    return SUCCESS;
}

uint8_t sc_commandEncode(uint8_t command, uint8_t operand, uint16_t *value) {
    if (command < 0 || command > 127 || operand < 0 || operand > 127) {
        return COMMAND_ERROR;
    }
    int temp = 0x00;
    temp |= command;
    temp <<= 7;
    temp |= operand;
    *value = temp;

    return SUCCESS;
}

uint8_t sc_commandDecode(uint16_t value, uint8_t *command, uint8_t *operand) {
    if (value >> 15 != 0x0) {
        return COMMAND_ERROR;
    }
    *command = (int) (value >> 7);
    *operand = (int) (value & 0177);
    return SUCCESS;
}
