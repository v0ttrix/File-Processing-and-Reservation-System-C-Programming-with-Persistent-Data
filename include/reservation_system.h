/**
 * @file reservation_system.h
 * @brief Professional Airline Reservation System Interface
 * @author Jaden Mardini
 * 
 * Comprehensive airline reservation system with persistent data storage,
 * robust error handling, and professional API design.
 */

#ifndef RESERVATION_SYSTEM_H
#define RESERVATION_SYSTEM_H

#include <stdbool.h>
#include <stddef.h>

/* Constants */
#define MAX_NAME_LENGTH 64
#define MAX_SEATS 12
#define RESERVATION_FILE "reservations.dat"

/* Error codes */
typedef enum {
    RESERVATION_SUCCESS = 0,
    RESERVATION_ERROR_INVALID_SEAT,
    RESERVATION_ERROR_SEAT_OCCUPIED,
    RESERVATION_ERROR_SEAT_EMPTY,
    RESERVATION_ERROR_INVALID_NAME,
    RESERVATION_ERROR_FILE_IO,
    RESERVATION_ERROR_MEMORY,
    RESERVATION_ERROR_SYSTEM
} ReservationResult;

/* Reservation structure */
typedef struct {
    int seat_number;                    /* Seat number (1-MAX_SEATS) */
    bool is_reserved;                   /* Reservation status */
    char first_name[MAX_NAME_LENGTH];   /* Passenger first name */
    char last_name[MAX_NAME_LENGTH];    /* Passenger last name */
} Reservation;

/* System structure */
typedef struct ReservationSystem ReservationSystem;

/**
 * @brief Creates a new reservation system
 * @return Pointer to system or NULL on failure
 */
ReservationSystem* reservation_system_create(void);

/**
 * @brief Destroys reservation system and frees memory
 * @param system Pointer to system
 */
void reservation_system_destroy(ReservationSystem* system);

/**
 * @brief Loads reservations from persistent storage
 * @param system Pointer to system
 * @return RESERVATION_SUCCESS on success, error code on failure
 */
ReservationResult reservation_system_load(ReservationSystem* system);

/**
 * @brief Saves reservations to persistent storage
 * @param system Pointer to system
 * @return RESERVATION_SUCCESS on success, error code on failure
 */
ReservationResult reservation_system_save(const ReservationSystem* system);

/**
 * @brief Makes a seat reservation
 * @param system Pointer to system
 * @param seat_number Seat number (1-MAX_SEATS)
 * @param first_name Passenger first name
 * @param last_name Passenger last name
 * @return RESERVATION_SUCCESS on success, error code on failure
 */
ReservationResult reservation_make(ReservationSystem* system, 
                                 int seat_number,
                                 const char* first_name, 
                                 const char* last_name);

/**
 * @brief Cancels a seat reservation
 * @param system Pointer to system
 * @param seat_number Seat number to cancel
 * @return RESERVATION_SUCCESS on success, error code on failure
 */
ReservationResult reservation_cancel(ReservationSystem* system, int seat_number);

/**
 * @brief Gets reservation information for a seat
 * @param system Pointer to system
 * @param seat_number Seat number to query
 * @param reservation Pointer to store reservation data
 * @return RESERVATION_SUCCESS on success, error code on failure
 */
ReservationResult reservation_get(const ReservationSystem* system, 
                                int seat_number, 
                                Reservation* reservation);

/**
 * @brief Gets all reservations for display purposes
 * @param system Pointer to system
 * @param reservations Array to store all seat data
 * @param max_seats Maximum number of seats to return
 * @return Number of seats returned, or -1 on error
 */
int reservation_get_all_seats(const ReservationSystem* system, 
                            Reservation* reservations, 
                            size_t max_seats);

/**
 * @brief Checks if a seat is available
 * @param system Pointer to system
 * @param seat_number Seat number to check
 * @return true if available, false otherwise
 */
bool reservation_is_available(const ReservationSystem* system, int seat_number);

/**
 * @brief Gets count of available seats
 * @param system Pointer to system
 * @return Number of available seats, or -1 on error
 */
int reservation_count_available(const ReservationSystem* system);

/**
 * @brief Gets list of available seat numbers
 * @param system Pointer to system
 * @param seats Array to store available seat numbers
 * @param max_seats Maximum number of seats to return
 * @return Number of available seats found, or -1 on error
 */
int reservation_list_available(const ReservationSystem* system, 
                             int* seats, 
                             size_t max_seats);

/**
 * @brief Gets list of all reservations sorted by last name
 * @param system Pointer to system
 * @param reservations Array to store reservations
 * @param max_reservations Maximum number of reservations to return
 * @return Number of reservations found, or -1 on error
 */
int reservation_list_sorted(const ReservationSystem* system, 
                          Reservation* reservations, 
                          size_t max_reservations);

/**
 * @brief Converts error code to human-readable string
 * @param result Error code
 * @return String description of error
 */
const char* reservation_error_string(ReservationResult result);

/**
 * @brief Validates seat number
 * @param seat_number Seat number to validate
 * @return true if valid, false otherwise
 */
bool reservation_is_valid_seat(int seat_number);

/**
 * @brief Validates passenger name
 * @param name Name to validate
 * @return true if valid, false otherwise
 */
bool reservation_is_valid_name(const char* name);

#endif /* RESERVATION_SYSTEM_H */
