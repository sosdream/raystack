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

typedef struct __ray_dev_capacity ray_devif_capacity_t;
typedef struct __ray_dev_status   ray_devif_status_t;
typedef struct __ray_dev_class    ray_devif_class_t;
typedef struct __ray_device       ray_devif_t;

struct __ray_dev_capacity {
	ray_u32_t mtu;
};

struct __ray_dev_status {
	/* rx status */
	ray_u64_t rx_in;
	ray_u64_t rx_errors;
	/* tx status */
	ray_u64_t tx_out;
	ray_u64_t tx_errors;
};

struct __ray_dev_class {
	ray_consts8_t *type;
	struct ray_tailq_devif_head devifs;
	ray_s32_t    (*init)(void);
	ray_devif_t *(*create_dev)(void);
	ray_devif_t *(*create_dev_byport)(ray_s32_t portid);
	ray_s32_t    (*start)(ray_devif_t *);
	ray_s32_t    (*recv)(ray_devif_t *, ray_packet_t *);
	ray_s32_t    (*send)(ray_devif_t *, ray_packet_t *);
};

struct __ray_device {
	/* Name of the Nic device */
	ray_s8_t *name;
	/* Identify the nic device */
	ray_s32_t dev_id;
	/* Function of the device */
	ray_devif_class_t *class;

	/* Status statistic of the device */
	ray_devif_status_t status;
	/* Capacities of the device */
	ray_devif_capacity_t capacities;
};


#ifdef __cplusplus
}
#endif

#endif //__RAY_DEVICE_H__