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
#ifndef __RAY_ETHERNET_H__
#define  __RAY_ETHERNET_H__ 1
#ifdef __cplusplus
extern "C" {
#endif

/*
 *      IEEE 802.3 Ethernet magic constants.  The frame sizes omit the preamble
 *      and FCS/CRC (frame check sequence).
 */    

#define ETH_ALEN        6               /* Octets in one ethernet addr   */
#define ETH_HLEN        14              /* Total octets in header.       */
#define ETH_ZLEN        60              /* Min. octets in frame sans FCS */
#define ETH_DATA_LEN    1500            /* Max. octets in payload        */
#define ETH_FRAME_LEN   1514            /* Max. octets in frame sans FCS */
#define ETH_FCS_LEN     4               /* Octets in the FCS             */


/* Ethernet protocol ID's */
#define ETHERTYPE_PUP   0x0200          /* Xerox PUP */
#define ETHERTYPE_SPRITE  0x0500    /* Sprite */
#define ETHERTYPE_IP    0x0800    /* IP */
#define ETHERTYPE_ARP   0x0806    /* Address resolution */
#define ETHERTYPE_REVARP  0x8035    /* Reverse ARP */
#define ETHERTYPE_AT    0x809B    /* AppleTalk protocol */
#define ETHERTYPE_AARP    0x80F3    /* AppleTalk ARP */
#define ETHERTYPE_VLAN    0x8100    /* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_IPX   0x8137    /* IPX */
#define ETHERTYPE_IPV6    0x86dd    /* IP protocol version 6 */
#define ETHERTYPE_LOOPBACK  0x9000    /* used to test interfaces */

/* This is a name for the 48 bit ethernet address available on many
   systems.  */
struct eth_addr
{
  ray_u8_t ether_addr[ETH_ALEN];
} __attribute__ ((__packed__));

/* 10Mb/s ethernet header */
struct eth_header
{
  ray_u8_t  ether_daddr[ETH_ALEN];	/* destination eth addr	*/
  ray_u8_t  ether_saddr[ETH_ALEN];	/* source ether addr	*/
  ray_u16_t ether_type;		        /* packet type ID field	*/
} __attribute__ ((__packed__));

#define ETHER_DESC		"ethernet"

#ifndef ETHER_ADDR_LEN
#define	ETHER_ADDR_LEN	ETH_ALEN                 /* size of ethernet addr */
#endif

#define	ETHER_TYPE_LEN	2                        /* bytes in type field */
#define	ETHER_CRC_LEN	4                        /* bytes in CRC field */

#ifndef ETHER_HDR_LEN
#define	ETHER_HDR_LEN	ETH_HLEN                 /* total octets in header */
#endif

#ifndef ETHER_MIN_LEN
#define	ETHER_MIN_LEN	(ETH_ZLEN + ETHER_CRC_LEN) /* min packet length */
#endif

#ifndef ETHER_MAX_LEN
#define	ETHER_MAX_LEN	(ETH_FRAME_LEN + ETHER_CRC_LEN) /* max packet length */
#endif

/* make sure ethenet length is valid */
#define	ETHER_IS_VALID_LEN(foo)	\
	((foo) >= ETHER_MIN_LEN && (foo) <= ETHER_MAX_LEN)

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16

#define	ETHERMTU	ETH_DATA_LEN
#define	ETHERMIN	(ETHER_MIN_LEN - ETHER_HDR_LEN - ETHER_CRC_LEN)

#ifdef __cplusplus
}
#endif

#endif //__RAY_ETHERNET_H__