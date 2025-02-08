#include "update_obstacles.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void UpdateObstacles(int coor_obs[][4], float x, float y, int nb_obs, int max_pos_x, int max_pos_y, int min, float dist_threshold, int max_lifetime, int min_lifetime)
{
	for (int i = 0; i < nb_obs; i++)
		{
			if (coor_obs[i][2] == 0 && ((fabs(x - coor_obs[i][0]) < dist_threshold && fabs(y - coor_obs[i][1]) < dist_threshold) || coor_obs[i][3] <= 0))
				{
					coor_obs[i][2] = 1;
				}
			else if (coor_obs[i][2] == 1)
				{
				coor_obs[i][0] = (rand() % (max_pos_x - min + 1)) + min;
				coor_obs[i][1] = (rand() % (max_pos_y - min + 1)) + min;
				coor_obs[i][3] = (rand() % (max_lifetime - min_lifetime + 1)) + min_lifetime;
				coor_obs[i][2] = 0;
				}
			coor_obs[i][3] -= 1; // drone ageing
		}
}