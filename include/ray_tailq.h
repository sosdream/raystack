#ifndef __RAY_TAILQ_H__
#define  __RAY_TAILQ_H__ 1

#include <sys/queue.h>
#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ray_tailq_entry {
	TAILQ_ENTRY(ray_tailq_entry) next;
	void *data;
};

#ifdef __cplusplus
}
#endif

#endif //__RAY_ACTION_H__