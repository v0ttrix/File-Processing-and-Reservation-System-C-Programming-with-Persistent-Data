// Jaden Mardini - PROG71990 - SEC1 - STUDENT#876299

#pragma once 

#define MAX_CHARS 1024 // Defines the maximum number of characters for names in reservations
#define CAPACITY 12 // Defines the maximum number of seats available for reservation
#define RESERVATION_FILE "Bookings.txt" // Defines the filename for storing reservation data
#define EMPTY_NAME "Unknown" // Default placeholder for an unassigned seat name

#include <stdio.h> 
#include <stdbool.h> 
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS 
#include <string.h>

// Definition of the RESERVATION struct for storing reservation details
typedef struct reservation
{
    int seatID; // The ID or number of the seat (1 through CAPACITY)
    bool reserved; // Boolean indicating whether the seat is reserved (true) or available (false)
    char lastName[MAX_CHARS]; // Stores the last name of the passenger reserving the seat
    char firstName[MAX_CHARS]; // Stores the first name of the passenger reserving the seat
} RESERVATION; // Typedef allows us to use 'RESERVATION' instead of 'struct reservation' in code

// Function prototypes (declarations) - These provide an outline of functions used in the program

void flushInput(); // Clears the input buffer to handle any leftover data from user inputs
void handleUserInput(RESERVATION*); // Processes user input and directs to appropriate functions
void showOptions(); // Displays the menu of available options to the user
void loadFromFile(RESERVATION*); // Loads reservation data from an external file
void saveToFile(RESERVATION*); // Saves current reservation data to an external file
void deleteSeat(RESERVATION*); // Deletes a reservation for a specific seat
void bookSeat(RESERVATION*); // Assigns a seat to a passenger
void countAvailableSeats(RESERVATION*); // Counts and displays the number of available seats
void listEmptySeats(RESERVATION*); // Displays a list of all currently available seats
void displaySortedSeats(RESERVATION*); // Displays reserved seats in alphabetical order
