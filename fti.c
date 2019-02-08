/*
***********System Program Assignment 01***********
				2016311477 
				LEE BO HEE 
*/
#include <string.h>

int float_to_int(float src){
	unsigned copyOfsrc = 0, sign = 0, exp = 0, frac = 0, copyOfdest = 0;
	int e = 0, dest = 0;

	memcpy(&copyOfsrc, &src, sizeof(unsigned));
	sign = copyOfsrc & 0x80000000u;
	exp = copyOfsrc & 0x7f800000u;
	frac = copyOfsrc & 0x007fffffu;

	//denormal	(set to 0)
	if(exp == 0x0u){
		copyOfdest = 0x0u;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}
	//special	(set to INT_MIN)
	else if(exp == 0x7f800000u){
		copyOfdest = 0x80000000u;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}
	//normal
	else{
		exp >>= 23;
		memcpy(&e, &exp, (sizeof(unsigned)));
		e -= 127;			//subtract bias
		frac += 0x800000u;	//add leading 1
		if(e >= 31){		//overflow (set to INT_MIN)
			copyOfdest = 0x80000000u;
			memcpy(&dest, &copyOfdest, sizeof(unsigned));
		}
		else{
			if(e == 23){	//determine wheter shift frac
				//copyOfdest = copyOfdest | sign;
				copyOfdest = copyOfdest | frac;
			}
			else if(e > 23){
				frac <<= (e-23);
				//copyOfdest = copyOfdest | sign;
				copyOfdest = copyOfdest | frac;
			}
			else if(e <= -1){
				copyOfdest = 0x0u;
				memcpy(&dest, &copyOfdest, sizeof(unsigned));
				return dest;
			}
			else{
				frac >>= (23-e);
				//copyOfdest = copyOfdest | sign;
				copyOfdest = copyOfdest | frac;
			}
			if(sign == 0x80000000u){	//negative
				copyOfdest = ~copyOfdest + 0x1u;
			}
			copyOfdest = copyOfdest | sign;
			memcpy(&dest, &copyOfdest, sizeof(unsigned));

			return dest;
		}
	}
}
