/*
***********System Program Assignment 01***********
				2016311477 
				LEE BO HEE 
*/
#include <string.h>

float int_to_float(int src){
	int i, e = 0, exp = 0;
	unsigned copyOfsrc = 0, sign = 0, val = 0, copyOfexp = 0, copyOffrac = 0, copyOfdest = 0, test_rounding = 0;
	float dest = 0.0;

	memcpy(&copyOfsrc, &src, sizeof(unsigned));

	if(copyOfsrc == 0x00000000u){
		copyOfdest = 0x00000000u;
		memcpy(&dest, &copyOfdest, sizeof(unsigned));
		return dest;
	}

	sign = src & 0x80000000u;

	//negative integer
	if(sign == 0x80000000u){
		if(src == 0x80000000)	//INT_MIN
			src = -(src+1);
		else
			src = -src;
	}

	val = src & 0x7fffffffu;
	//shift until counter leading 1
	val <<= 1;
	for(i = 1; i < 32; i++){
		if(val & 0x80000000u)
			break;
		else
			val <<= 1;
	}
	val <<= 1;
	e = 31 - i;
	
	//store frac
	test_rounding  = val & 0x1ffu;	
	val = val & 0xfffffe00u;
	if(test_rounding == 0x100u){
		if(val & 0x200u == 0x200u)
			val += 0x200u;
		if(val == 0x0u){	//overflow
				e++;
			}
	}
	else if(test_rounding > 0x100u){
		val += 0x200u;
		if(val == 0x0u)
				e++;
	}
	val >>= 9;
	memcpy(&copyOffrac, &val, sizeof(unsigned));

	memcpy(&exp, &e, sizeof(unsigned));
	exp += 127;	//bias
	exp <<= 23;	

	copyOfdest = copyOfdest | sign;
	copyOfdest = copyOfdest | exp;
	copyOfdest = copyOfdest | copyOffrac;
	memcpy(&dest, &copyOfdest, sizeof(unsigned));
	
	return dest;
}
