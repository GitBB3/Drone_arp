#include "display_obstacles.h"
#include <ncurses.h>
#include <stdio.h>

void DisplayObstacles(int coor_obs[][4], int nb_obs, WINDOW *main_w)
{
	for (int i=0;i<nb_obs;i++)
		{
		if (coor_obs[i][2] == 1)
			{
			wattron(main_w, COLOR_PAIR(5));
			mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "*");	
			wattroff(main_w, COLOR_PAIR(5));
			}
		else if (coor_obs[i][2] == 0)
			{
			wattron(main_w, COLOR_PAIR(3));
			mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "o");	
			wattroff(main_w, COLOR_PAIR(3));
			}	
		}
}