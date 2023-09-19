#include "main.h"

/**
 * get_width - Extracts and calculates the width for formatting.
 * @format: The formatted string containing conversion specifiers.
 * @i: Pointer to the current position in the format string.
 * @list: A list of arguments (va_list) for variable-width extraction.
 *
 * Return: The calculated width for formatting.
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i;
    int width = 0;

    // Loop through characters after the '%' symbol
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            // If a digit is encountered, accumulate it into the width
            width *= 10;
            width += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            // If a '*' is encountered, get the width from the argument list
            curr_i++;
            width = va_arg(list, int);
            break;
        }
        else
        {
            // If a non-digit character is encountered, exit the loop
            break;
        }
    }

    // Update the position in the format string based on the width specifier
    *i = curr_i - 1;

    return width;
}

