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
	RAY_LOG(INFO, "virt device class init!\n");
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