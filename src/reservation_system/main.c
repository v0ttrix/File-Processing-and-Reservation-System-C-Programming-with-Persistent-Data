/**
 * @file main.c
 * @brief Reservation System Main Program
 * @author Jaden Mardini
 */

#include "reservation_system.h"
#include <stdio.h>
#include <stdlib.h>

static void show_menu(void) {
    printf("\n=== Airline Reservation System ===\n");
    printf("1. Book a seat\n");
    printf("2. Cancel reservation\n");
    printf("3. Show available seats\n");
    printf("4. Show all reservations\n");
    printf("5. Save and exit\n");
    printf("Enter choice: ");
}

static void book_seat(ReservationSystem* system) {
    int seat;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    
    printf("Enter seat number (1-%d): ", MAX_SEATS);
    if (scanf("%d", &seat) != 1) {
        printf("Invalid input\n");
        return;
    }
    
    printf("Enter first name: ");
    if (scanf("%63s", first_name) != 1) {
        printf("Invalid input\n");
        return;
    }
    
    printf("Enter last name: ");
    if (scanf("%63s", last_name) != 1) {
        printf("Invalid input\n");
        return;
    }
    
    ReservationResult result = reservation_make(system, seat, first_name, last_name);
    if (result == RESERVATION_SUCCESS) {
        printf("Seat %d booked successfully for %s %s\n", seat, first_name, last_name);
    } else {
        printf("Error: %s\n", reservation_error_string(result));
    }
}

static void cancel_seat(ReservationSystem* system) {
    int seat;
    
    printf("Enter seat number to cancel (1-%d): ", MAX_SEATS);
    if (scanf("%d", &seat) != 1) {
        printf("Invalid input\n");
        return;
    }
    
    ReservationResult result = reservation_cancel(system, seat);
    if (result == RESERVATION_SUCCESS) {
        printf("Seat %d cancelled successfully\n", seat);
    } else {
        printf("Error: %s\n", reservation_error_string(result));
    }
}

static void show_available(ReservationSystem* system) {
    printf("\nAvailable seats: ");
    bool found = false;
    
    for (int i = 1; i <= MAX_SEATS; i++) {
        if (reservation_is_available(system, i)) {
            printf("%d ", i);
            found = true;
        }
    }
    
    if (!found) {
        printf("None");
    }
    printf("\n");
}

static void show_reservations(ReservationSystem* system) {
    printf("\nCurrent Reservations:\n");
    printf("Seat  Name\n");
    printf("----  ----\n");
    
    Reservation seats[MAX_SEATS];
    int count = reservation_get_all_seats(system, seats, MAX_SEATS);
    
    if (count < 0) {
        printf("Error retrieving reservations\n");
        return;
    }
    
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (seats[i].is_reserved) {
            printf("%-4d  %s %s\n", 
                   seats[i].seat_number,
                   seats[i].first_name,
                   seats[i].last_name);
            found = true;
        }
    }
    
    if (!found) {
        printf("No reservations found\n");
    }
}

int main(void) {
    ReservationSystem* system = reservation_system_create();
    if (!system) {
        fprintf(stderr, "Failed to create reservation system\n");
        return EXIT_FAILURE;
    }
    
    reservation_system_load(system);
    
    int choice;
    while (1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n'); /* Clear input buffer */
            continue;
        }
        
        switch (choice) {
            case 1:
                book_seat(system);
                break;
            case 2:
                cancel_seat(system);
                break;
            case 3:
                show_available(system);
                break;
            case 4:
                show_reservations(system);
                break;
            case 5:
                reservation_system_save(system);
                printf("Data saved. Goodbye!\n");
                reservation_system_destroy(system);
                return EXIT_SUCCESS;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
