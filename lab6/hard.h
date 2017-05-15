#ifndef ARCH_HARD_H
#define ARCH_HARD_H

struct TCHS {
	int Cylinder;
	int Head;
	int Sector;
};

struct TLBA {
	unsigned int lba;
};

struct TLARGE {
	int Cylinder;
	int Head;
	int Sector;
};

struct TIDECHS {
	int Cylinder;
	int Head;
	int Sector;
};

typedef struct TCHS tCHS;
typedef struct TLBA tLBA;
typedef struct TLARGE tLARGE;
typedef struct TIDECHS tIDECHS;

int g_lba2chs(tLBA LBA, tCHS *CHS);

int g_lba2large(tLBA LBA, tLARGE *LARGE);

int g_lba2idechs(tLBA LBA, tIDECHS *IDECHS);

int g_chs2large(tCHS CHS, tLARGE *LARGE);

int g_chs2lba(tCHS CHS, tLBA *LBA);

int g_chs2idechs(tIDECHS IDECHS, tLBA *LBA);

int g_large2chs(tLARGE LARGE, tCHS *CHS);

int g_large2idechs(tLARGE LARGE, tIDECHS *IDECHS);

int g_large2lba(tLARGE LARGE, tLBA *LBA);

int g_idechs2chs(tIDECHS IDECHS, tCHS *CHS);

int g_idechs2lagre(tIDECHS IDECHS, tLARGE *LARGE);

int g_idechs2lba(tIDECHS IDECHS, tLBA *LBA);

int a_lba2chs(tCHS geometry, tLBA LBA, tCHS *CHS);

int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE *LARGE);

int a_lba2idechs(tIDECHS geometry, tLBA LBA, tIDECHS *IDECHS);

int a_chs2lba(tCHS geometry, tCHS CHS, tLBA *LBA);

int a_large2lba(tLARGE geometry, tLARGE LARGE, tLBA *LBA);

int a_idechs2lba(tIDECHS geometry, tIDECHS IDECHS, tLBA *LBA);

int a_large2chs(tLARGE geometry1, tCHS geometry2, tLARGE LARGE, tCHS *CHS);

int a_large2idechs(tLARGE geometry1, tIDECHS geometry2, tLARGE LARGE, tIDECHS *IDECHS);

int a_chs2large(tCHS geometry1, tLARGE geometry2, tCHS CHS, tLARGE *LARGE);

int a_idechs2large(tIDECHS geometry1, tLARGE geometry2, tIDECHS IDECHS, tLARGE *LARGE);

int a_chs2idechs(tCHS geometry1, tIDECHS geometry2, tCHS CHS, tIDECHS *IDECHS);

int a_idechs2chs(tIDECHS geometry1, tCHS geometry2, tIDECHS IDECHS, tCHS *CHS);

#endif //ARCH_HARD_H
