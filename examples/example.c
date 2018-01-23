#include <stdio.h>
#include "ray_device.h"
#include <ray_devif_class.h>

int main()
{
	ray_devif_t *devif;
	ray_devif_class_t *dpdk_class = get_devif_class("dpdk");

	dpdk_class->init();
	devif = dpdk_class->create_dev();
	dpdk_class->start(devif);

	return 0;
}