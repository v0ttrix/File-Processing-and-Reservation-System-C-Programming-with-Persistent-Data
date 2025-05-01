// Jaden Mardini
//all the work from <main.c>

#define _CRT_SECURE_NO_WARNINGS
#include "reservations.h"
#include <stdlib.h> //needed for dynamic memory functions like malloc and free

//flushes out leftover characters from the input buffer.
//this helps prevent errors when reading user input, especially after scanf.
void flushInput()
{
    char input;
    while ((input = getchar()) != '\n' && input != EOF) {};
}

//counts how many seats are not reserved and prints the total available.
//loops through the booking array to check each seat's reservation status.
void countAvailableSeats(RESERVATION* booking)
{
    int availableSeats = 0;

    // Go through each seat in the array
    for (int i = 0; i < CAPACITY; i++)
    {
        //if the seat isn't reserved, add to the count
        if (!booking[i].reserved)
        {
            availableSeats++;
        }
    }
    //show the total number of free seats
    printf("Currently, %d seats are available.\n", availableSeats);
}

//lists out all the empty seats, showing the seat number for each.
//this is useful for showing users which seats they can reserve.
void listEmptySeats(RESERVATION* booking)
{
    for (int i = 0; i < CAPACITY; i++)
    {
        // If the seat isn’t taken, print its number
        if (!booking[i].reserved)
        {
            printf("Available Seat: %d\n", booking[i].seatID);
        }
    }
}

//sorts and displays the reserved seats alphabetically.
// allows sorting by first or last name based on user preference.
void displaySortedSeats(RESERVATION* booking)
{
    //allocate memory for arrays to store seat data
    //dynamic allocation helps avoid stack overflow for large data.
    char (*firstNames)[MAX_CHARS] = malloc(CAPACITY * MAX_CHARS * sizeof(char));
    char (*lastNames)[MAX_CHARS] = malloc(CAPACITY * MAX_CHARS * sizeof(char));
    int* seatIDs = malloc(CAPACITY * sizeof(int));
    int sortedChoice = 0; // 0 for last name, 1 for first name

    //check if memory allocation worked; if not, exit to avoid crashes
    if (firstNames == NULL || lastNames == NULL || seatIDs == NULL)
    {
        printf("Memory allocation failed.\n");
        free(firstNames);
        free(lastNames);
        free(seatIDs);
        return;
    }

    //ask the user how to sort: by first name or last name
    printf("Enter 1 for alphabetical by first name or 0 for last name: ");
    if (scanf("%d", &sortedChoice) != 1 || (sortedChoice != 0 && sortedChoice != 1))
    {
        //if input is invalid, clear the buffer and set default to last name
        flushInput();
        printf("Invalid input. Defaulting to last name.\n");
        sortedChoice = 0;
    }

    //copy data from booking array to temporary arrays for sorting
    for (int i = 0; i < CAPACITY; i++)
    {
        strcpy(firstNames[i], booking[i].firstName);
        strcpy(lastNames[i], booking[i].lastName);
        seatIDs[i] = booking[i].seatID;
    }

    //simple bubble sort to arrange by first or last name based on user choice
    for (int i = 0; i < CAPACITY - 1; i++)
    {
        for (int j = 0; j < CAPACITY - i - 1; j++)
        {
            //compare and swap if necessary based on sortedChoice
            if ((sortedChoice == 1 && strcmp(firstNames[j], firstNames[j + 1]) > 0) ||
                (sortedChoice == 0 && strcmp(lastNames[j], lastNames[j + 1]) > 0))
            {
                //temporary storage for swapping
                char tempName[MAX_CHARS];
                int tempID = seatIDs[j];

                //swap first names
                strcpy(tempName, firstNames[j]);
                strcpy(firstNames[j], firstNames[j + 1]);
                strcpy(firstNames[j + 1], tempName);

                //swap last names
                strcpy(tempName, lastNames[j]);
                strcpy(lastNames[j], lastNames[j + 1]);
                strcpy(lastNames[j + 1], tempName);

                //swap seat numbers so data stays consistent
                seatIDs[j] = seatIDs[j + 1];
                seatIDs[j + 1] = tempID;
            }
        }
    }

    //display sorted list of reserved seats
    for (int i = 0; i < CAPACITY; i++)
    {
        if (booking[i].reserved)
        {
            printf("Seat %d: %s %s\n", seatIDs[i], firstNames[i], lastNames[i]);
        }
    }

    //free the dynamically allocated memory to avoid memory leaks
    free(firstNames);
    free(lastNames);
    free(seatIDs);
}

//assigns a seat to a passenger by taking their seat number, first name, and last name.
//verifies that the seat is available, then confirms with the user.
void bookSeat(RESERVATION* booking)
{
    int seatNum = 0; // User-selected seat number
    char firstName[MAX_CHARS] = ""; // fgirst name of the passenger
    char lastName[MAX_CHARS] = ""; //last name of the passenger

    //ask user for a seat number and make sure it’s valid
    printf("Enter seat number to reserve: ");
    while (scanf("%d", &seatNum) != 1 || seatNum < 1 || seatNum > CAPACITY || booking[seatNum - 1].reserved)
    {
        flushInput(); //clear buffer on invalid input
        printf("Invalid or taken seat. Try another seat number: ");
    }

    //get the passenger’s first name
    printf("Enter first name: ");
    if (scanf("%1023s", firstName) != 1)
    {
        printf("Error reading first name.\n");
        return; //exit if reading fails
    }
    firstName[MAX_CHARS - 1] = '\0'; //ensure null termination

    //get the passenger’s last name
    printf("Enter last name: ");
    if (scanf("%1023s", lastName) != 1)
    {
        printf("Error reading last name.\n");
        return; //exit if reading fails
    }
    lastName[MAX_CHARS - 1] = '\0'; //ensure null termination

    //confirm the reservation before finalizing
    printf("Confirm reservation for %s %s at seat %d? Enter 1 to confirm, 0 to cancel: ", firstName, lastName, seatNum);
    int confirmation = 0;
    while (scanf("%d", &confirmation) != 1 || (confirmation != 0 && confirmation != 1))
    {
        flushInput();
        printf("Invalid input. Confirm with 1 or cancel with 0: ");
    }

    //update booking if confirmed
    if (confirmation == 1)
    {
        seatNum--; //adjust for zero-based indexing
        strcpy(booking[seatNum].firstName, firstName);
        strcpy(booking[seatNum].lastName, lastName);
        booking[seatNum].reserved = true; //mark as reserved
    }
}

// Removes a reservation from a seat and resets the seat to default values.
void deleteSeat(RESERVATION* booking)
{
    int seatNum = 0;

    //get the seat number to delete, and ensure it’s valid and reserved
    printf("Enter seat number to delete: ");
    while (scanf("%d", &seatNum) != 1 || seatNum < 1 || seatNum > CAPACITY || !booking[seatNum - 1].reserved)
    {
        flushInput();
        printf("Invalid or empty seat. Try another seat number: ");
    }

    //reset the seat info to "Unknown" and mark it as available
    seatNum--;
    booking[seatNum].reserved = false;
    strcpy(booking[seatNum].firstName, EMPTY_NAME);
    strcpy(booking[seatNum].lastName, EMPTY_NAME);
}

//displays the main menu of options for the program
void showOptions(void)
{
    printf("To choose a function, enter its letter label:\n");
    printf("a) Show number of empty seats\n");
    printf("b) Show list of empty seats\n");
    printf("c) Show alphabetical list (by passenger name) of seats\n");
    printf("d) Assign a customer to a seat assignment\n");
    printf("e) Delete a seat assignment\n");
    printf("f) Quit\n");
}

//reads the user's choice from the menu and calls the relevant function
void handleUserInput(RESERVATION* booking)
{
    char choice;
    printf("Enter your choice: ");

    // Check if scanf successfully reads a character
    if (scanf(" %c", &choice) != 1) {
        printf("Error reading input. Please try again.\n");
        flushInput(); // Clear input buffer in case of error
        return; // Exit the function early if input fails
    }

    //switch-case to handle each menu option
    switch (choice)
    {
    case 'a':
        countAvailableSeats(booking);
        break;
    case 'b':
        listEmptySeats(booking);
        break;
    case 'c':
        displaySortedSeats(booking);
        break;
    case 'd':
        bookSeat(booking);
        break;
    case 'e':
        deleteSeat(booking);
        break;
    case 'f':
        free(booking); //free dynamically allocated memory before quitting
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
    }
}

//loads data from the file into the booking array, initializing seat info
void loadFromFile(RESERVATION* booking)
{
    FILE* file = fopen(RESERVATION_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    //reads seat data line by line and assigns it to booking array
    for (int i = 0; i < CAPACITY; i++)
    {
        int reservedInt = 0; //temp int to store reserved status
        int result = fscanf(file, "%d %d %1023s %1023s", &booking[i].seatID, &reservedInt, booking[i].firstName, booking[i].lastName);
        if (result != 4)
        {
            printf("Error reading from file.\n");
            break;
        }
        booking[i].reserved = (reservedInt != 0); //convert int to bool
    }

    fclose(file); //close file after reading
}
