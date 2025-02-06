#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float UpdatePosition(float x_past, float x_past_past, float F, float M, float K, float T){
	float A = (x_past_past - 2*x_past) * M/(T*T);
	float B = x_past * K / T;
	float C = M/(T*T) + K/T;
	float res = (F - A + B)/C;
	return res;
}

void GetKeyboardInstructions(int *running, int ch, int *color, float *Fx, float *Fy, float *x, float *y, float *x_past, float *x_past_past, float *y_past, float *y_past_past, float M, float K, float T, float dF){
		if (ch == 27) *running = 0; // 27 is ESC
		if (ch == 'f')
			{
				*color=(1-(*color-1))+1; //Changes from 1 to 2 or from 2 to 1
			}
		else if (*color==2) // If the gears are on
			{
			switch (ch) 
				{
				case 'e': *Fx -= dF; *Fy -= dF; break; // Top-Left // Watch out, y-- : moves towards the top and vice versa
				case 'r': *Fy -= dF; break; // Top
				case 't': *Fx += dF; *Fy -= dF; break; // Top-Right
				case 'g': *Fx += dF; break; // Right
				case 'b': *Fx += dF; *Fy += dF; break; // Bottom-Right
				case 'v': *Fy += dF; break; // Bottom
				case 'c': *Fx -= dF; *Fy += dF; break; // Bottom-Left
				case 'd': *Fx -= dF; break; // Left
				}
			
			////////////////////////////////////////////////////////////////////////////////////////////
			// Update the drone //
			////////////////////////////////////////////////////////////////////////////////////////////
				
			*x_past_past = *x_past;
			*y_past_past = *y_past;
			*x_past = *x;
			*y_past = *y;
			*x = UpdatePosition(*x_past, *x_past_past, *Fx, M, K, T);
			*y = UpdatePosition(*y_past, *y_past_past, *Fy, M, K, T);
				
			}
}

void DisplayDrone(float x, float y, int color, WINDOW *main_w)
{
	wattron(main_w, COLOR_PAIR(color));
	mvwprintw(main_w, y, x, "+");
	wattroff(main_w, COLOR_PAIR(color));
}

void DisplayTargets(int coor_tar[][4], int max_pos_x, int max_pos_y, int min, int nb_tar, int *num_tar, WINDOW *main_w)
{
	for (int i=0;i<nb_tar;i++)
		{
		if (coor_tar[i][2] == 1) // If the target is reached
			{ 
		 	coor_tar[i][0] = (rand() % (max_pos_x - min + 1)) + min;
			coor_tar[i][1] = (rand() % (max_pos_y - min + 1)) + min;
			coor_tar[i][2] = 0;
			*num_tar++;
			coor_tar[i][3] = *num_tar;
			} 
		else 
			{
				wattron(main_w, COLOR_PAIR(4));
			}
		mvwprintw(main_w, coor_tar[i][1], coor_tar[i][0], "%d", coor_tar[i][3]);
		wattroff(main_w, COLOR_PAIR(4));	
		}
}

int main() {
	float M = 1;
	float K = 1;
	float T = 0.1;
	float Fx=0, Fy=0;
	float dF = 0.1;
////////////////////////////////////////////////////////////////////////////////////////////
// Initialize ncurses //
////////////////////////////////////////////////////////////////////////////////////////////

	initscr();
	start_color();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);

////////////////////////////////////////////////////////////////////////////////////////////
// Display the windows //
////////////////////////////////////////////////////////////////////////////////////////////

	// Obtenir la taille de l'écran
	int screen_height, screen_width;
	getmaxyx(stdscr, screen_height, screen_width);

	// Dimensions des fenêtres
	int main_height = screen_height - 2;  // Réduction de 2 pour éviter de dépasser les limites
	int side_height = screen_height - 2;
	int main_width = screen_width * 0.8;  // 80% de la largeur de l'écran pour la fenêtre principale
	int side_width = screen_width - main_width;  // Le reste pour la fenêtre latérale

	// Création des fenêtres
	WINDOW *main_w = newwin(main_height, main_width, 1, 0);  // Fenêtre principale
	WINDOW *side_w = newwin(side_height, side_width, 1, main_width);  // Fenêtre latérale

	// Dessiner les bordures
	box(main_w, 0, 0);  // Bordure pour la fenêtre principale
	box(side_w, 0, 0);  // Bordure pour la fenêtre latérale

	// Afficher les titres
	mvprintw(0, 1, "DRONE ENVIRONMENT");  // Titre pour la fenêtre principale
	mvprintw(0, main_width + 1, "INPUT AND DYNAMIC DISPLAY");  // Titre pour la fenêtre latérale

	// Rafraîchir les fenêtres et l'écran principal
	refresh();            // Rafraîchir l'écran principal (pour les titres)
	wrefresh(main_w);     // Rafraîchir la fenêtre principale
	wrefresh(side_w);     // Rafraîchir la fenêtre latérale

////////////////////////////////////////////////////////////////////////////////////////////
// Initialize variables and colors //
////////////////////////////////////////////////////////////////////////////////////////////
	
	int max_pos_y = main_height-2;
	int max_pos_x = main_width-2;
	int min = 2;
	srand(time(NULL));
	
	//Def colors
	init_pair(1, COLOR_BLUE, COLOR_RED); // Blue on red
	init_pair(2, COLOR_BLUE, COLOR_GREEN); // Blue on green
	init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Obstacle color
	init_pair(4, COLOR_GREEN, COLOR_BLACK); // Target color
	init_pair(5, COLOR_YELLOW, COLOR_RED); // Obstacle is reached color
	init_pair(6, COLOR_BLUE, COLOR_YELLOW); // Pressed key color

////////////////////////////////////////////////////////////////////////////////////////////
// Initialize targets //
////////////////////////////////////////////////////////////////////////////////////////////
	
	int nb_tar=5;
	int num_tar=nb_tar;
	int coor_tar[nb_tar][4]; // x, y, is_reached
	
	for (int i=0;i<nb_tar;i++)
	{
		coor_tar[i][0] = (rand() % (max_pos_x - min + 1)) + min;
		coor_tar[i][1] = (rand() % (max_pos_y - min + 1)) + min;
		coor_tar[i][2] = 0;
		coor_tar[i][3] = i+1;
	}
	
////////////////////////////////////////////////////////////////////////////////////////////
// Initialize obstacles //
////////////////////////////////////////////////////////////////////////////////////////////
	
	int nb_obs=5;
	int coor_obs[nb_obs][2];
	
	for (int i=0;i<nb_obs;i++)
	{
		coor_obs[i][0] = (rand() % (max_pos_x - min + 1)) + min;
		coor_obs[i][1] = (rand() % (max_pos_y - min + 1)) + min;
	}
	
////////////////////////////////////////////////////////////////////////////////////////////
// Initialize drone //
////////////////////////////////////////////////////////////////////////////////////////////
	
	float x_past_past = 10, y_past_past = 10;
	float x_past = 10, y_past = 10;
	float x = 10, y = 10;
	int color=1; //Drone initialized in static configuration
	
	int running = 1;
	
	while (running) {
		////////////////////////////////////////////////////////////////////////////////////////////
		// Clear the windows //
		////////////////////////////////////////////////////////////////////////////////////////////
		werase(main_w);
		werase(side_w);
		box(main_w, 0, 0);
	    	box(side_w, 0, 0);
		mvwprintw(side_w, 25, 3, "Pos init: %f, %f", x, y);
		mvwprintw(side_w, 30, 3, "Fx:");
		mvwprintw(side_w, 30, 8, "%f", Fx);
		mvwprintw(side_w, 31, 3, "Fy:");
		mvwprintw(side_w, 31, 8, "%f", Fy);
		////////////////////////////////////////////////////////////////////////////////////////////
		// Display the inspection window //
		////////////////////////////////////////////////////////////////////////////////////////////
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
		
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Update targets //
		////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Update obstacles //
		////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Display the targets //
		////////////////////////////////////////////////////////////////////////////////////////////
		DisplayTargets(coor_tar, max_pos_x, max_pos_y, min, nb_tar, &num_tar, main_w);
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Display the drone //
		////////////////////////////////////////////////////////////////////////////////////////////
		DisplayDrone(x, y, color, main_w);
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Display the obstacles //
		////////////////////////////////////////////////////////////////////////////////////////////
		
		for (int i=0;i<nb_obs;i++)
			{
				if (x == coor_obs[i][0] && y == coor_obs[i][1])
				{
					wattron(main_w, COLOR_PAIR(5));
					mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "*");	
					wattroff(main_w, COLOR_PAIR(5));
					//score[1] = score[1] - score[0]/2;
				}
				else
				{
					wattron(main_w, COLOR_PAIR(3));
					mvwprintw(main_w, coor_obs[i][1], coor_obs[i][0], "o");	
					wattroff(main_w, COLOR_PAIR(3));
				}	
			}
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Refresh the windows //
		////////////////////////////////////////////////////////////////////////////////////////////
		refresh();
		wrefresh(main_w);
		wrefresh(side_w);
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Get the keyboard instructions //
		////////////////////////////////////////////////////////////////////////////////////////////
		int ch = getch();
		GetKeyboardInstructions(&running, ch, &color, &Fx, &Fy, &x, &y, &x_past, &x_past_past, &y_past, &y_past_past, M, K, T, dF);
		
		usleep(1e4);
	}
		
	// Nettoyage
	delwin(main_w);
	delwin(side_w);
	endwin();

	return 0;
}


