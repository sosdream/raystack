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
#ifndef __RAY_PROTO_H__
#define  __RAY_PROTO_H__ 1

#include "ray_config.h"
#include <ray_types.h>
#include <ray_list.h>
#include <ray_device.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __ray_protocol;

typedef struct __ray_protocol ray_protocol_t;

struct __ray_protocol {
	ray_s32_t proto_id;
	ray_s8_t *proto_desc;
	ray_s32_t    (*proto_input)(ray_devif_t *, ray_packet_t *);
	ray_s32_t    (*proto_output)(ray_devif_t *, ray_packet_t *);
	RAY_STAILQ_ENTRY(ray_protocol_t) proto_list;
};

void proto_register(ray_protocol_t *protocol);
ray_protocol_t *get_protocol_byname(const ray_s8_t const *proto_name);

#define INIT_PROTOCOL_LIST(head)											\
static void __attribute__((constructor(101), used)) preinit_##head(void)	\
{																			\
	RAY_STAILQ_INIT(&head);													\
}

#define REGISTER_PROTOCOL(proto)											\
static void __attribute__((constructor(102), used)) preinit_##proto(void)	\
{																			\
	proto_register(&proto);													\
}

#ifdef __cplusplus
}
#endif

#endif //__RAY_PROTO_H__