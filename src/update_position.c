#include "update_position.h"
#include <math.h>

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T){
	float A = (x_past_past - 2*x_past) * M/(T*T);
	float B = x_past * K / T;
	float C = M/(T*T) + K/T;
	float res = (F - A + B)/C;
	return res;
}

void UpdateDroneDynamics(float *x, float *x_past, float *x_past_past, float *y, float *y_past, float *y_past_past, float Fx, float Fy, float M, float K, float T)
{
	*x_past_past = *x_past;
	*y_past_past = *y_past;
	*x_past = *x;
	*y_past = *y;
	*x = UpdatePosition(*x_past, *x_past_past, Fx, M, K, T);
	*y = UpdatePosition(*y_past, *y_past_past, Fy, M, K, T);
}

