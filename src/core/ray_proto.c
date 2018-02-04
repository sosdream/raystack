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
#include <ray_string.h>
#include <ray_proto.h>
#include <ray_errno.h>
/* Save all register protocols */
RAY_STAILQ_HEAD(, ray_protocol_t) ray_protocol_head;

ray_bool_t proto_exist(ray_protocol_t *protocol)
{
	ray_bool_t ret = FALSE;
	ray_protocol_t *tmp_proto;

	RAY_STAILQ_FOREACH(tmp_proto, &ray_protocol_head, proto_list) {
		if (ray_strcmp(tmp_proto->proto_desc, protocol->proto_desc) == 0) {
			ret = TRUE;
			break;
		}
	}
	return ret;
}

ray_protocol_t *get_protocol_byname(const ray_s8_t const *proto_name)
{
	ray_protocol_t *tmp_proto;

	if (proto_name == NULL) {
		errno = EINVAL;
		goto no_found;
	}

	RAY_STAILQ_FOREACH(tmp_proto, &ray_protocol_head, proto_list) {
		if (ray_strcmp(tmp_proto->proto_desc, proto_name) == 0) {
			return tmp_proto;
		}
	}

no_found:
	return NULL;
}

void proto_register(ray_protocol_t *protocol)
{
	/* Invalid parameter check */
	if(protocol == NULL) {
		RAY_LOG(ERR, "Invalid Parameter!\n");
		errno = EINVAL;
		return;
	}

	if (proto_exist(protocol)) {
		errno = EEXIST;
		return;
	}

	/* Insert the tail list */
	RAY_STAILQ_INSERT_TAIL(&ray_protocol_head, protocol, proto_list);
}

INIT_PROTOCOL_LIST(ray_protocol_head);