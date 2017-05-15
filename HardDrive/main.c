#include <stdio.h>
#include "hd_tr_interface.h"

struct Record {
    uint8_t active;
    uint8_t type;
    tCHS chs_start;
    tLBA l_start;
    tCHS chs_end;
    int32_t sectors;
    tLBA end;
};

struct Table {
    uint8_t full;
    struct Record records[4];
};


void test_g_lba() {
    tLBA lba = 2046;
    tCHS chs;
    tIDECHS idechs;
    tLARGE large;
    g_lba2chs(lba, &chs);
    printf("%d/%d/%d\n", chs.cylinder, chs.head, chs.sector);
    g_chs2lba(chs, &lba);
    printf("%d\n", lba);
    lba = 52864;
    g_lba2idechs(lba, &idechs);
    printf("%d/%d/%d\n", idechs.cylinder, idechs.head, idechs.sector);
    g_idechs2lba(idechs, &lba);
    printf("%d\n", lba);
    lba = 52864;
    g_lba2large(lba, &large);
    printf("%d/%d/%d\n", large.cylinder, large.head, large.sector);
    g_large2lba(large, &lba);
    printf("%d\n", lba);
}

void test_a_lba() {
}

int main() {
    tIDECHS idechs;
    int heads = 0;
    int sectors = 0;
    scanf("%hu%d%d", &idechs.cylinder, &heads, &sectors);
    idechs.head = (uint8_t) (heads);
    idechs.sector = (uint8_t) (sectors);
    uint64_t size = (((uint64_t) idechs.cylinder) * ((uint64_t) idechs.head) * ((uint64_t) idechs.sector) * 512) / (1024 * 1024 * 1024);
    printf("Size is %ld GB\n", size);
    uint8_t was_active = 0;
    tLBA now_at = 1;
    uint32_t table_num = 0;
    struct Table tables[1024];
    int64_t free_size = size;
    for (uint64_t i = 0; i < 1024; ++i) {
        tables[i].full = 0;
    }
    tLBA l_geom;
    g_idechs2lba(idechs, &l_geom);
    const uint8_t types[10] = {0, 0x1, 0x4, 0x5, 0x6, 0x7, 0xc, 0xd, 0x82, 0x83};
    while (1) {
        if (tables[table_num].full >= 4) {
            break;
        }
        int32_t size_to_create = 0;
        printf("Enter size of the section:\n");
        scanf("%d", &size_to_create);
        if (size_to_create == 0) {
            break;
        }
        if (free_size - size_to_create < 0) {
            printf("Section is too big.\n");
            continue;
        }
        free_size -= size_to_create;

        tables[table_num].records[tables[table_num].full].sectors = size_to_create * 1024 * 1024 / 512;
        printf("Choose type: 1.Empty\n2.FAT12\n3.FAT16<32M\n4.Расширенный\n5.MS-DOS FAT16\n");
        printf("6.NTFS\n7.FAT32\n8.FAT16\n9.Linux swap\n10.Linux\n");
        int32_t type = 0;
        scanf("%d", &type);
        while (type < 1 || type > 10) {
            printf("Come again:\n");
            scanf("%d", &type);
        }
        --type;
        tables[table_num].records[tables[table_num].full].type = types[type];
        if (!was_active) {
            printf("Is active? y/n\n");
            char c[10];
            scanf("%10s", c);
            if (c[0] == 'y') {
                was_active = 1;
                tables[table_num].records[tables[table_num].full].active = 1;
            }
        }
        tables[table_num].records[tables[table_num].full].l_start = now_at;
        tLBA tmp = now_at;
        now_at = now_at + tables[table_num].records[tables[table_num].full].sectors;
        tables[table_num].records[tables[table_num].full].end = now_at;
        tCHS chs_geom;
        g_idechs2chs(idechs, &chs_geom);
        a_lba2chs(chs_geom, tables[table_num].records[tables[table_num].full].l_start, &tables[table_num].records[tables[table_num].full].chs_start);
        a_lba2chs(chs_geom, now_at - 1, &tables[table_num].records[tables[table_num].full].chs_end);
        ++tables[table_num].full;
        if (type == 3) {
            now_at = tmp + 2;
            ++table_num;
        }
    }
    printf("Active Start          End         Sectors          Size          Type\n");
    for (uint64_t k = 0; k <= table_num; ++k) {
        for (uint64_t i = 0; i < tables[k].full; ++i) {
            if (tables[k].records[i].active == 1) {
                printf("*      ");
            } else {
                printf("       ");
            }
            printf("%-15d ", tables[k].records[i].l_start);
            printf("%-12d ", tables[k].records[i].end);
            printf("%-17d ", tables[k].records[i].sectors);
            printf("%-14d ", tables[k].records[i].sectors * 512);
            printf("%-4x\n", tables[k].records[i].type);
        }
    }

    return 0;
}