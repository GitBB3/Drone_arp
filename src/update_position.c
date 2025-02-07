#include "update_position.h"
#include <math.h>

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T){
	float A = (x_past_past - 2*x_past) * M/(T*T);
	float B = x_past * K / T;
	float C = M/(T*T) + K/T;
	float res = (F - A + B)/C;
	return res;
}

void UpdateDroneDynamics(float *x, float *x_past, float *x_past_past, float *y, float *y_past, float *y_past_past, int min_x, int max_x, int min_y, int max_y, float F_command[2], float F_repulsive[2], float M, float K, float T)
{
	*x_past_past = *x_past;
	*y_past_past = *y_past;
	*x_past = *x;
	*y_past = *y;
	float x_calc = UpdatePosition(*x_past, *x_past_past, F_command[0]+F_repulsive[0], M, K, T);
	float y_calc = UpdatePosition(*y_past, *y_past_past, F_command[1]+F_repulsive[1], M, K, T);
	
	float x_bounded = fmaxf(min_x, fminf(x_calc, max_x));
    float y_bounded = fmaxf(min_y, fminf(y_calc, max_y));

	*x = x_bounded;
	*y = y_bounded;
}