#include "SimpleComputer.h"

int sc_memoryInit(){
	int i = 0;
	for(i = 0; i < sizeArray; i++){
		*(scmemory + i) = 0 + i;
	}
	return SUCCESS;
}

int sc_memorySet(int address, int value){
	if(address < 0 || address >= sizeArray)
		return INCORRECT_MEMORY;

	*(scmemory + address) = value;

	return SUCCESS;
}

int sc_memoryGet(int address, int *value){
	if(address < 0 || address >= sizeArray)
		return INCORRECT_MEMORY;

	*value = *(scmemory + address);

	return SUCCESS;
}

int sc_memorySave(char *filename){
	FILE *file = fopen(filename, "wb");
	if(!file) FILE_ERROR;

	fwrite(scmemory, sizeof(int), sizeArray, file);

	fclose(file);
	return SUCCESS;
}

int sc_memoryLoad(char *filename){
	FILE *file = fopen(filename, "rb");
	if(!file) return FILE_ERROR;

	fread(scmemory, sizeof(int), sizeArray, file);

	fclose(file);
	return SUCCESS;
}

int sc_regInit(){
	Flags = 0;
	return SUCCESS;
}

int sc_regSet(int reg, int value) {
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

int sc_regGet(int reg, int *value) {
    if ((reg != FLAG_E) && (reg != FLAG_M) && (reg != FLAG_P) &&
        (reg != FLAG_T) && (reg != FLAG_0)  ) {
        return COMMAND_ERROR;
    }
    *value = (int) (Flags & reg);
    //*value >>= (int)log2((double) reg);
    return SUCCESS;
}

int sc_commandEncode(int command, int operand, int *value) {
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

int sc_commandDecode(int value, int *command, int *operand) {
    if (value >> 15 != 0x0) {
        return COMMAND_ERROR;
    }
    *command = (int) (value >> 7);
    *operand = (int) (value & 0xFF);
    return SUCCESS;
}
