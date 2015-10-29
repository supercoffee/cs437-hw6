#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "nacl/include/amd64/crypto_hash.h"
#include "functions.h"
#include "base64.h"

#define INT_BUFFER_LENGTH 16

#define ERROR_NON_NUMERIC_INPUT 1
#define ERROR_INT_OVERFLOW 2

int write_password_to_file(char *password) {

    FILE *password_file = fopen(PASSWORD_FILE, "w");
    if (NULL != password_file) {
        store_password(password, password_file);
        fclose(password_file);
        return 0;
    }
    return 1;
}

int store_password(char *password, FILE *output) {

    if (NULL != output) {

        unsigned char hash[crypto_hash_BYTES];
        // Invoke NaCl hash function (based on sha512) to hash the pw securely
        crypto_hash(hash, (unsigned char *) password, strlen(password));

        // Determine how long the hashed version is
        // and how long the base 64 version will be
        size_t hash_length = strlen((char *) hash);
        int encoded_length = Base64encode_len(hash_length);

        // Allocate a buffer large enough for the Base 64 version of the hash
        char *encoded_hash = (char *) calloc(encoded_length, sizeof(char));
        Base64encode(encoded_hash, (char *) hash, hash_length);

        output_to_stream(encoded_hash, output);

        return 0;
    }
    return 1;
}

void output_to_stream(char *output, FILE *stream) {
    fprintf(stream, "%s", output);
}

int seek_to_newline(FILE *stream) {

    int ch, ctr;
    for (ctr = 0; (ch = getc(stream)) != EOF && ch != '\n'; ctr++);

    return ctr;
}

void gather_string(char *buffer, size_t length, FILE *input,
                   const char *prompt) {

    if (NULL != prompt) {
        printf("%s", prompt);
    }

    if (NULL != buffer && NULL != input) {
        fgets(buffer, length, input);
        // Replace newline character with null byte.
        // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input

        size_t chars_read = strcspn(buffer, "\n");

        // If no newline occurs before the end of the string, then it must be
        // sitting on the buffer and needs to be removed.
        if (chars_read == length - 1) {
            seek_to_newline(stdin);
        } else {
            // Set newline character to null because fgets leaves it there
            buffer[chars_read] = '\0';
        }

    }
}


/**
    Convert a string into an integer.
    Caller must check error parameter to ensure
    that conversion result is accurate. The value zero is
    returned in error cases.
*/
int32_t str_to_int(const char *in, int *error) {
    char *garbage_bin = "";

    long long_val = strtol(in, &garbage_bin, 0);

    // Check if any chars were thrown away by strtol
    if (*garbage_bin != '\0') {
        //The input contained some non numeric garbage,  abort
        *error = ERROR_NON_NUMERIC_INPUT;
        return 0;
    }

    if (long_val > INT_MAX || long_val < INT_MIN) {
        *error = ERROR_INT_OVERFLOW;
        return 0;
    }

    *error = 0;
    return (int) long_val;
}
