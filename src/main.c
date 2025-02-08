#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "main_includes.h"


int main() {
	float M = 1;
	float K = 1;
	float T = 0.1;
	float Fx=0, Fy=0;
	float dF = 0.1;
	int max_lifetime = 1e3; // in (unity)seconds // 1e3
	int min_lifetime = 1e2; // 1e2
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
	int score[2]={0,0};
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
	
	int nb_tar=10;
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
	
	int nb_obs=10;
	int coor_obs[nb_obs][4]; // x, y, is_reached, life_time
	float dist_threshold = 1;
	
	for (int i=0;i<nb_obs;i++)
	{
		coor_obs[i][0] = (rand() % (max_pos_x - min + 1)) + min;
		coor_obs[i][1] = (rand() % (max_pos_y - min + 1)) + min;
		coor_obs[i][2] = 0;
		coor_obs[i][3] = (rand() % (max_lifetime - min_lifetime + 1)) + min_lifetime;
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
		DisplayInspectionWindow(main_w, side_w);
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Update targets //
		////////////////////////////////////////////////////////////////////////////////////////////
		// UpdateTargets(coor_tar, x, y, nb_tar, dist_threshold);
		UpdateTargets(coor_tar, x, y, nb_tar, &num_tar, max_pos_x, max_pos_y, min, dist_threshold);
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// Update obstacles //
		////////////////////////////////////////////////////////////////////////////////////////////
		UpdateObstacles(coor_obs, x, y, nb_obs, max_pos_x, max_pos_y, min, dist_threshold, max_lifetime, min_lifetime);
		for (int i=0;i<nb_obs;i++) 
			{
				mvwprintw(side_w, 40+i, 3, "%d", coor_obs[i][3]);
				mvwprintw(side_w, 40+i, 8, "%d", coor_obs[i][2]);	
			}

		////////////////////////////////////////////////////////////////////////////////////////////
		// Display the targets, the drone and the obstacles //
		////////////////////////////////////////////////////////////////////////////////////////////
		// DisplayTargets(coor_tar, max_pos_x, max_pos_y, min, nb_tar, &num_tar, main_w);
		DisplayTargets(coor_tar, nb_tar, main_w);
		DisplayDrone(x, y, color, main_w);
		DisplayObstacles(coor_obs, nb_obs, main_w);
		
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


