void DisplayTargets(int coor_tar[][4], int nb_tar, WINDOW *main_w) // Split the Displays in Display and Update
{
	for (int i=0;i<nb_tar;i++)
		{
		wattron(main_w, COLOR_PAIR(4));
		mvwprintw(main_w, coor_tar[i][1], coor_tar[i][0], "%d", coor_tar[i][3]);
		wattroff(main_w, COLOR_PAIR(4));	
		}
}

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

for (int i = 0; i < nb_tar; i++) // Update if targets are reached
		{
		    if (x == coor_tar[i][0] && y == coor_tar[i][1])
		    {
		        coor_tar[i][2] = 1; // Is reached
		        if (coor_tar[i][3]==score[0]+1)
		        {
		        	score[1] = score[1] + coor_tar[i][3];
		        }
		        else
		        {
		        score[1] = coor_tar[i][3];
		        }
		        score[0] = coor_tar[i][3];
		    }
		}

// Print Targets
for (int i=0;i<nb_tar;i++)
{
    if (coor_tar[i][2] == 1) // If the target is reached
    { 
         coor_tar[i][0] = (rand() % (max - min + 1)) + min;
        coor_tar[i][1] = (rand() % (max - min + 1)) + min;
        coor_tar[i][2] = 0;
        num_tar++;
        coor_tar[i][3] = num_tar;
    } 
    else 
    {
        wattron(main_w, COLOR_PAIR(4));
    }
    mvwprintw(main_w, coor_tar[i][1], coor_tar[i][0], "%d", coor_tar[i][3]);
    wattroff(main_w, COLOR_PAIR(4));	
}