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
#include <ray_errno.h>
#include <ray_device.h>
#include <ray_string.h>
#include <ray_list.h>
#include <ray_devif_class.h>

/* Save all register device class */
RAY_STAILQ_HEAD(, ray_devif_class_t) ray_class_head;

ray_bool_t devif_class_exist(ray_devif_class_t *devif_class)
{
	ray_bool_t ret = FALSE;
	ray_devif_class_t *class;

	RAY_STAILQ_FOREACH(class, &ray_class_head, class_list) {
		if (ray_strcmp(class->name, devif_class->name) == 0) {
			ret = TRUE;
			break;
		}
	}
	return ret;
}

ray_devif_class_t *devif_class_get_byname(const ray_s8_t const *class_name)
{
	ray_devif_class_t *class;

	if (class_name == NULL) {
		errno = EINVAL;
		goto no_found;
	}

	RAY_STAILQ_FOREACH(class, &ray_class_head, class_list) {
		if (ray_strcmp(class->name, class_name) == 0) {
			return class;
		}
	}

no_found:
	return NULL;
}

void devif_class_register(ray_devif_class_t *devif_class)
{
	/* Invalid parameter check */
	if(devif_class == NULL) {
		RAY_LOG(ERR, "Invalid Parameter!\n");
		errno = EINVAL;
		return;
	}

	if (devif_class_exist(devif_class)) {
		errno = EEXIST;
		return;
	}

	/* Init the class */
	devif_class->init();

	/* Insert the tail list */
	RAY_STAILQ_INSERT_TAIL(&ray_class_head, devif_class, class_list);
}

INIT_CLASS_LIST(ray_class_head);