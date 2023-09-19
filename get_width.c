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
for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
{
if (is_digit(format[curr_i]))
{
width *= 10;
width += format[curr_i] - '0';
}
else if (format[curr_i] == '*')
{
curr_i++;
width = va_arg(list, int);
break;
}
else
{
break;
}
}
*i = curr_i - 1;
return (width);
}

