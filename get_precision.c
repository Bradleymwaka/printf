#include "main.h"

/**
 * get_precision - Extracts and calculates the precision for formatting.
 * @format: The formatted string containing conversion specifiers.
 * @i: Pointer to the current position in the format string.
 * @list: The list of arguments to be printed.
 *
 * Return: The calculated precision value or -1 if no precision is specified.
 */
int get_precision(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precision = -1;

    // Check if the precision is specified with a period ('.')
    if (format[curr_i] != '.')
        return precision;

    precision = 0;

    for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
    {
        // If the character is a digit, update the precision value
        if (is_digit(format[curr_i]))
        {
            precision *= 10;
            precision += format[curr_i] - '0';
        }
        // If the character is '*', get the precision from the argument list
        else if (format[curr_i] == '*')
        {
            curr_i++;
            precision = va_arg(list, int);
            break;
        }
        // If the character is not a digit or '*', exit the loop
        else
        {
            break;
        }
    }

    // Update the position in the format string
    *i = curr_i - 1;

    return precision;
}

