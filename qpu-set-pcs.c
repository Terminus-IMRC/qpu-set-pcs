#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mailbox.h>
#include <v3d.h>

#define NUM_PCS 16

static const v3d_field_name_t pctr[NUM_PCS] = {
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

static const v3d_field_name_t pctrs[NUM_PCS] = {
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

static void print_pcs(uint32_t *vp)
{
	int i;

	printf("CTEN: 0x%08x\n", v3d_read(vp, V3D_CTEN));
	for (i = 0; i < NUM_PCS; i ++)
		printf("%2d: %2d %10u\n", i, v3d_read(vp, pctrs[i]), v3d_read(vp, pctr[i]));
}

int main(int argc, char *argv[])
{
	int i;
	uint32_t *vp = NULL;

	if (argc - 1 > NUM_PCS) {
		fprintf(stderr, "%s:%d: error: Too many arguments\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	v3d_init();
	vp = mapmem_cpu(BUS_TO_PHYS(v3d_peripheral_addr()), V3D_LENGTH);

	if (argc == 1) {
		print_pcs(vp);
		goto cleanup;
	}

	v3d_write(vp, V3D_CTEN, 0);
	v3d_write(vp, V3D_CTCLR, 0xffff);
	for (i = 0; i < NUM_PCS; i ++) {
		v3d_write(vp, pctrs[i], 0);
		v3d_write(vp, pctr[i], 0);
	}

	for (i = 0; i < argc - 1; i ++)
		v3d_write(vp, pctrs[i], atoi(argv[i + 1]));
	v3d_write(vp, V3D_CTEN, 0x80000000 | ((1 << (argc - 1)) - 1));

	print_pcs(vp);

cleanup:
	unmapmem_cpu(vp, V3D_LENGTH);
	v3d_finalize();

	return 0;
}
