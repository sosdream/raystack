#include <ray_log.h>
#include <ray_types.h>
#include <ray_string.h>
#include <ray_device.h>
#include <ray_devif_class.h>

/* Macro Define */
#define VIRT_DEVIF_CLASS        "virt"

ray_devif_t *virt_internal_create_dev(ray_devif_class_t *devif_class);
static ray_devif_class_t virt_device_class;

static ray_s32_t virt_init(void)
{
	/* Init the platform */
	RAY_LOG(INFO, "This is init!\n");
	return 0;
}

static ray_devif_t *virt_create_dev(void)
{
	return virt_internal_create_dev(&virt_device_class);
}

static ray_devif_t *virt_create_dev_byport(ray_s32_t portid)
{
	return NULL;
}



static ray_devif_class_t virt_device_class = {
	.name = VIRT_DEVIF_CLASS,
	.init = virt_init,
	.create_dev = virt_create_dev,
	.create_dev_byport = virt_create_dev_byport,
	.destroy_dev = NULL,
	.destroy_all_dev = NULL,

	.devif_count = 0,
	.head_devs  = RAY_STAILQ_HEAD_INITIALIZER(virt_device_class.head_devs),
};

REGISTER_DEV_CLASS(virt_device_class);