/**
 * @file reservation_system.c
 * @brief Reservation System Implementation
 * @author Jaden Mardini
 */

#include "reservation_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ReservationSystem {
    Reservation seats[MAX_SEATS];
    bool initialized;
};

ReservationSystem* reservation_system_create(void) {
    ReservationSystem* system = malloc(sizeof(ReservationSystem));
    if (!system) return NULL;
    
    for (int i = 0; i < MAX_SEATS; i++) {
        system->seats[i].seat_number = i + 1;
        system->seats[i].is_reserved = false;
        strcpy(system->seats[i].first_name, "");
        strcpy(system->seats[i].last_name, "");
    }
    system->initialized = true;
    return system;
}

void reservation_system_destroy(ReservationSystem* system) {
    if (system) {
        free(system);
    }
}

ReservationResult reservation_make(ReservationSystem* system, int seat_number,
                                 const char* first_name, const char* last_name) {
    if (!system || !reservation_is_valid_seat(seat_number)) {
        return RESERVATION_ERROR_INVALID_SEAT;
    }
    
    if (!reservation_is_valid_name(first_name) || !reservation_is_valid_name(last_name)) {
        return RESERVATION_ERROR_INVALID_NAME;
    }
    
    int index = seat_number - 1;
    if (system->seats[index].is_reserved) {
        return RESERVATION_ERROR_SEAT_OCCUPIED;
    }
    
    system->seats[index].is_reserved = true;
    strncpy(system->seats[index].first_name, first_name, MAX_NAME_LENGTH - 1);
    strncpy(system->seats[index].last_name, last_name, MAX_NAME_LENGTH - 1);
    system->seats[index].first_name[MAX_NAME_LENGTH - 1] = '\0';
    system->seats[index].last_name[MAX_NAME_LENGTH - 1] = '\0';
    
    return RESERVATION_SUCCESS;
}

ReservationResult reservation_cancel(ReservationSystem* system, int seat_number) {
    if (!system || !reservation_is_valid_seat(seat_number)) {
        return RESERVATION_ERROR_INVALID_SEAT;
    }
    
    int index = seat_number - 1;
    if (!system->seats[index].is_reserved) {
        return RESERVATION_ERROR_SEAT_EMPTY;
    }
    
    system->seats[index].is_reserved = false;
    strcpy(system->seats[index].first_name, "");
    strcpy(system->seats[index].last_name, "");
    
    return RESERVATION_SUCCESS;
}

bool reservation_is_available(const ReservationSystem* system, int seat_number) {
    if (!system || !reservation_is_valid_seat(seat_number)) {
        return false;
    }
    return !system->seats[seat_number - 1].is_reserved;
}

int reservation_count_available(const ReservationSystem* system) {
    if (!system) return -1;
    
    int count = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (!system->seats[i].is_reserved) {
            count++;
        }
    }
    return count;
}

bool reservation_is_valid_seat(int seat_number) {
    return seat_number >= 1 && seat_number <= MAX_SEATS;
}

bool reservation_is_valid_name(const char* name) {
    return name && strlen(name) > 0 && strlen(name) < MAX_NAME_LENGTH;
}

const char* reservation_error_string(ReservationResult result) {
    switch (result) {
        case RESERVATION_SUCCESS: return "Success";
        case RESERVATION_ERROR_INVALID_SEAT: return "Invalid seat number";
        case RESERVATION_ERROR_SEAT_OCCUPIED: return "Seat already occupied";
        case RESERVATION_ERROR_SEAT_EMPTY: return "Seat is empty";
        case RESERVATION_ERROR_INVALID_NAME: return "Invalid name";
        case RESERVATION_ERROR_FILE_IO: return "File I/O error";
        case RESERVATION_ERROR_MEMORY: return "Memory allocation error";
        default: return "Unknown error";
    }
}

ReservationResult reservation_system_load(ReservationSystem* system) {
    if (!system) return RESERVATION_ERROR_SYSTEM;
    
    FILE* file = fopen(RESERVATION_FILE, "rb");
    if (!file) return RESERVATION_SUCCESS; /* File doesn't exist yet */
    
    size_t read = fread(system->seats, sizeof(Reservation), MAX_SEATS, file);
    fclose(file);
    
    return (read == MAX_SEATS) ? RESERVATION_SUCCESS : RESERVATION_ERROR_FILE_IO;
}

ReservationResult reservation_system_save(const ReservationSystem* system) {
    if (!system) return RESERVATION_ERROR_SYSTEM;
    
    FILE* file = fopen(RESERVATION_FILE, "wb");
    if (!file) return RESERVATION_ERROR_FILE_IO;
    
    size_t written = fwrite(system->seats, sizeof(Reservation), MAX_SEATS, file);
    fclose(file);
    
    return (written == MAX_SEATS) ? RESERVATION_SUCCESS : RESERVATION_ERROR_FILE_IO;
}

int reservation_get_all_seats(const ReservationSystem* system, 
                            Reservation* reservations, 
                            size_t max_seats) {
    if (!system || !reservations || max_seats < MAX_SEATS) {
        return -1;
    }
    
    for (int i = 0; i < MAX_SEATS; i++) {
        reservations[i] = system->seats[i];
    }
    
    return MAX_SEATS;
}
