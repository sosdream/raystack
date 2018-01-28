#include <ray_log.h>
#include <ray_device.h>
#include <ray_string.h>
#include <ray_memory.h>

/* Macro Define */
#define DEVICE_NAME_LENGTH		128

static ray_devif_ops_t virt_device_ops;

ray_devif_t *virt_internal_create_dev(ray_devif_class_t *devif_class)
{
	ray_devif_t *ifdev;
	ray_s8_t dev_name[DEVICE_NAME_LENGTH];

	ifdev = ray_malloc(sizeof(ray_devif_t), RAY_CACHELINE_ALIGN);
	/* The device name is it's class name + index */
	ray_sprintf(dev_name, "%s-%d",
					 devif_class->name, devif_class->devif_count++);
	ifdev->name = ray_strdup(dev_name);
	ifdev->ops  = &virt_device_ops;

	return ifdev;
}

/* Device oprations */
static ray_s32_t virt_start(ray_devif_t *dev, ray_u32_t core_id, dev_start_loop_t loop)
{
	RAY_LOG(INFO, "%s has started!\n", dev->name);
	/* Set CPU affinity */
	loop(dev);
	return 0;
}

static ray_s32_t virt_input(ray_devif_t *dev, ray_packet_t *pkt)
{
	static size_t counter = 0;
	RAY_LOG(INFO, "packet len: %d %llu\n", pkt->data_len, counter++);
	return 0;
}

static ray_s32_t virt_output(ray_devif_t *dev, ray_packet_t *pkt)
{
	return 0;
}

static ray_devif_ops_t virt_device_ops = {
	.if_start = virt_start,
	.if_input = virt_input,
	.if_output = virt_output,
};