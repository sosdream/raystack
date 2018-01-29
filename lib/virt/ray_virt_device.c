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
#include <ray_log.h>
#include <ray_device.h>
#include <ray_string.h>
#include <ray_memory.h>

/* Macro Define */
#define DEVICE_NAME_LENGTH		128

static ray_devif_ops_t virt_device_ops;

ray_devif_t *virt_internal_create_dev(ray_devif_class_t *devif_class)
{
	ray_devif_t *ifdev;
	ray_s8_t dev_name[DEVICE_NAME_LENGTH];

	ifdev = ray_malloc(sizeof(ray_devif_t), RAY_CACHELINE_ALIGN);
	/* The device name is it's class name + index */
	ray_sprintf(dev_name, "%s-%d",
					 devif_class->name, devif_class->devif_count++);
	ifdev->name = ray_strdup(dev_name);
	ifdev->ops  = &virt_device_ops;

	return ifdev;
}

/* Device oprations */
static ray_s32_t virt_start(ray_devif_t *dev, ray_u32_t core_id, dev_start_loop_t loop)
{
	RAY_LOG(INFO, "%s has started!\n", dev->name);
	/* Set CPU affinity */
	loop(dev);
	return 0;
}

static ray_s32_t virt_input(ray_devif_t *dev, ray_packet_t *pkt)
{
	static size_t counter = 0;
	RAY_LOG(INFO, "packet len: %d %llu\n", pkt->data_len, counter++);
	return 0;
}

static ray_s32_t virt_output(ray_devif_t *dev, ray_packet_t *pkt)
{
	return 0;
}

static ray_devif_ops_t virt_device_ops = {
	.if_start = virt_start,
	.if_input = virt_input,
	.if_output = virt_output,
};