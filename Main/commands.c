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
    if (!isData(val)) {
        return EXIT_FAILURE;
    }
    
    sc_getData(val, &val);
    char str[16];
    sprintf(str, "Out : %d", val);
    q_add(str);
    printIO();
    
    return EXIT_SUCCESS;
}

int READ(int v) {
    int val;
    mt_gotoXY(1, 29);
    write(STDOUT_FILENO, "Please, enter : ", 16);
    rk_mytermregime(1, 0, 0, 1, 1);
    if (readInt(8, &val)) {
        sc_regSet(FLAG_P, 1);
        rk_mytermregime(0, 0, 1, 0, 1);
        return EXIT_FAILURE;
    }
    rk_mytermregime(0, 0, 1, 0, 1);

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
    if (!isData(getAccum())) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }
    
    int tmp_get_acc;
    sc_getData(getAccum(), &tmp_get_acc);
    val += tmp_get_acc;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
    
    return EXIT_SUCCESS;
}

int SUB(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }

    val = tmp_get_acc - val;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
    return EXIT_SUCCESS;
}

int DIVIDE(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }
    if (!val) {
        sc_regSet(FLAG_0, 1);
        sc_regSet(FLAG_T, 1);
        return EXIT_SUCCESS;
    }

    val = tmp_get_acc / val;
    sc_setData(val, &accumulator);
    return EXIT_SUCCESS;
}

int MUL(int v) {
    int val;

    if (sc_memoryGet(v, &val)) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }
    if (sc_getData(val, &val)) {
        return EXIT_FAILURE;
    }

    val = tmp_get_acc * val;
    if (sc_setData(val, &accumulator)) {
        sc_regSet(FLAG_P, 1);
        sc_setData(0, &accumulator);
    }
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
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }


    if (tmp_get_acc < 0)
        counter = (unsigned) v;
    else ++counter;
    
    return EXIT_SUCCESS;
}

int JZ(int v) {
    if (v < 0 || v >= SIZE) {
        return EXIT_FAILURE;
    }
    int tmp_get_acc;
    if (sc_getData(getAccum(), &tmp_get_acc)) {
        return EXIT_FAILURE;
    }


    if (tmp_get_acc == 0)
        counter = (unsigned) v;
    else ++counter;
    
    return EXIT_SUCCESS;
}

int HALT(int v) {
    char str[32];
    sprintf(str, "Exit(%d)", v);
    q_add(str);
    
    sc_regSet(FLAG_T, 1);
    printIO();
    
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