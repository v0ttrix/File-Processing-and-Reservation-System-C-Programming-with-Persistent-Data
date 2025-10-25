# File Processing and Reservation System

## Overview

Professional C programming project demonstrating file I/O operations, data persistence, and system design. This project includes two main components: a robust file processing utility and a comprehensive airline reservation system.

## Project Structure

```
File-Processing-and-Reservation-System-C-Programming-with-Persistent-Data/
├── src/
│   ├── file_converter/         # File processing utilities
│   └── reservation_system/     # Airline reservation system
├── include/                    # Header files
├── tests/                      # Unit tests
├── bin/                        # Compiled executables
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## Components

### 1. File Processing Utility

A robust file converter that transforms text files with various options:

**Features:**
- Text case conversion (lowercase, uppercase)
- Comprehensive error handling
- Command-line argument parsing
- Large file support with buffered I/O
- Verbose output mode

**Usage:**
```bash
./bin/file_converter [OPTIONS] <source_file> <destination_file>

Options:
  -l, --lowercase    Convert text to lowercase (default)
  -u, --uppercase    Convert text to uppercase
  -v, --verbose      Enable verbose output
  -h, --help         Show help message
```

### 2. Airline Reservation System

Professional reservation management system for airline seating:

**Features:**
- Seat booking and cancellation
- Persistent data storage
- Passenger name management
- Available seat tracking
- Sorted reservation listings
- Comprehensive error handling

**Capabilities:**
- 12-seat capacity management
- Binary file persistence
- Input validation
- Memory safety
- Professional API design

## Building the Project

### Prerequisites
- GCC compiler (C11 standard)
- Make utility
- Standard C library

### Compilation
```bash
# Build all components
make all

# Build specific components
make file_converter
make reservation_system

# Run tests
make test

# Clean build artifacts
make clean
```

## Usage Examples

### File Converter
```bash
# Convert file to lowercase
./bin/file_converter input.txt output.txt

# Convert to uppercase with verbose output
./bin/file_converter -u -v input.txt output.txt
```

### Reservation System
```bash
# Run the reservation system
./bin/reservation_system
```

The reservation system provides an interactive menu with options to:
1. Book a seat
2. Cancel reservation
3. View available seats
4. List all reservations
5. Save and exit

## Technical Features

### Error Handling
- Comprehensive error codes and messages
- Input validation for all user data
- File I/O error checking
- Memory allocation verification

### Memory Management
- Proper allocation and deallocation
- No memory leaks (valgrind verified)
- Bounds checking for all arrays
- Safe string operations

### File I/O
- Binary file format for reservations
- Buffered I/O for performance
- Cross-platform file handling
- Atomic save operations

### Code Quality
- C11 standard compliance
- Professional naming conventions
- Comprehensive documentation
- Modular design principles

## API Documentation

### File Converter
The file converter is a standalone utility with command-line interface.

### Reservation System API
```c
// System management
ReservationSystem* reservation_system_create(void);
void reservation_system_destroy(ReservationSystem* system);

// Data persistence
ReservationResult reservation_system_load(ReservationSystem* system);
ReservationResult reservation_system_save(const ReservationSystem* system);

// Reservation operations
ReservationResult reservation_make(ReservationSystem* system, 
                                 int seat_number,
                                 const char* first_name, 
                                 const char* last_name);
ReservationResult reservation_cancel(ReservationSystem* system, int seat_number);

// Query operations
bool reservation_is_available(const ReservationSystem* system, int seat_number);
int reservation_count_available(const ReservationSystem* system);
int reservation_list_available(const ReservationSystem* system, int* seats, size_t max_seats);
```

## Testing

The project includes comprehensive testing:

```bash
make test
```

Tests cover:
- File processing functionality
- Reservation system operations
- Error handling scenarios
- Memory management
- File I/O operations

## Design Principles

1. **Modularity** - Clear separation of concerns
2. **Error Handling** - Comprehensive validation and reporting
3. **Memory Safety** - Proper allocation and cleanup
4. **Performance** - Efficient algorithms and I/O
5. **Maintainability** - Clean code and documentation

## Author

Jaden Mardini - Computer Science Student

## License

This project is for educational purposes.
