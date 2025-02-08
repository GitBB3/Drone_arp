#include "display_targets.h"
#include <stdio.h>
#include <ncurses.h>

void DisplayTargets(int coor_tar[][4], int nb_tar, WINDOW *main_w)
{
	for (int i=0;i<nb_tar;i++)
		{
		wattron(main_w, COLOR_PAIR(4));
		mvwprintw(main_w, coor_tar[i][1], coor_tar[i][0], "%d", coor_tar[i][3]);
		wattroff(main_w, COLOR_PAIR(4));	
		}
}