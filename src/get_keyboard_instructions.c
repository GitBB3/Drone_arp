#include "get_keyboard_instructions.h"
#include <ncurses.h>
#include <math.h>
#include "update_position.h"

void GetKeyboardInstructions(int *running, int ch, int *color, float F_command[2], float dF){
    float *Fx = &F_command[0];
    float *Fy = &F_command[1];
    
    float dF_diag = dF/sqrt(2*dF);

    if (ch == 27) *running = 0; // 27 is ESC
    if (ch == 'f')
        {
            *color=(1-(*color-1))+1; //Changes from 1 to 2 or from 2 to 1
        }
    else if (*color==2) // If the simulation is not in pause/freeze
        {
        switch (ch) 
            {
            case 'e': *Fx -= dF_diag; *Fy -= dF_diag; break; // Top-Left // Watch out, y-- : moves towards the top and vice versa
            case 'r': *Fy -= dF; break; // Top
            case 't': *Fx += dF_diag; *Fy -= dF_diag; break; // Top-Right
            case 'g': *Fx += dF; break; // Right
            case 'b': *Fx += dF_diag; *Fy += dF_diag; break; // Bottom-Right
            case 'v': *Fy += dF; break; // Bottom
            case 'c': *Fx -= dF_diag; *Fy += dF_diag; break; // Bottom-Left
            case 'd': *Fx -= dF; break; // Left
            case 's': *Fx = 0; *Fy = 0; break; // Stop the drone (forces to 0)
            // case 'o': // Start Over/Reset
            }          
        }
}