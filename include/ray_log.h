#ifndef __RAY_LOG_H__
#define  __RAY_LOG_H__ 1

#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RAY_LOG(l, t, ...) printf(__VA_ARGS__);


#ifdef __cplusplus
}
#endif

#endif //__RAY_LOG_H__