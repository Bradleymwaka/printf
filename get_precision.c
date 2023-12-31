#include "main.h"

/**
 * get_precision - Extracts and calculates the precision for formatting.
 * @format: The formatted string containing conversion specifiers.
 * @i: Pointer to the current position in the format string.
 * @list: The list of arguments to be printed.
 *
 * Return: The calculated precision value or
 * -1 if no precision is specified.
 */
int get_precision(const char *format, int *i, va_list list)
{
int curr_i = *i + 1;
int precision = -1;
if (format[curr_i] != '.')
return (precision);
precision = 0;
for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
{
if (is_digit(format[curr_i]))
{
precision *= 10;
precision += format[curr_i] - '0';
}
else if (format[curr_i] == '*')
{
curr_i++;
precision = va_arg(list, int);
break;
}
else
{
break;
}
}
*i = curr_i - 1;
return (precision);
}
