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

#include <pthread.h>
#include <sched.h>

#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mbuf.h>


/* Macro Define */
#define DEVICE_NAME_LENGTH		128

static ray_devif_ops_t dpdk_device_ops;
static const struct rte_eth_conf dpdk_devif_conf = {
        .rxmode = {
                .split_hdr_size = 0,
                .header_split   = 0, /**< Header Split disabled */
                .hw_ip_checksum = 0, /**< IP checksum offload disabled */
                .hw_vlan_filter = 0, /**< VLAN filtering disabled */
                .jumbo_frame    = 0, /**< Jumbo Frame Support disabled */
                .hw_strip_crc   = 1, /**< CRC stripped by hardware */
        },
        .txmode = {
                .mq_mode = ETH_MQ_TX_NONE,
        },
};
/* Init dpdk device */
static void dpdk_device_configuration(ray_devif_t *dev, struct rte_mempool *pkt_mempool)
{
	struct ether_addr ether_addr;
	ray_u16_t nb_rxd, nb_txd;

	if (DEVICE_INITED(dev))
		return ;
	RAY_LOG(INFO, "%s configuration...\n", dev->name);
	rte_eth_dev_configure(dev->dev_id, 1, 1, &dpdk_devif_conf);

	rte_eth_dev_adjust_nb_rx_tx_desc(dev->dev_id, &nb_rxd,
                                                       &nb_txd);

	rte_eth_macaddr_get(dev->dev_id, (struct ether_addr *)&dev->dev_mac);
	RAY_LOG(INFO, "%s mac : %02x:%02x:%02x:%02x:%02x:%02x\n", dev->name,
					dev->dev_mac.ether_addr[0], dev->dev_mac.ether_addr[1],
					dev->dev_mac.ether_addr[2], dev->dev_mac.ether_addr[3],
					dev->dev_mac.ether_addr[4],dev->dev_mac.ether_addr[5]);

	rte_eth_rx_queue_setup(dev->dev_id, 0, nb_rxd,
                                    rte_eth_dev_socket_id(dev->dev_id),
                                    NULL,
									pkt_mempool);
	rte_eth_tx_queue_setup(dev->dev_id, 0, nb_txd,
                                rte_eth_dev_socket_id(dev->dev_id),
                                NULL);
	/* Initialize TX buffers */
	/*tx_buffer[portid] = rte_zmalloc_socket("tx_buffer",
                                RTE_ETH_TX_BUFFER_SIZE(MAX_PKT_BURST), 0,
                                rte_eth_dev_socket_id(portid));
	rte_eth_tx_buffer_init(tx_buffer[portid], MAX_PKT_BURST);
	rte_eth_tx_buffer_set_err_callback(tx_buffer[portid],
                                rte_eth_tx_buffer_count_callback,
                                &port_statistics[portid].dropped);
    */
	DEVICE_SET_STATE(dev, INTIALIZATION);
}

ray_devif_t *dpdk_internal_create_dev(ray_devif_class_t *devif_class, struct rte_mempool *pkt_mempool)
{
	ray_u32_t   port_max;
	ray_devif_t *ifdev;
	ray_s8_t dev_name[DEVICE_NAME_LENGTH];

	if (pkt_mempool == NULL)
		return NULL;
	/* Check the devid is ok? */
	port_max = rte_eth_dev_count();
	if (devif_class->devif_count >= port_max) {
		return NULL;
	}

	ifdev = ray_malloc(sizeof(ray_devif_t), RAY_CACHELINE_ALIGN);
	if (ifdev == NULL)
		return NULL;
	ifdev->dev_id = devif_class->devif_count++;

	/* The device name is it's class name + index */
	ray_sprintf(dev_name, "%s-%d",
					 devif_class->name, ifdev->dev_id);
	ifdev->name = ray_strdup(dev_name);
	ifdev->ops  = &dpdk_device_ops;

	DEVICE_SET_STATE(ifdev, UNINTIALIZATION);
	/* configuration this device */
	dpdk_device_configuration(ifdev, pkt_mempool);

	return ifdev;
}
ray_devif_t *dpdk_internal_create_dev_byid(ray_devif_class_t *devif_class,
									 struct rte_mempool *pkt_mempool,
									 ray_u32_t portid)
{
	ray_u32_t   port_max;
	ray_devif_t *ifdev;
	ray_s8_t dev_name[DEVICE_NAME_LENGTH];

	if (pkt_mempool == NULL)
		return NULL;

	/* Check the devid is ok? */
	port_max = rte_eth_dev_count();
	if (portid >= port_max) {
		return NULL;
	}

	ifdev = ray_malloc(sizeof(ray_devif_t), RAY_CACHELINE_ALIGN);
	if (ifdev == NULL)
		goto finish;

	ifdev->dev_id = portid;

	/* The device name is it's class name + index */
	ray_sprintf(dev_name, "%s-%d",
					 devif_class->name, devif_class->devif_count++);
	ifdev->name = ray_strdup(dev_name);
	ifdev->ops  = &dpdk_device_ops;
	DEVICE_SET_STATE(ifdev, UNINTIALIZATION);
	/* configuration this device */
	dpdk_device_configuration(ifdev, pkt_mempool);

finish:
	return ifdev;
}

static void dpdk_device_main_loop(ray_devif_t *dev)
{
	ray_packet_t pkts[64];
	ray_devif_ops_t *devops;

	devops = dev->ops;
	while (1) {
		/* receive the packet */
		devops->if_input(dev, pkts);
	}
}

/* Device oprations */
static ray_s32_t dpdk_start(ray_devif_t *dev, ray_u32_t core_id, dev_start_loop_t loop)
{
	ray_s32_t ret;
	cpu_set_t cpuset;
	pthread_t thread_id;

	if (!DEVICE_INITED(dev)) {
		return -1;
	}

    rte_eth_dev_start(dev->dev_id);

	CPU_ZERO(&cpuset);
	CPU_SET(core_id, &cpuset);


	ret = pthread_create(&thread_id, NULL, dpdk_device_main_loop, dev);
	if (ret != 0) {
		RAY_LOG(INFO, "%s start failed!", dev->name);
		return ret;
	}
	/* Set CPU affinity */
	ret = pthread_setaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset);
	if (ret != 0) {
		RAY_LOG(INFO, "Warning: %s set cpu to running failed!", dev->name);
	}

	RAY_LOG(INFO, "%s has started!\n", dev->name);
	return 0;
}

static ray_s32_t dpdk_input(ray_devif_t *dev, ray_packet_t *pkt)
{
	static size_t counter = 0;
	struct rte_mbuf *pkts_burst[64];

re_receive:
	counter = rte_eth_rx_burst(dev->dev_id, 0, pkts_burst, 64);
	if (counter <= 0) {
		usleep(10000);
		goto re_receive;
	}
	RAY_LOG(INFO, "receive : %d packets\n", counter);
	return 0;
}

static ray_s32_t dpdk_output(ray_devif_t *dev, ray_packet_t *pkt)
{
	return 0;
}

static ray_devif_ops_t dpdk_device_ops = {
	.if_start = dpdk_start,
	.if_input = dpdk_input,
	.if_output = dpdk_output,
};