#include "uint_t.h"

/**
	@file uint8x.c
	@author feh
	@brief packing/unpacking 8 bit int to/from char string
*/

void uint8_pack(char s[2],uint8 u) 
{
  s[0] = u & 255;
  s[1] = u >> 4;
}

void uint8_pack_big(char s[2],uint8 u)
{
  s[1] = u & 255;
  s[0] = u >> 4;
}

void uint8_unpack(char s[2],uint8 *u)
{
  uint8 result;

  result =  (unsigned char) s[1]; result <<= 4;
  result += (unsigned char) s[0];

  *u = result;
}

void uint8_unpack_big(char s[2],uint8 *u)
{
  uint8 result;

  result =  (unsigned char) s[0]; result <<= 4;
  result += (unsigned char) s[1];

  *u = result;
}
