#include "display_drone.h"
#include <ncurses.h>

void DisplayDrone(float x, float y, int color, WINDOW *main_w)
{
	wattron(main_w, COLOR_PAIR(color));
	mvwprintw(main_w, y, x, "+");
	wattroff(main_w, COLOR_PAIR(color));
}