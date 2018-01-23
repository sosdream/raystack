#ifndef __RAY_ACTION_H__
#define  __RAY_ACTION_H__ 1

#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _ray_action_e {
	RAY_ACTION_NONE,
	RAY_ACTION_DROP,
	RAY_ACTION_NEXT,
	RAY_ACTION_SOCKET,
} ray_action_e;

struct __ray_action {
	ray_action_e action;
};

typedef struct __ray_action ray_action_t;
#ifdef __cplusplus
}
#endif

#endif //__RAY_ACTION_H__