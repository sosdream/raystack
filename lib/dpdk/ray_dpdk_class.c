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

#include <rte_debug.h>
#include <rte_mbuf.h>
/* Macro Define */
#define DPDK_DEVIF_CLASS        "dpdk"
#define DPDK_MEMORY_POOL_NAME   "dpdk_pool"

#define NB_MBUF   8192
#define MEMPOOL_CACHE_SIZE 256

ray_devif_t *dpdk_internal_create_dev(ray_devif_class_t *, struct rte_mempool *);

static struct rte_mempool *dpdk_mempool = NULL;
static ray_devif_class_t dpdk_device_class;

static ray_s32_t dpdk_init(void)
{
	ray_s32_t ret;
	ray_s32_t argc = 1;
	ray_s8_t *argv = DPDK_DEVIF_CLASS;
	/* Init the platform */
	ret = rte_eal_init(argc, &argv);
	if (ret < 0) {
		rte_panic("Init DPDK Failed!");
	}
	RAY_LOG(INFO, "DPDK device class init!\n");
	/* Init the packet memory pool */
	dpdk_mempool = rte_pktmbuf_pool_create(DPDK_MEMORY_POOL_NAME,
							 NB_MBUF,MEMPOOL_CACHE_SIZE,
							 0,
							 RTE_MBUF_DEFAULT_BUF_SIZE,
							 rte_socket_id());
	if (dpdk_mempool == NULL) {
		rte_panic("Can't init dpdk memory pool!");
	}
	return 0;
}

static ray_devif_t *dpdk_create_dev(void)
{
	return dpdk_internal_create_dev(&dpdk_device_class, dpdk_mempool);
}

static ray_devif_t *dpdk_create_dev_byport(ray_s32_t portid)
{
	return dpdk_internal_create_dev(&dpdk_device_class, dpdk_mempool);
}



static ray_devif_class_t dpdk_device_class = {
	.name = DPDK_DEVIF_CLASS,
	.init = dpdk_init,
	.create_dev = dpdk_create_dev,
	.create_dev_byport = dpdk_create_dev_byport,
	.destroy_dev = NULL,
	.destroy_all_dev = NULL,

	.devif_count = 0,
	.head_devs  = RAY_STAILQ_HEAD_INITIALIZER(dpdk_device_class.head_devs),
};

REGISTER_DEV_CLASS(dpdk_device_class);