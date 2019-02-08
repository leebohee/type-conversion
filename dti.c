/*
***********System Program Assignment 01***********
				2016311477 
				LEE BO HEE 
*/
#include <string.h>

int double_to_int(double src){
	unsigned long copyOfsrc = 0, sign = 0, exp = 0, frac = 0, copyOfdest = 0;
	int dest = 0, e = 0;

	memcpy(&copyOfsrc, &src, sizeof(unsigned long));
	sign = copyOfsrc & 0x8000000000000000u;
	exp = copyOfsrc & 0x7ff0000000000000u;
	frac = copyOfsrc & 0x000fffffffffffffu;

	//denormal (set to 0)
	if(exp == 0x0u){
		copyOfdest = 0x0u;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}
	//special	(set to INT_MIN)
	else if(exp == 0x7ff0000000000000u){
		copyOfdest = 0x0000000080000000u;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}
	//normal
	else{
		exp >>= 52;
		memcpy(&e, &exp, (sizeof(unsigned long)));
		e -= 1023;				//subtract bias
		frac += 0x10000000000000u;	//add leading 1
		if(e >= 31){				//overflow (set to INT_MIN)
			copyOfdest = 0x8000000000000000u;
			copyOfdest >>= 32;
			memcpy(&dest, &copyOfdest, sizeof(unsigned));
		}
		else{
			if(e <= -1){
				copyOfdest = 0x0u;
				memcpy(&dest, &copyOfdest, sizeof(unsigned));
				return dest;
			}
			else{
				frac >>= (52-e);
				copyOfdest = copyOfdest | frac;

			}
			if(sign == 0x8000000000000000u){	//negative
				copyOfdest = ~copyOfdest + 0x1u;
			}
			copyOfdest = copyOfdest | sign;
			memcpy(&dest, &copyOfdest, sizeof(unsigned));

			return dest;
		}
	}
}
