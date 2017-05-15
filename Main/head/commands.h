#ifndef ARCH_COMMANDS_H
#define ARCH_COMMANDS_H

int ALU(int command, int operand);

void CU();

int c_read(int v);

int c_write(int v);

int c_load(int v);

int STORE(int v);

int ADD(int v);

int SUB(int v);

int DIVIDE(int v);

int MUL(int v);

int JUMP(int v);

int JNEG(int v);

int JZ(int v);

int HALT(int v);

int NOT(int v);

int AND(int v);

int OR(int v);

int XOR(int v);

int JNS(int v);

int JC(int v);

int JNC(int v);

int JP(int v);

int JNP(int v);

int CHL(int v);

int SHR(int v);

int RCL(int v);

int RCR(int v);

int NEG(int v);

int ADDC(int v);

int SUBC(int v);

int LOGLC(int v);

int LOGRC(int v);

int RCCL(int v);

int RCCR(int v);

int MOVA(int v);

int MOVR(int v);

int MOVCA(int v);

int MOVCR(int v);


#endif //ARCH_COMMANDS_H
