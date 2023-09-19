#include "main.h"

/**
 * get_flags - Extracts and calculates active formatting flags from a format string.
 * @format: The formatted string containing conversion specifiers.
 * @i: Pointer to the current position in the format string.
 *
 * Return: Flags representing the active formatting options.
 */
int get_flags(const char *format, int *i)
{
    // List of possible flag characters in the format string
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};

    // Corresponding flag values for each character
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    int j, curr_i;
    int flags = 0;

    // Iterate through the characters following the '%' symbol
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        // Check if the current character is one of the flag characters
        for (j = 0; FLAGS_CH[j] != '\0'; j++)
        {
            if (format[curr_i] == FLAGS_CH[j])
            {
                // If a flag character is found, set the corresponding flag bit
                flags |= FLAGS_ARR[j];
                break;
            }
        }

        // If the character is not a flag character, exit the loop
        if (FLAGS_CH[j] == '\0')
            break;
    }

    // Update the position in the format string
    *i = curr_i - 1;

    return flags;
}

