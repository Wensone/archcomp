#include "SimpleComputer.h"

uint8_t sc_memoryInit(){
	for (int i = 0; i < 100; i++) *(ram + i) = 0;
	return SUCCESS_SC;
}

uint8_t sc_memorySet(uint8_t address, uint16_t value){
	if(address < 0 || address >= SIZE)
		return INCORRECT_MEMORY;
	*(ram + address) = value;

	return SUCCESS_SC;
}

uint8_t sc_memoryGet(uint8_t address, uint16_t *value){
	if(address < 0 || address >= SIZE)
		return INCORRECT_MEMORY;

	*value = *(ram + address);

	return SUCCESS_SC;
}

uint8_t sc_memorySave(char *filename){
	FILE *file = fopen(filename, "wb");
	if(!file) FILE_ERROR;

	fwrite(ram, sizeof(int), SIZE, file);

	fclose(file);
	return SUCCESS_SC;
}

uint8_t sc_memoryLoad(char *filename){
	FILE *file = fopen(filename, "rb");
	if(!file) return FILE_ERROR;

	fread(ram, sizeof(int), SIZE, file);

	fclose(file);
	return SUCCESS_SC;
}

uint8_t sc_regInit(){
	Flags = 0;
	return SUCCESS_SC;
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
    return SUCCESS_SC;

}

uint8_t sc_regGet(uint8_t reg, uint8_t *value) {
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
        (reg != FLAG_T) && (reg != FLAG_0)  ) {
        return COMMAND_ERROR;
    }
    *value = (uint8_t) (Flags & reg);
    //*value >>= (int)log2((double) reg);
    return SUCCESS_SC;
}

uint8_t sc_commandEncode(uint8_t command, uint8_t operand, uint16_t *value) {
    if (command < 0 || command > 127 || operand < 0 || operand > 127) {
        return COMMAND_ERROR;
    }
    uint16_t temp = 0x00;
    temp |= command;
    temp <<= 7;
    temp |= operand;
    *value = temp;

    return SUCCESS_SC;
}

uint8_t sc_commandDecode(uint16_t value, uint8_t *command, uint8_t *operand) {
    if (value >> 14 != 0x0) {
        return COMMAND_ERROR;
    }
    *command = (uint8_t) (value >> 7);
    *operand = (uint8_t) (value & 0177);
    return SUCCESS_SC;
}
