// Jaden Mardini - PROG71990 - SEC1 - STUDENT#8762993 
//a seating reservation program for the Colossus Airlines fleet consists
//one plane with a seating capacity of 12. It makes one flight daily

#define _CRT_SECURE_NO_WARNINGS
#include "reservations.h"
#include <stdlib.h>

int main(void)
{
    //dynamically allocating memory for 'booking' to reduce stack usage
    RESERVATION* booking = (RESERVATION*)malloc(CAPACITY * sizeof(RESERVATION));
    if (booking == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    //loading reservation data from a file
    loadFromFile(booking);

    //infinite loop for displaying options and handling inputs until exit
    while (1)
    {
        showOptions();
        handleUserInput(booking);
    }

    //freeing allocated memory before exit (in case loop exits unexpectedly)
    free(booking);
}
