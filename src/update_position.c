#include "update_position.h"
#include <math.h>

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T){
	float A = (x_past_past - 2*x_past) * M/(T*T);
	float B = x_past * K / T;
	float C = M/(T*T) + K/T;
	float res = (F - A + B)/C;
	return res;
}