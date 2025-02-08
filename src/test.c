// #include <ncurses.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// int main() {
// 	int score[2]={0,0};
	
// 	initscr();
// 	start_color();
// 	keypad(stdscr, TRUE);
// 	noecho();
// 	curs_set(0);
	
// 	// Define the main character window and the lateral inspection window
// 	int screen_height, screen_width;
// 	getmaxyx(stdscr, screen_height, screen_width);
// 	int main_height = screen_height;
// 	int main_width = screen_width * 0.8;
// 	int side_height = screen_height;
// 	int side_width = screen_width - main_width;
//     	WINDOW *main_w = newwin(main_height-2, main_width, 2, 0);
//     	WINDOW *side_w = newwin(side_height-2, side_width, 2, main_width);
//     	box(main_w, 0, 0);
//     	mvprintw(1, 1, "DRONE ENVIRONMENT");
//     	box(side_w, 0, 0);
//     	mvprintw(1, main_width, "INPUT AND DYNAMIC DISPLAY");
// 	//wrefresh(main_w);
// 	//wrefresh(side_w);
	
// 	int max = main_height-2;
	
// 	//Def colors
// 	init_pair(1, COLOR_BLUE, COLOR_RED); // Blue on red
// 	init_pair(2, COLOR_BLUE, COLOR_GREEN); // Blue on green
// 	init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Obstacle color
// 	init_pair(4, COLOR_GREEN, COLOR_BLACK); // Target color
// 	init_pair(5, COLOR_YELLOW, COLOR_RED); // Obstacle is reached color
// 	init_pair(6, COLOR_BLUE, COLOR_YELLOW); // Pressed key color
	
// 	// Test obstacles and targets 
// 	int nb_obs=5;
// 	int nb_tar=5;
// 	int num_tar=nb_tar;
// 	int min=3;
// 	int coor_obs[nb_obs][2]; // Add a third random parameter corresponding to the time bf the obst. disappears. time-- every time it's printed and reset when is null.
// 	int coor_tar[nb_tar][4]; // x, y, is_reached
	
// 	srand(time(NULL));
// 	for (int i=0;i<nb_obs;i++)
// 	{
// 		coor_obs[i][0] = (rand() % (max - min + 1)) + min;
// 		coor_obs[i][1] = (rand() % (max - min + 1)) + min;
// 	}
// 	for (int i=0;i<nb_tar;i++)
// 	{
// 		coor_tar[i][0] = (rand() % (max - min + 1)) + min;
// 		coor_tar[i][1] = (rand() % (max - min + 1)) + min;
// 		coor_tar[i][2] = 0;
// 		coor_tar[i][3] = i+1;
// 	}
	
// 	int x = 10, y = 10;
// 	int color=1; //Drone initialized in static configuration
// 	while (1) {
// 		wclear(main_w);
// 		wclear(side_w);
// 		box(main_w, 0, 0);
//     		box(side_w, 0, 0);
		
// 		// Inspection window
// 		for (int i=2;i<14;i++)
// 		{
// 			mvwprintw(side_w, 2, i, "_");
// 			mvwprintw(side_w, 5, i, "_");
// 			mvwprintw(side_w, 8, i, "_");
// 			mvwprintw(side_w, 11, i, "_");
// 		}
// 		mvwprintw(side_w, 2, 2, ".");
// 		mvwprintw(side_w, 2, 6, ".");
// 		mvwprintw(side_w, 2, 10, ".");
// 		mvwprintw(side_w, 2, 14, ".");
// 		for (int j=3; j<12; j++)
// 		{
// 			mvwprintw(side_w, j, 2, "|");
// 			mvwprintw(side_w, j, 6, "|");
// 			mvwprintw(side_w, j, 10, "|");
// 			mvwprintw(side_w, j, 14, "|");
// 		}
// 		mvwprintw(side_w, 3, 4, "_"); // Top Left
// 		mvwprintw(side_w, 4, 3, "'");
// 		mvwprintw(side_w, 4, 4, "\\");
// 		mvwprintw(side_w, 3, 8, "A"); // Top
// 		mvwprintw(side_w, 4, 8, "|");
// 		mvwprintw(side_w, 3, 12, "_"); // Top Right
// 		mvwprintw(side_w, 4, 12, "/");
// 		mvwprintw(side_w, 4, 13, "'");
// 		mvwprintw(side_w, 7, 12, "-"); // Right
// 		mvwprintw(side_w, 7, 13, ">");
// 		mvwprintw(side_w, 10, 12, "\\"); // Bottom Right
// 		mvwprintw(side_w, 10, 13, "|");
// 		mvwprintw(side_w, 11, 12, "'");
// 		mvwprintw(side_w, 10, 8, "|"); // Bottom
// 		mvwprintw(side_w, 11, 8, "V");
// 		mvwprintw(side_w, 10, 4, "/"); // Bottom Left
// 		mvwprintw(side_w, 10, 3, "|");
// 		mvwprintw(side_w, 11, 4, "'");
// 		mvwprintw(side_w, 7, 4, "-"); // Left
// 		mvwprintw(side_w, 7, 3, "<");
// 		//wattron(side_w, COLOR_PAIR(color)); // Play or Pause
// 		mvwprintw(side_w, 7, 8, "@"); 
// 		//wattroff(side_w, COLOR_PAIR(color));
		
// 		for (int i=2;i<14;i++) ///////////////////////////////////////////// Keyboard: Letters
// 		{
// 			mvwprintw(side_w, 13, i, "_");
// 			mvwprintw(side_w, 16, i, "_");
// 			mvwprintw(side_w, 19, i, "_");
// 			mvwprintw(side_w, 22, i, "_");
// 		}
// 		mvwprintw(side_w, 13, 2, ".");
// 		mvwprintw(side_w, 13, 6, ".");
// 		mvwprintw(side_w, 13, 10, ".");
// 		mvwprintw(side_w, 13, 14, ".");
// 		for (int j=14; j<23; j++)
// 		{
// 			mvwprintw(side_w, j, 2, "|");
// 			mvwprintw(side_w, j, 6, "|");
// 			mvwprintw(side_w, j, 10, "|");
// 			mvwprintw(side_w, j, 14, "|");
// 		}
// 		mvwprintw(side_w, 15, 4, "E"); // Top Left
// 		mvwprintw(side_w, 15, 8, "R"); // Top
// 		mvwprintw(side_w, 15, 12, "T"); // Top Right
// 		mvwprintw(side_w, 18, 12, "G"); // Right
// 		mvwprintw(side_w, 21, 12, "B"); // Bottom Right
// 		mvwprintw(side_w, 21, 8, "V"); // Bottom
// 		mvwprintw(side_w, 21, 4, "C"); // Bottom Left
// 		mvwprintw(side_w, 18, 4, "D"); // Left
// 		mvwprintw(side_w, 18, 8, "F"); // On/Off
		
// 		mvwprintw(side_w, 24, 3, "SCORE:");
// 		mvwprintw(side_w, 25, 3, "%d", score[1]);
		
		
// 		// Update targets
// 		for (int i = 0; i < nb_tar; i++) // Update if targets are reached
// 		{
// 		    if (x == coor_tar[i][0] && y == coor_tar[i][1])
// 		    {
// 		        coor_tar[i][2] = 1; // Is reached
// 		        if (coor_tar[i][3]==score[0]+1)
// 		        {
// 		        	score[1] = score[1] + coor_tar[i][3];
// 		        }
// 		        else
// 		        {
// 		        score[1] = coor_tar[i][3];
// 		        }
// 		        score[0] = coor_tar[i][3];
// 		    }
// 		}
		
// 		// Print the drone
// 		wattron(main_w, COLOR_PAIR(color));
// 		mvwprintw(main_w, y, x, "+");
// 		wattroff(main_w, COLOR_PAIR(color));
		
// 		// Print the obstacles
// 		for (int i=0;i<nb_obs;i++)
// 		{
// 			if (x == coor_obs[i][0] && y == coor_obs[i][1])
// 			{
// 				wattron(main_w, COLOR_PAIR(5));
// 				mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "*");	
// 				wattroff(main_w, COLOR_PAIR(5));
// 				score[1] = score[1] - score[0]/2;
// 			}
// 			else
// 			{
// 				wattron(main_w, COLOR_PAIR(3));
// 				mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "o");	
// 				wattroff(main_w, COLOR_PAIR(3));
// 			}	
// 		}
		
		
// 		// Print Targets
// 		for (int i=0;i<nb_tar;i++)
// 		{
// 			if (coor_tar[i][2] == 1) // If the target is reached
// 			{ 
// 			 	coor_tar[i][0] = (rand() % (max - min + 1)) + min;
// 				coor_tar[i][1] = (rand() % (max - min + 1)) + min;
// 				coor_tar[i][2] = 0;
// 				num_tar++;
// 				coor_tar[i][3] = num_tar;
// 			} 
// 			else 
// 			{
// 				wattron(main_w, COLOR_PAIR(4));
// 			}
// 			mvwprintw(main_w, coor_tar[i][1], coor_tar[i][0], "%d", coor_tar[i][3]);
// 			wattroff(main_w, COLOR_PAIR(4));	
// 		}
		
		
		
		
// 		wrefresh(main_w);
// 		wrefresh(side_w);
			
// 		int ch = getch();
// 		if (ch == 27) break; // 27 is ESC
// 		if (ch == 'f')
// 		{
// 			color=(1-(color-1))+1; //Changes from 1 to 2 or from 2 to 1
// 		}
// 		else if (color==2) // If the gears are on
// 		{
// 			switch (ch) 
// 			{
// 			case 'e': x--; y--; break; // Top-Left // Watch out, y-- : moves towards the top and vice versa
// 			case 'r': y--; break; // Top
// 			case 't': x++; y--; break; // Top-Right
// 			case 'g': x++; break; // Right
// 			case 'b': x++; y++; break; // Bottom-Right
// 			case 'v': y++; break; // Bottom
// 			case 'c': x--; y++; break; // Bottom-Left
// 			case 'd': x--; break; // Left
// 			}
// 		}
// 		wrefresh(main_w);
// 		wrefresh(side_w);
// 	}
// 	delwin(main_w);
// 	delwin(side_w);
// 	endwin();
// 	return 0;

// }




