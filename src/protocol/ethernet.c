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
#include <ray_proto.h>
#include <ray_device.h>
#include <ray_packet.h>
#include <proto/ray_ether.h>
/*
  struct eth_header
{
  ray_u8_t  ether_daddr[ETH_ALEN];
  ray_u8_t  ether_saddr[ETH_ALEN];
  ray_u16_t ether_type;
} __attribute__ ((__packed__));
*/
#define ETHERNET_DEBUG
#ifdef ETHERNET_DEBUG
void ether_dump_addr(struct eth_header *ether_hdr)
{
	RAY_LOG(INFO, "daddr: %02x-%02x-%02x-%02x-%02x-%02x\n"
				  "saddr: %02x-%02x-%02x-%02x-%02x-%02x\n",
				  ether_hdr->ether_daddr[0], ether_hdr->ether_daddr[1], ether_hdr->ether_daddr[2],
				  ether_hdr->ether_daddr[3], ether_hdr->ether_daddr[4], ether_hdr->ether_daddr[5],
				  ether_hdr->ether_saddr[0], ether_hdr->ether_saddr[1], ether_hdr->ether_saddr[2],
				  ether_hdr->ether_saddr[3], ether_hdr->ether_saddr[4], ether_hdr->ether_saddr[5])
}
#endif
void ether_input(ray_devif_t *dev, ray_packet_t *pkt)
{
	struct eth_header *ether_hdr = RAY_PACKET_DATA(pkt);
	#ifdef ETHERNET_DEBUG
	ether_dump_addr(ether_hdr);
	#endif
}

ray_protocol_t ethernet = {
	.proto_desc = ETHER_DESC,
	.proto_input = ether_input,
};

REGISTER_PROTOCOL(ethernet);