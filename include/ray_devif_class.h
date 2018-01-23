#ifndef __RAY_DEVIF_CLASS_H__
#define  __RAY_DEVIF_CLASS_H__ 1
#include "ray_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ray_tailq_devif_head;

ray_devif_class_t *
get_devif_class(ray_consts8_t *class_name);

#ifdef __cplusplus
}
#endif

#endif //__RAY_DEVIF_CLASS_H__