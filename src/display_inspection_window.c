#include "display_inspection_window.h"
#include <ncurses.h>

void DisplayInspectionWindow(WINDOW *main_w, WINDOW *side_w)
{
	for (int i=2;i<14;i++)
		{
		mvwprintw(side_w, 2, i, "_");
		mvwprintw(side_w, 5, i, "_");
		mvwprintw(side_w, 8, i, "_");
		mvwprintw(side_w, 11, i, "_");
		}
	mvwprintw(side_w, 2, 2, ".");
	mvwprintw(side_w, 2, 6, ".");
	mvwprintw(side_w, 2, 10, ".");
	mvwprintw(side_w, 2, 14, ".");
	for (int j=3; j<12; j++)
		{
		mvwprintw(side_w, j, 2, "|");
		mvwprintw(side_w, j, 6, "|");
		mvwprintw(side_w, j, 10, "|");
		mvwprintw(side_w, j, 14, "|");
		}
	mvwprintw(side_w, 3, 4, "_"); // Top Left
	mvwprintw(side_w, 4, 3, "'");
	mvwprintw(side_w, 4, 4, "\\");
	mvwprintw(side_w, 3, 8, "A"); // Top
	mvwprintw(side_w, 4, 8, "|");
	mvwprintw(side_w, 3, 12, "_"); // Top Right
	mvwprintw(side_w, 4, 12, "/");
	mvwprintw(side_w, 4, 13, "'");
	mvwprintw(side_w, 7, 12, "-"); // Right
	mvwprintw(side_w, 7, 13, ">");
	mvwprintw(side_w, 10, 12, "\\"); // Bottom Right
	mvwprintw(side_w, 10, 13, "|");
	mvwprintw(side_w, 11, 12, "'");
	mvwprintw(side_w, 10, 8, "|"); // Bottom
	mvwprintw(side_w, 11, 8, "V");
	mvwprintw(side_w, 10, 4, "/"); // Bottom Left
	mvwprintw(side_w, 10, 3, "|");
	mvwprintw(side_w, 11, 4, "'");
	mvwprintw(side_w, 7, 4, "-"); // Left
	mvwprintw(side_w, 7, 3, "<");
	//wattron(side_w, COLOR_PAIR(color)); // Play or Pause
	mvwprintw(side_w, 7, 8, "@"); 
	//wattroff(side_w, COLOR_PAIR(color));
		
	for (int i=2;i<14;i++) ///////////////////////////////////////////// Keyboard: Letters
		{
		mvwprintw(side_w, 13, i, "_");
		mvwprintw(side_w, 16, i, "_");
		mvwprintw(side_w, 19, i, "_");
		mvwprintw(side_w, 22, i, "_");
		}
	mvwprintw(side_w, 13, 2, ".");
	mvwprintw(side_w, 13, 6, ".");
	mvwprintw(side_w, 13, 10, ".");
	mvwprintw(side_w, 13, 14, ".");
	for (int j=14; j<23; j++)
		{
		mvwprintw(side_w, j, 2, "|");
		mvwprintw(side_w, j, 6, "|");
		mvwprintw(side_w, j, 10, "|");
		mvwprintw(side_w, j, 14, "|");
		}
	mvwprintw(side_w, 15, 4, "E"); // Top Left
	mvwprintw(side_w, 15, 8, "R"); // Top
	mvwprintw(side_w, 15, 12, "T"); // Top Right
	mvwprintw(side_w, 18, 12, "G"); // Right
	mvwprintw(side_w, 21, 12, "B"); // Bottom Right
	mvwprintw(side_w, 21, 8, "V"); // Bottom
	mvwprintw(side_w, 21, 4, "C"); // Bottom Left
	mvwprintw(side_w, 18, 4, "D"); // Left
	mvwprintw(side_w, 18, 8, "F"); // Freeze
	mvwprintw(side_w, 18, 15, "Press F to Freeze");
	mvwprintw(side_w, 35, 3, "SCORE:");
	//mvwprintw(side_w, 36, 3, "%d", score[1]);
}