/*-
 * Copyright (c) 2018, Honglin Xiao
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef __RAY_DEVICE_H__
#define  __RAY_DEVICE_H__ 1
#include "ray_packet.h"
#include "ray_list.h"

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
	ray_consts8_t *name;
	ray_s32_t    (*init)(void);
	ray_devif_t *(*create_dev)(void);
	ray_devif_t *(*create_dev_byport)(ray_s32_t);
	ray_s32_t    (*start)(ray_devif_t *);
	ray_s32_t    (*recv)(ray_devif_t *, ray_packet_t *);
	ray_s32_t    (*send)(ray_devif_t *, ray_packet_t *);

	RAY_STAILQ_ENTRY(ray_devif_class_t) class_list;
	RAY_STAILQ_HEAD(, ray_devif_t) head_devs;
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

	RAY_STAILQ_ENTRY(ray_devif_t) attach_list;
};

#ifdef __cplusplus
}
#endif

#endif //__RAY_DEVICE_H__