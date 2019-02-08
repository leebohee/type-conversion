/*
***********System Program Assignment 01***********
				2016311477 
				LEE BO HEE 
*/
#include <string.h>

double float_to_double(float src){
	unsigned copyOfsrc = 0, sign = 0, exp = 0, frac = 0;
	unsigned long copyOfdest = 0, copyOfsign = 0, copyOfexp = 0, copyOffrac = 0;
	double dest = 0.0;

	memcpy(&copyOfsrc, &src, sizeof(float));	// copy bit sequence to do bitwise operation
	sign = copyOfsrc & 0x80000000u;		//copy sign bit
	memcpy(&copyOfsign, &sign, sizeof(unsigned));
	copyOfsign <<= 32;

	exp = copyOfsrc & 0x7f800000u;	//copy bit sequence of exp
	frac = copyOfsrc & 0x007fffffu;	//copy bit sequence of frac
	//special 
	if(exp == 0x7f800000u){
		copyOfexp = 0x7ff0000000000000u;
		if(frac != 0x00000000u){
			copyOffrac = 0x0000000000000001u;
		}
		else
			copyOffrac = 0x0000000000000000u;
		copyOfdest = copyOfdest | copyOfsign;
		copyOfdest = copyOfdest | copyOfexp;
		copyOfdest = copyOfdest | copyOffrac;
		memcpy(&dest, &copyOfdest, sizeof(unsigned long));
		return dest;
	}
	
	memcpy(&copyOfexp, &exp, sizeof(unsigned));
	copyOfexp <<= 32;
	copyOfexp >>= 3;

	//plus bias difference (1023-127=896)
 	copyOfexp += 0x3800000000000000u;   
 
	memcpy(&copyOffrac, &frac, sizeof(unsigned));
	copyOffrac <<= 32;
	copyOffrac >>= 3;
	copyOfdest = copyOfdest | copyOfsign;
	copyOfdest = copyOfdest | copyOfexp;
	copyOfdest = copyOfdest | copyOffrac;
	
	memcpy(&dest, &copyOfdest, sizeof(unsigned long));

	return dest;
}
