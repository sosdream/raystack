#include <ray_log.h>
#include <ray_types.h>
#include <ray_device.h>
#include <ray_devif_class.h>

static ray_s32_t virt_init(void)
{
	/* Init the platform */
	RAY_LOG(INFO, "This is init!\n");
	return 0;
}

static ray_devif_t *virt_create_dev(void)
{
	return NULL;
}

static ray_devif_t *virt_create_dev_byport(ray_s32_t portid)
{
	return NULL;
}

static ray_s32_t virt_start(ray_devif_t *dev)
{
	return 0;
}

static ray_s32_t virt_recv(ray_devif_t *dev, ray_packet_t *pkt)
{
	return 0;
}

static ray_s32_t virt_send(ray_devif_t *dev, ray_packet_t *pkt)
{
	return 0;
}

static ray_devif_class_t virt_device_class = {
	.name = "virt",
	.init = virt_init,
	.create_dev = virt_create_dev,
	.create_dev_byport = virt_create_dev_byport,
	.start = virt_start,
	.recv = virt_recv,
	.send = virt_send,

	.head_devs  = RAY_STAILQ_HEAD_INITIALIZER(virt_device_class.head_devs),
};

REGISTER_DEV_CLASS(virt_device_class);