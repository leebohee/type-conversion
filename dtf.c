/*
***********System Program Assignment 01***********
				2016311477 
				LEE BO HEE 
*/
#include <string.h>

float double_to_float(double src){
	unsigned long copyOfsrc = 0, sign = 0, exp = 0, frac_h = 0, frac_l = 0, test = 0;
	unsigned copyOfdest = 0, copyOfsign = 0, copyOfexp = 0, copyOffrac = 0, test_rounding = 0;
	float dest = 0.0;

	memcpy(&copyOfsrc, &src, sizeof(unsigned long));
	sign = copyOfsrc & 0x8000000000000000u;	//copy sign bit
	sign >>= 32;
	memcpy(&copyOfsign, &sign, sizeof(unsigned));

	exp = copyOfsrc & 0x7ff0000000000000u;	//copy bit sequence of exp
	memcpy(&copyOfexp, &exp, sizeof(unsigned));
	//special
	test = copyOfsrc & 0x000fffffffffffffu;
	if(exp == 0x7ff0000000000000u){
		copyOfexp = 0x7f800000u;
		if(test != 0x0000000000000000u){
			copyOffrac = 0x00000001u;
		}
		else
			copyOffrac = 0x00000000u;
		copyOfdest = copyOfdest | copyOfsign;
		copyOfdest = copyOfdest | copyOfexp;
		copyOfdest = copyOfdest | copyOffrac;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}
	frac_h = copyOfsrc & 0x000fffffe0000000u;	//copy bit sequence of frac that is upper 23 bits
	frac_h >>= 29;
	frac_l = copyOfsrc & 0x000000001fffffffu;
	
	//copy bit sequence of frac that is lower 29 bits 
	//determine frac_l > 100.... or not then round nearest-even
	test_rounding  = frac_l & 0x1fffffffu;
	
	if(test_rounding == 0x10000000u){
		if(frac_h & 0x1 == 0x1){
			frac_h += 1;
			if(frac_h >= 0x800000u){
				exp++;
				frac_h & 0;
			}
		}
	}
	else if(test_rounding > 0x10000000u){
		frac_h += 1;
		if(frac_h >= 0x800000u){
			exp++;
			frac_h & 0;
		}
	}
	memcpy(&copyOffrac, &frac_h, sizeof(unsigned));
	
	//infinity if exp of double is larger than 1150 or smaller than 897
	if(exp > 0x47e0000000000000 || exp < 0x3810000000000000u){
		exp = exp & 0;
		exp = exp | 0x7f80000000000000u;
		exp >>= 32;
		copyOffrac = copyOffrac & 0;
	}
	else{
		exp = exp - 0x3800000000000000u;
		exp >>= 32;
		exp <<= 3;
	}
	memcpy(&copyOfexp, &exp, sizeof(unsigned));

	copyOfdest = copyOfdest | copyOfsign;
	copyOfdest = copyOfdest | copyOfexp;
	copyOfdest = copyOfdest | copyOffrac;

	memcpy(&dest, &copyOfdest, sizeof(unsigned));
	
	return dest;
}
