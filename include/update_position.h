#ifndef UPDATE_POSITION_H
#define UPDATE_POSITION_H

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T);

void UpdateDroneDynamics(float *x, float *x_past, float *x_past_past, float *y, float *y_past, float *y_past_past, float F_command[2], float F_repulsive[2], float M, float K, float T);

#endif