#include "SimpleComputer.h"

void print(int i, int n){
	for(; i < n; i++)
		printf("%d ", scmemory[i]);
}

int main(){
	int value;
	int command;
	int operand;
	char *fileSave = "memSave";
	char *fileLoad = fileSave;

	sc_memoryInit();
	printf("Mem init\n");

	sc_memorySet(0, 6);
	printf("Mem set. Address: 0. Value: 6\n");

	sc_memoryGet(0, &value);
	printf("Value after using memGet: %d\n", value);

	sc_memorySave(fileSave);
	printf("Mem has been save in file %s\n", fileSave);

	sc_memoryLoad(fileLoad);
	printf("Mem has been load from file %s\n", fileLoad);

	sc_regInit();
	printf("Reg init\n");

	sc_regSet(FLAG_M, 1);
	printf("Flag init 1\n");

	sc_regGet(FLAG_M, &value);
	printf("FLAG set value %d\n", value);

	command = 0x33;
	operand = 59;
	sc_commandEncode(command, operand, &value);
	printf("Encode Command: 0x33 and Operand: 59 in value: %d\n", value);

	sc_commandDecode(value, &command, &operand);
	printf("Decode Comand: %d. Operand: %d\n", command, operand);


	return 0;
}
