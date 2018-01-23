#ifndef __RAY_TYPES_H__
#define  __RAY_TYPES_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

typedef unsinged long long ray_u64_t;
typedef long long          ray_s64_t;

typedef unsinged int	   ray_u32_t;
typedef int				   ray_s32_t;

typedef unsinged short     ray_u16_t;
typedef short			   ray_s16_t;

typedef unsinged char	   ray_u8_t;
typedef char			   ray_s8_t;
typedef const char         ray_consts8_t;

#ifdef __cplusplus
}
#endif

#endif //__RAY_TYPES_H__