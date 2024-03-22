/*
 * main.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Omar Tarek
 */
#include "StdTypes.h"
#include "Delay.h"
#include "mines_detector.h"

// Global variables
u16 Timer_Counter = 0;   // Counter for the timer
u8 Detected_Mine = 0;    // Flag indicating whether a mine is detected
u16 i = 0;               // Counter variable
u8 flag1 = 0;            // Flag 1
u8 flag2 = 0;            // Flag 2
u8 flag3 = 0;            // Flag 3
u8 steps = 0;            // Steps counter
u8 Total_Steps= 0;       // Total steps counter

int main(void)
{
    Car_Init();                                // Initialize the car
    while (1)
    {
        while (steps < 4)                      // Loop until steps reach 4
        {
            // Reset flags
            flag1 = 0;
            flag2 = 0;
            flag3 = 0;

            // Check if a mine is detected
            Car_Detected();
            if (Detected_Mine == 1)
            {
                Detected_Mine = 0;
                Car_Draft();                   // Take appropriate action if a mine is detected
            }
            else
            {
                Car_Continue();                // Continue moving forward
            }
        }
        Total_Steps += steps;                  // Accumulate steps
        if (Total_Steps == 4)
        {
            Car_Round(ROUND_RIGHT);            // Perform a right round
            Car_Detected();                    // Check if a mine is detected after the right round
            Car_Round(ROUND_RIGHT);            // Perform another right round
        }
        else if (Total_Steps == 8)
        {
            Car_Round(ROUND_LEFT);             // Perform a left round
            Car_Detected();                    // Check if a mine is detected after the left round
            Car_Round(ROUND_LEFT);             // Perform another left round
            Total_Steps = 0;                   // Reset the total steps counter
        }
        steps = 0;                             // Reset the steps counter
    } // end of while
    return 0;
} // end of main
