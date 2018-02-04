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
#ifndef __RAY_PACKET_H__
#define  __RAY_PACKET_H__ 1
#include <ray_debug.h>
#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif
struct __ray_packet;
typedef struct __ray_packet ray_packet_t;

/* the packet buffer */
struct __ray_packet {
	ray_u8_t *data;
	ray_u16_t data_off;
	ray_u16_t data_len;
	/* The next segment of the packet */
	ray_packet_t  *next;
};

#define RAY_PACKET_SANITY_CHECK(pkt) do {									\
	if (pkt == NULL)														\
		RAY_PANIC("packet is null!");										\
	if (pkt->data_len == 0 || pkt->data_off > pkt->data_len)				\
		RAY_PANIC("packet len is error!");									\
} while(0)

static inline ray_u8_t *ray_packet_append(ray_packet_t *pkt, ray_u16_t len)
{
	void *tail;
	ray_packet_t *pkt_last;


}
#define RAY_PACKET_DATA(pkt)												\
({																			\
	void *ptr;																\
	RAY_PACKET_SANITY_CHECK(pkt);											\
	ptr = pkt->data + pkt->data_off;										\
	ptr;																	\
}) 
#define RAY_PACKET_LEN(pkt) ({												\
	RAY_PACKET_SANITY_CHECK(pkt);											\
	pkt->data_len;															\
})


#ifdef __cplusplus
}
#endif

#endif //__RAY_PACKET_H__