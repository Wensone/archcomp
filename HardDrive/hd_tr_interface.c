#include "hd_tr_interface.h"

int g_lba2chs(tLBA lba_geometry, tCHS *chs_geometry) {
    tCHS best = {0, 0, 63};
    for (uint16_t i = 0; i < 256; ++i) {
        for (uint16_t j = 0; j < 1024; ++j) {
            int64_t dif = (int64_t) (lba_geometry) - 63 * i * j;
            int64_t b_dif = (int64_t) (lba_geometry) - 63 * best.cylinder * best.head;
            if (dif >= 0 && dif <= b_dif) {
                best.head = (uint8_t) i;
                best.cylinder = j;
            }
        }
    }
    chs_geometry->cylinder = best.cylinder;
    chs_geometry->head = best.head;
    chs_geometry->sector = 63;
    return 0;
}

int g_lba2large(tLBA lba_geometry, tLARGE *large_geometry) {
    tCHS chs_geometry;
    g_lba2chs(lba_geometry, &chs_geometry);
    g_chs2large(chs_geometry, large_geometry);
    return 0;
}

int g_lba2idechs(tLBA lba_geometry, tIDECHS *idechs_geometry) {
    tIDECHS best = {0, 0, 255};
    for (uint16_t i = 0; i < 256; ++i) {
        for (uint32_t j = 0; j < UINT16_MAX; ++j) {
            int64_t dif = (int64_t) (lba_geometry) - 255 * i * j;
            int64_t b_dif = (int64_t) (lba_geometry) - 255 * best.cylinder * best.head;
            if (dif >= 0 && dif <= b_dif) {
                best.head = (uint8_t) i;
                best.cylinder = (uint16_t) j;
            }
        }
    }
    idechs_geometry->cylinder = best.cylinder;
    idechs_geometry->head = best.head;
    idechs_geometry->sector = 255;
    return 0;
}

int g_chs2large(tCHS chs_geometry, tLARGE *large_geometry) {
    uint32_t pow = 2;
    large_geometry->cylinder = (uint16_t) (chs_geometry.cylinder / pow);
    large_geometry->head = (uint8_t) (chs_geometry.head * pow);
    large_geometry->sector = chs_geometry.sector;
    return 0;
}

int g_chs2lba(tCHS chs_geometry, tLBA *lba_geometry) {
    *lba_geometry = (uint32_t) (chs_geometry.cylinder * chs_geometry.head * chs_geometry.sector);
    return 0;
}

int g_chs2idechs(tCHS chs_geometry, tIDECHS *idechs_geometry) {
    tLBA lba_geom;
    g_chs2lba(chs_geometry, &lba_geom);
    g_lba2idechs(lba_geom, idechs_geometry);
    return 0;
}

int g_large2lba(tLARGE large_geometry, tLBA *lba_geometry) {
    *lba_geometry = large_geometry.cylinder * large_geometry.head * large_geometry.sector;
    return 0;
}

int g_large2chs(tLARGE large_geometry, tCHS *chs_geometry) {
    tLBA lba_geom;
    g_large2lba(large_geometry, &lba_geom);
    g_lba2chs(lba_geom, chs_geometry);
    return 0;
}

int g_large2idechs(tLARGE large_geometry, tIDECHS *idechs_geometry) {
    tLBA lba_geom;
    g_large2lba(large_geometry, &lba_geom);
    g_lba2idechs(lba_geom, idechs_geometry);
    return 0;
}

int g_idechs2lba(tIDECHS idechs_geometry, tLBA *lba_geometry) {
    *lba_geometry = idechs_geometry.cylinder * idechs_geometry.head * idechs_geometry.sector;
    return 0;
}

int g_idechs2chs(tIDECHS idechs_geometry, tCHS *chs_geometry) {
    tLBA lba;
    g_idechs2lba(idechs_geometry, &lba);
    g_lba2chs(lba, chs_geometry);
    return 0;
}

int g_idechs2large(tIDECHS idechs_geometry, tLARGE *large_geometry) {
    tLBA lba;
    g_idechs2lba(idechs_geometry, &lba);
    g_lba2large(lba, large_geometry);
    return 0;
}

int a_lba2chs(tCHS chs_geom, tLBA lba, tCHS *chs) {
    chs->sector = (uint8_t) ((lba % chs_geom.sector) + 1);
    chs->head = (uint8_t) ((lba / chs_geom.sector) % chs_geom.head);
    chs->cylinder = (uint16_t) ((lba / chs_geom.sector) / chs_geom.head);
    return 0;
}

int a_lba2idechs(tIDECHS chs_geom, tLBA lba, tIDECHS *chs) {
    chs->sector = (uint8_t) ((lba % chs_geom.sector) + 1);
    chs->head = (uint8_t) ((lba / chs_geom.sector) % chs_geom.head);
    chs->cylinder = (uint16_t) ((lba / chs_geom.sector) / chs_geom.head);
    return 0;
}

int a_lba2large(tLARGE chs_geom, tLBA lba, tLARGE *chs) {
    chs->sector = (uint8_t) ((lba % chs_geom.sector) + 1);
    chs->head = (uint8_t) ((lba / chs_geom.sector) % chs_geom.head);
    chs->cylinder = (uint16_t) ((lba / chs_geom.sector) / chs_geom.head);
    return 0;
}

int a_chs2lba(tCHS geom, tCHS chs, tLBA *lba) {
    *lba = (uint32_t) (chs.cylinder * geom.head + chs.head * geom.sector + chs.sector - 1);
    return 0;
}

int a_chs2large(tCHS c_geom, tLARGE l_geom, tCHS chs, tLARGE *large) {
    tLBA lba;
    a_chs2lba(c_geom, c_geom, &lba);
    a_lba2large(l_geom, lba, large);
    return 0;
}

int a_chs2idechs(tCHS c_geom, tIDECHS i_geom, tCHS chs, tIDECHS *idechs) {
    tLBA lba;
    a_chs2lba(c_geom, c_geom, &lba);
    a_lba2idechs(i_geom, lba, idechs);
    return 0;
}

int a_idechs2lba(tIDECHS geom, tIDECHS chs, tLBA *lba) {
    *lba = (uint32_t) (chs.cylinder * geom.head + chs.head * geom.sector + chs.sector - 1);
    return 0;
}

int a_idechs2chs(tIDECHS i_geom, tCHS c_geom, tIDECHS idechs, tCHS *chs) {
    tLBA lba;
    a_idechs2lba(i_geom, idechs, &lba);
    a_lba2chs(c_geom, lba, chs);
    return 0;
}

int a_idechs2large(tIDECHS i_geom, tLARGE l_geom, tIDECHS idechs, tLARGE *chs) {
    tLBA lba;
    a_idechs2lba(i_geom, idechs, &lba);
    a_lba2large(l_geom, lba, chs);
    return 0;
}

int a_large2lba(tLARGE geom, tLARGE chs, tLBA *lba) {
    *lba = (uint32_t) (chs.cylinder * geom.head + chs.head * geom.sector + chs.sector - 1);
    return 0;
}

int a_large2chs(tLARGE l_geom, tCHS c_geom, tLARGE large, tCHS *chs) {
    tLBA lba;
    a_large2lba(l_geom, large, &lba);
    a_lba2chs(c_geom, lba, chs);
    return 0;
}

int a_large2idechs(tLARGE l_geom, tIDECHS i_geom, tLARGE large, tIDECHS *chs) {
    tLBA lba;
    a_large2lba(l_geom, large, &lba);
    a_lba2idechs(i_geom, lba, chs);
    return 0;
}
