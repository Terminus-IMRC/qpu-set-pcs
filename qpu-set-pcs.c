#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vc4regmap.h>

#define NUM_PCS 16

static const uint32_t pctr[NUM_PCS] = {
    V3D_PCTR0,
    V3D_PCTR1,
    V3D_PCTR2,
    V3D_PCTR3,
    V3D_PCTR4,
    V3D_PCTR5,
    V3D_PCTR6,
    V3D_PCTR7,
    V3D_PCTR8,
    V3D_PCTR9,
    V3D_PCTR10,
    V3D_PCTR11,
    V3D_PCTR12,
    V3D_PCTR13,
    V3D_PCTR14,
    V3D_PCTR15
};

static const uint32_t pctrs[NUM_PCS] = {
    V3D_PCTRS0,
    V3D_PCTRS1,
    V3D_PCTRS2,
    V3D_PCTRS3,
    V3D_PCTRS4,
    V3D_PCTRS5,
    V3D_PCTRS6,
    V3D_PCTRS7,
    V3D_PCTRS8,
    V3D_PCTRS9,
    V3D_PCTRS10,
    V3D_PCTRS11,
    V3D_PCTRS12,
    V3D_PCTRS13,
    V3D_PCTRS14,
    V3D_PCTRS15
};

static void print_pcs(volatile uint32_t *peri)
{
    int i;

    printf("CTEN: 0x%08x\n", peri[V3D_PCTRE]);
    for (i = 0; i < NUM_PCS; i ++)
        printf("%2d: %2d %10u\n", i, peri[pctrs[i]], peri[pctr[i]]);
}

int main(int argc, char *argv[])
{
    int i;
    volatile uint32_t *peri;

    if (argc - 1 > NUM_PCS) {
        fprintf(stderr, "error: Too many arguments\n");
        exit(EXIT_FAILURE);
    }

    peri = vc4regmap_init();
    if (peri == NULL)
        exit(EXIT_FAILURE);

    if (!is_qpu_enabled(peri)) {
        printf("error: QPU is not enabled\n");
        return vc4regmap_finalize();
    }

    if (argc == 1) {
        print_pcs(peri);
        goto cleanup;
    }

    peri[V3D_PCTRE] = 0;
    peri[V3D_PCTRC] = 0xffff;
    for (i = 0; i < NUM_PCS; i ++) {
        peri[pctrs[i]] = 0;
        peri[pctr[i]] = 0;
    }

    for (i = 0; i < argc - 1; i ++)
        peri[pctrs[i]] = atoi(argv[i + 1]);
    peri[V3D_PCTRE] = 0x80000000 | ((1 << (argc - 1)) - 1);

    print_pcs(peri);

cleanup:
    return vc4regmap_finalize();
}
