#include "head/commands.h"
#include "../lab1/head/SimpleComputer.h"
#include "head/terminal.h"

/*
    м - выход за границы
    0 - деление на 0
    п - переполнение
*/

/* Ввод\вывод */
int WRITE(int v) {
    int val;
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (isData(val)) {
        return EXIT_FAILURE;
    }
    
    sc_getData(val, &val);
    char str[8];
    sprintf(str, "%d", val);
    q_add(str);
    printIO();
    
    return EXIT_SUCCESS;
}

int READ(int v) {
    int val;
    mt_gotoXY(1, 29);
    
    if (readInt(8, &val)) {
        return EXIT_FAILURE;
    }
    
    sc_setData(val, &val);
    sc_memorySet(v, val);
    
    return EXIT_SUCCESS;
}

/* Операции загрузки\выгрузки в аккумулятор */
int LOAD(int v) {
    if (sc_memoryGet(v, &accumulator))
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int STORE(int v) {
    if (sc_memorySet(v, getAccum())) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/* Арифметика */
int cADD(int v) {
    int val;
    
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
    
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val = val + tmp_get_acc;
    
    return EXIT_SUCCESS;
}

int SUB(int v) {
    int val;
    
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
    
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val = val - tmp_get_acc;
}

int DIVIDE(int v) {
    int val;
    
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
    
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val = val / tmp_get_acc;
}

int MUL(int v) {
    int val;
    
    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val = val * tmp_get_acc;
    setAccum(val);
    
    return EXIT_SUCCESS;
}

/* ЦУ */
int JUMP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    counter = (unsigned) v;
    
    return EXIT_SUCCESS;
}

int JNEG(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    
    if (tmp_get_acc < 0)
        counter = (unsigned) v;
    
    return EXIT_SUCCESS;
}

int JZ(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    
    if (tmp_get_acc == 0)
        counter = (unsigned) v;
    
    return EXIT_SUCCESS;
}

int HALT(int v) {
    char str[8];
    sprintf(str, "%d", v);
    q_add(str);
    
    sc_regSet(FLAG_T, 1);
    
    return EXIT_SUCCESS;
}

/* УЗЕРС */
int NOT(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    tmp_get_acc = ~tmp_get_acc;
    sc_memorySet(v, tmp_get_acc);
    
    return EXIT_SUCCESS;
}

int AND(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    
    tmp_get_acc = tmp_get_acc & tmp_get_dat;
    
    if (sc_setData(tmp_get_acc, &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_acc);
    
    return EXIT_SUCCESS;
}

int OR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    
    tmp_get_acc = tmp_get_acc | tmp_get_dat;
    
    if (sc_setData(tmp_get_acc, &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_acc);
    
    return EXIT_SUCCESS;
}

int XOR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    
    tmp_get_acc = tmp_get_acc ^ tmp_get_dat;
    
    if (sc_setData(tmp_get_acc, &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_acc);
    
    return EXIT_SUCCESS;
}

int JNS(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    
    if (tmp_get_acc > 0)
        counter = (unsigned) v;
    
    return EXIT_SUCCESS;
}

int JC(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_flg;
    if (sc_regGet(FLAG_P, &tmp_get_flg)) {
        return EXIT_FAILURE;
    }
    if (tmp_get_flg)
        counter = (unsigned) v;
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int JNC(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_flg;
    if (sc_regGet(FLAG_P, &tmp_get_flg)) {
        return EXIT_FAILURE;
    }
    if (!tmp_get_flg)
        counter = (unsigned) v;
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int JP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    if (tmp_get_acc % 2 == 0)
        counter = (unsigned) v;
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int JNP(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    if (isData(getAccum())) {
        return EXIT_SUCCESS;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    if (tmp_get_acc % 2 == 1)
        counter = (unsigned) v;
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int CHL(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    tmp_get_dat <<= 1;
    
    if (sc_setData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_dat);
    
    return EXIT_SUCCESS;
}

int SHR(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (sc_getData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    tmp_get_dat >>= 1;
    
    if (sc_setData(tmp_get_dat, &tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_dat);
    
    return EXIT_SUCCESS;
}

// ЦИКЛИЧЕСКОЕ дерьмо
int RCL(int v) {
    return 0;
}

// ЦИКЛИЧЕСКОЕ дерьмо
int RCR(int v) {
    return 0;
}

int NEG(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_dat;
    sc_memoryGet(v, &tmp_get_dat);
    
    if (isData(tmp_get_dat)) {
        return EXIT_FAILURE;
    }
    
    setAccum(tmp_get_dat);
    
    return EXIT_SUCCESS;
}

// 0 <= getAccum < 100 - address