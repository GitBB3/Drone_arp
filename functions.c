#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T){
	float res = (T*T/(M+K*T)) * ((F - M/(T*T)) * (x_past_past-2*x_past) + (K/T) * x_past);
	return res;
	}

int main(){
	float x_past = 10;
	float x_past_past = 10;
	float F = 0;
	float M = 1;
	float K = 1;
	float T = 1e4;
for (int i=0;i<50;i++){

	printf("%f \n",UpdatePosition(x_past, x_past_past, F, M, K, T));
	x_past_past = x_past;
	x_past = UpdatePosition(x_past, x_past_past, F, M, K, T);
	F+= 1e-6;
	}
	return 0 ;

}
