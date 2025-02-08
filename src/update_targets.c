#include "update_targets.h"
#include <math.h>
#include <stdlib.h>

void UpdateTargets(int coor_tar[][4], float x, float y, int nb_tar, int *num_tar, int max_pos_x, int max_pos_y, int min, float dist_threshold)
{
	for (int i = 0; i < nb_tar; i++) // Update if targets are reached
		{
		if (coor_tar[i][2] == 0 && fabs(x - coor_tar[i][0]) < dist_threshold && fabs(y - coor_tar[i][1]) < dist_threshold)
			{
		    coor_tar[i][2] = 1; // Is reached
			}
		else if (coor_tar[i][2] == 1)
            {
			coor_tar[i][0] = (rand() % (max_pos_x - min + 1)) + min;
			coor_tar[i][1] = (rand() % (max_pos_y - min + 1)) + min;
			coor_tar[i][2] = 0;
			(*num_tar)++;
			coor_tar[i][3] = *num_tar;
        	}
		}
}