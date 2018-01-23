#ifndef __RAY_PACKET_H__
#define  __RAY_PACKET_H__ 1

#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif
struct __ray_packet;
typedef struct __ray_packet; ray_packet_t;

/* the packet buffer */
struct __ray_packet {
	ray_u8_t *data;
	/* The next segment of the packet */
	ray_packet_t  *next;
};

#ifdef __cplusplus
}
#endif

#endif //__RAY_PACKET_H__