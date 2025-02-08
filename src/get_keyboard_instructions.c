#include "get_keyboard_instructions.h"
#include <ncurses.h>
#include <math.h>
#include "update_position.h"

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