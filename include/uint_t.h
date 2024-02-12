#include <stdint.h>

/**
	@file uint_t.h
	@author djb, kp, feh
	@source qmail, djbdns6
	@brief additional types and pack routines
	@brief define basic integer types and size through <stdint.h>
*/

#ifndef UINT8_H
#define UINT8_H

#ifdef HAS_UINT8_H
typedef uint8_t uint8;
#else
typedef unsigned char uint8;
#endif

#endif

#ifndef UINT16_H
#define UINT16_H

typedef uint16_t uint16;

extern void uint16_pack(char[2],uint16);
extern void uint16_pack_big(char[2],uint16);
extern void uint16_unpack(char[2],uint16 *);
extern void uint16_unpack_big(char[2],uint16 *);
#endif

#ifndef UINT32_H
#define UINT32_H

typedef uint32_t uint32;

extern void uint32_pack(char[4],uint32);
extern void uint32_pack_big(char[4],uint32);
extern void uint32_unpack(char[4],uint32 *);
extern void uint32_unpack_big(char[4],uint32 *);
#endif

#ifndef UINT64_H
#define UINT64_H

#ifdef HAS_UINT64_H
typedef uint64_t uint64;
#else
typedef unsigned long long uint64;
#endif

extern void uint64_pack(char[8],uint64);
extern void uint64_pack_big(char[8],uint64);
extern void uint64_unpack(char[8],uint64 *);
extern void uint64_unpack_big(char[8],uint64 *);
#endif

#ifndef UINT128_H
#define UINT128_H

/* uint128 used for native IPv6 address presentation */

struct uint128_t
{
    uint64_t hi; /* routing area */
    uint64_t lo; /* local area */
};

typedef struct uint128_t uint128;

extern void uint128_pack(char[16],uint128);
extern void uint128_pack_big(char[16],uint128);
extern void uint128_unpack(char[16],uint128 *);
extern void uint128_unpack_big(char[16],uint128 *);
#endif
