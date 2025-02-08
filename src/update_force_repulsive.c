#include "update_force_repulsive.h"
#include <math.h>

void add_repulsive_force_idx(float diff_x, float diff_y, float F_repulsive[2], float dist, float eta, float phi_0)
{
    if (dist <= phi_0)
    {
        float grad_x = diff_x/dist;
        float grad_y = diff_y/dist;
        F_repulsive[0] += eta * (1/dist - 1/phi_0) * (1/(dist*dist)) * grad_x;
        F_repulsive[1] += eta * (1/dist - 1/phi_0) * (1/(dist*dist)) * grad_y;
    }
}

void UpdateForceRepulsive(float F_repulsive[2], int nb_obs, int coor_obs[][4], float x, float x_past, float x_past_past, float y, float y_past, float y_past_past, float repulsion_param, float dist_threshold, float detection_threshold)
{
    float dist_min = 0.9 * dist_threshold;
    float phi_0 = detection_threshold;
    float eta = repulsion_param;
    float f_repulsive_x = 0;
    float f_repulsive_y = 0;
    for (int idx=0 ; idx<nb_obs ; idx++)
    {  
        float diff_x = x - coor_obs[idx][0];
        float diff_y = y - coor_obs[idx][1];
        float dist = sqrt(diff_x*diff_x + diff_y*diff_y);
        float dist_securised = fmaxf(dist, dist_min);
        if (dist <= phi_0)
        {
            float grad_x = diff_x/dist;
            float grad_y = diff_y/dist;
            f_repulsive_x += eta * (1/dist - 1/phi_0) * (1/(dist*dist)) * grad_x;
            f_repulsive_y += eta * (1/dist - 1/phi_0) * (1/(dist*dist)) * grad_y;
        }
        // add_repulsive_force_idx(diff_x, diff_y, F_repulsive, dist_securised, repulsion_param, detection_threshold);    
    }
    F_repulsive[0] = f_repulsive_x;
    F_repulsive[1] = f_repulsive_y;
}