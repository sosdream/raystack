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
#ifndef __RAY_DEVIF_CLASS_H__
#define  __RAY_DEVIF_CLASS_H__ 1
#include "ray_config.h"

#ifdef CONFIG_LINUX
#include <sys/queue.h>
#endif

#include "ray_device.h"
#include "ray_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

void devif_class_register(ray_devif_class_t *devif_class);

ray_devif_class_t *devif_class_get_byname(const ray_s8_t const*class_name);

//#define INIT_CLASS_LIST(head)						\
//RAY_INIT_PRIO(preinit_##head, 101);					\
//static void preinit_##head()(void) {				\
	head = RAY_STAILQ_HEAD_INITIALIZER(head);		\
}
#define INIT_CLASS_LIST(head)												\
static void __attribute__((constructor(101), used)) preinit_##head(void)	\
{																			\
	RAY_STAILQ_INIT(&head);													\
}

#define REGISTER_DEV_CLASS(class)											\
static void __attribute__((constructor(102), used)) preinit_##class(void)	\
{																			\
	devif_class_register(&class);											\
}

#ifdef __cplusplus
}
#endif

#endif //__RAY_DEVIF_CLASS_H__