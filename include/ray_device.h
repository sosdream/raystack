#ifndef __RAY_DEVICE_H__
#define  __RAY_DEVICE_H__ 1
#include "ray_packet.h"

#ifdef __cplusplus
extern "C" {
#endif
struct __ray_dev_capacity;
struct __ray_dev_status;
struct __ray_dev_class;
struct __ray_device;

typedef struct __ray_dev_capacity ray_dev_capacity_t;
typedef struct __ray_dev_status   ray_dev_status_t;
typedef struct __ray_dev_class    ray_dev_class_t;
typedef struct __ray_device       ray_dev_t;

typedef int (*dev_func_t)(ray_dev_t *, ray_packet_t *);

struct __ray_dev_capacity {

};

struct __ray_dev_status {

};

struct __ray_dev_class {
	dev_func_t input;
	dev_func_t output;
};

struct __ray_device {
	/* Name of the Nic device */
	char *name;
	/* Function of the device */
	ray_dev_class_t class;
	/* Status statistic of the device */
	ray_dev_status_t status;
	/* Capacities of the device */
	ray_dev_capacity_t capacities;
};


#ifdef __cplusplus
}
#endif

#endif //__RAY_DEVICE_H__