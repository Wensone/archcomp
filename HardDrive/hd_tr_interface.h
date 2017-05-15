#include <stdint.h>

#ifndef LAB_7_HD_TR_INTERFACE_H
#define LAB_7_HD_TR_INTERFACE_H

typedef struct {
    uint16_t cylinder;
    uint8_t head;
    uint8_t sector;
} tCHS;

typedef struct {
    uint16_t cylinder;
    uint8_t head;
    uint8_t sector;
} tLARGE;

typedef struct {
    uint16_t cylinder;
    uint8_t head;
    uint8_t sector;
} tIDECHS;

typedef uint32_t tLBA;

int g_lba2chs(tLBA lba_geometry, tCHS *chs_geometry);

int g_lba2large(tLBA lba_geometry, tLARGE *large_geometry);

int g_lba2idechs(tLBA lba_geometry, tIDECHS *idechs_geometry);


int g_chs2large(tCHS chs_geometry, tLARGE *large_geometry);

int g_chs2lba(tCHS chs_geometry, tLBA *lba_geometry);

int g_chs2idechs(tCHS chs_geometry, tIDECHS *idechs_geometry);


int g_large2chs(tLARGE large_geometry, tCHS *chs_geometry);

int g_large2lba(tLARGE large_geometry, tLBA *lba_geometry);

int g_large2idechs(tLARGE large_geometry, tIDECHS *idechs_geometry);


int g_idechs2lba(tIDECHS idechs_geometry, tLBA *lba_geometry);

int g_idechs2chs(tIDECHS idechs_geometry, tCHS *chs_geometry);

int g_idechs2large(tIDECHS idechs_geometry, tLARGE *large_geometry);


int a_lba2chs(tCHS chs_geom, tLBA lba, tCHS *chs);

int a_lba2idechs(tIDECHS chs_geom, tLBA lba, tIDECHS *chs);

int a_lba2large(tLARGE chs_geom, tLBA lba, tLARGE *chs);


int a_chs2lba(tCHS geom, tCHS chs, tLBA *lba);

int a_chs2large(tCHS c_geom, tLARGE l_geom, tCHS chs, tLARGE *large);

int a_chs2idechs(tCHS c_geom, tIDECHS i_geom, tCHS chs, tIDECHS *idechs);


int a_idechs2lba(tIDECHS geom, tIDECHS chs, tLBA *lba);

int a_idechs2chs(tIDECHS i_geom, tCHS c_geom, tIDECHS idechs, tCHS *chs);

int a_idechs2large(tIDECHS i_geom, tLARGE l_geom, tIDECHS idechs, tLARGE *chs);


int a_large2lba(tLARGE geom, tLARGE chs, tLBA *lba);

int a_large2chs(tLARGE l_geom, tCHS c_geom, tLARGE large, tCHS *chs);

int a_large2idechs(tLARGE l_geom, tIDECHS i_geom, tLARGE large, tIDECHS *chs);

#endif
