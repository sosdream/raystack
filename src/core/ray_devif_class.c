#include <ray_log.h>
#include <ray_errno.h>
#include <ray_device.h>
#include <ray_devif_class.h>

#define RAY_TAILQ_NAMESIZE 32
struct ray_tailq_devclass_elem {
	TAILQ_ENTRY(ray_tailq_devclass_elem) next;
	ray_devif_class_t *dev_class;
};

TAILQ_HEAD(ray_tailq_devclass_head, ray_tailq_devclass_elem);


struct ray_tailq_devif_elem {
	TAILQ_ENTRY(ray_tailq_devif_elem) next;
	ray_devif_t *dev_if;
};

TAILQ_HEAD(ray_tailq_devif_head, ray_tailq_devif_elem);

static struct ray_tailq_devclass_head devclasses_head =
					TAILQ_HEAD_INITIALIZER(devclasses_head);

ray_s32_t devclass_exist(ray_devif_class_t *devif_class)
{
	ray_s32_t ret = 0;
	struct ray_tailq_devclass_elem *devclass = NULL;

	TAILQ_FOREACH(devclass, &devclasses_head, next) {
		if (ray_strcmp(devclass->type, devif_class->type) == 0) {
			ret = 1;
		}
	}
	return ret;
}

ray_devif_class_t *
get_devif_class(ray_consts8_t *class_name)
{
	struct ray_tailq_devclass_elem *devclass = NULL;

	TAILQ_FOREACH(devclass, &devclasses_head, next) {
		RAY_LOG("","", "%s\n", devclass->type);
	}
}

void register_devif_class(ray_devif_class_t *devif_class)
{
	struct ray_tailq_devclass_elem *new_elem;
	/* Invalid parameter check */
	if(devif_class == NULL) {
		RAY_LOG("", "", "Invalid Parameter!\n");
		return -EINVAL;
	}

	if (devclass_exist(devif_class))
		return -EEXIST;

	new_elem = ray_malloc();
}