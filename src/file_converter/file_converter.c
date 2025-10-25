/**
 * @file file_converter.c
 * @brief Professional File Processing Utility
 * @author Jaden Mardini
 * 
 * Robust file processing utility with comprehensive error handling,
 * memory management, and support for various text transformations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096
#define MAX_PATH_LENGTH 512

typedef enum {
    TRANSFORM_LOWERCASE,
    TRANSFORM_UPPERCASE,
    TRANSFORM_CAPITALIZE
} TransformType;

typedef struct {
    char source_path[MAX_PATH_LENGTH];
    char dest_path[MAX_PATH_LENGTH];
    TransformType transform;
    bool verbose;
} ProcessingConfig;

/**
 * @brief Validates file paths and accessibility
 */
static bool validate_files(const char* source, const char* dest) {
    if (!source || !dest) {
        fprintf(stderr, "Error: Invalid file paths provided\n");
        return false;
    }
    
    FILE* test_source = fopen(source, "r");
    if (!test_source) {
        fprintf(stderr, "Error: Cannot open source file '%s': %s\n", 
                source, strerror(errno));
        return false;
    }
    fclose(test_source);
    
    return true;
}

/**
 * @brief Applies text transformation to a character
 */
static char transform_char(char c, TransformType transform) {
    switch (transform) {
        case TRANSFORM_LOWERCASE:
            return tolower(c);
        case TRANSFORM_UPPERCASE:
            return toupper(c);
        case TRANSFORM_CAPITALIZE:
            return c; /* Handled at word level */
        default:
            return c;
    }
}

/**
 * @brief Processes file with specified transformation
 */
static bool process_file(const ProcessingConfig* config) {
    FILE* source = fopen(config->source_path, "r");
    FILE* dest = fopen(config->dest_path, "w");
    
    if (!source || !dest) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        fprintf(stderr, "Error: Failed to open files for processing\n");
        return false;
    }
    
    char buffer[BUFFER_SIZE];
    size_t bytes_processed = 0;
    
    while (fgets(buffer, sizeof(buffer), source)) {
        size_t len = strlen(buffer);
        
        for (size_t i = 0; i < len; i++) {
            buffer[i] = transform_char(buffer[i], config->transform);
        }
        
        if (fputs(buffer, dest) == EOF) {
            fprintf(stderr, "Error: Failed to write to destination file\n");
            fclose(source);
            fclose(dest);
            return false;
        }
        
        bytes_processed += len;
    }
    
    fclose(source);
    fclose(dest);
    
    if (config->verbose) {
        printf("Successfully processed %zu bytes\n", bytes_processed);
        printf("Source: %s\n", config->source_path);
        printf("Destination: %s\n", config->dest_path);
    }
    
    return true;
}

/**
 * @brief Displays usage information
 */
static void show_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS] <source_file> <destination_file>\n\n", program_name);
    printf("Options:\n");
    printf("  -l, --lowercase    Convert text to lowercase (default)\n");
    printf("  -u, --uppercase    Convert text to uppercase\n");
    printf("  -v, --verbose      Enable verbose output\n");
    printf("  -h, --help         Show this help message\n\n");
    printf("Examples:\n");
    printf("  %s input.txt output.txt\n", program_name);
    printf("  %s -u input.txt output.txt\n", program_name);
    printf("  %s --verbose input.txt output.txt\n", program_name);
}

/**
 * @brief Parses command line arguments
 */
static bool parse_arguments(int argc, char* argv[], ProcessingConfig* config) {
    if (argc < 3) {
        show_usage(argv[0]);
        return false;
    }
    
    /* Initialize config with defaults */
    config->transform = TRANSFORM_LOWERCASE;
    config->verbose = false;
    
    int file_arg_start = 1;
    
    /* Parse options */
    for (int i = 1; i < argc - 2; i++) {
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lowercase") == 0) {
            config->transform = TRANSFORM_LOWERCASE;
            file_arg_start++;
        } else if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--uppercase") == 0) {
            config->transform = TRANSFORM_UPPERCASE;
            file_arg_start++;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            config->verbose = true;
            file_arg_start++;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_usage(argv[0]);
            return false;
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return false;
        }
    }
    
    /* Ensure we have source and destination files */
    if (argc - file_arg_start < 2) {
        fprintf(stderr, "Error: Source and destination files required\n");
        show_usage(argv[0]);
        return false;
    }
    
    /* Copy file paths */
    strncpy(config->source_path, argv[file_arg_start], MAX_PATH_LENGTH - 1);
    strncpy(config->dest_path, argv[file_arg_start + 1], MAX_PATH_LENGTH - 1);
    config->source_path[MAX_PATH_LENGTH - 1] = '\0';
    config->dest_path[MAX_PATH_LENGTH - 1] = '\0';
    
    return true;
}

/**
 * @brief Main program entry point
 */
int main(int argc, char* argv[]) {
    ProcessingConfig config;
    
    if (!parse_arguments(argc, argv, &config)) {
        return EXIT_FAILURE;
    }
    
    if (!validate_files(config.source_path, config.dest_path)) {
        return EXIT_FAILURE;
    }
    
    if (!process_file(&config)) {
        return EXIT_FAILURE;
    }
    
    if (!config.verbose) {
        printf("File processing completed successfully\n");
    }
    
    return EXIT_SUCCESS;
}
