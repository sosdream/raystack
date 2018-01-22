#ifndef __RAY_PACKET_H__
#define  __RAY_PACKET_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

struct __ray_packet {
	unsigned char *data;
};


typedef struct __ray_packet ray_packet_t;
#ifdef __cplusplus
}
#endif

#endif //__RAY_PACKET_H__