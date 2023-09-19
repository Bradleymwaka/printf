#include "main.h"

/**
 * get_size - Extracts and calculates the size specifier for formatting.
 * @format: The formatted string containing conversion specifiers.
 * @i: Pointer to the current position in the format string.
 *
 * Return: The calculated size specifier (S_LONG, S_SHORT, or 0 if none).
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    // Check if the size specifier is 'l' for long or 'h' for short
    if (format[curr_i] == 'l')
        size = S_LONG;
    else if (format[curr_i] == 'h')
        size = S_SHORT;

    // Update the position in the format string based on the size specifier
    if (size == 0)
        *i = curr_i - 1;
    else
        *i = curr_i;

    return size;
}

