#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Handles the printing of a single character.
 * @c: The character to print.
 * @buffer: Buffer array to handle printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
                      int flags, int width, int precision, int size)
{
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    // Check if zero-padding is required
    if (flags & F_ZERO)
        padd = '0';

    // Add the character to the buffer
    buffer[i++] = c;
    buffer[i] = '\0';

    // Handle width formatting
    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) +
                    write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
                    write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Handles the printing of a number.
 * @is_negative: Indicates if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
                int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    // Check if zero-padding is required
    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    // Determine the extra character ('-', '+', or ' ')
    if (is_negative)
        extra_ch = '-';
    else if (flags & F_PLUS)
        extra_ch = '+';
    else if (flags & F_SPACE)
        extra_ch = ' ';

    return (write_num(ind, buffer, flags, width, precision,
                      length, padd, extra_ch));
}

/**
 * write_num - Writes a number using a buffer.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer.
 * @flags: Flags.
 * @width: Width.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Padding character.
 * @extra_c: Extra character.
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[], int flags, int width, int prec,
              int length, char padd, char extra_c)
{
    int i, padd_start = 1;

    // Handle the case when precision is 0 and the number is zero
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return (0); // printf(".0d", 0) - no character is printed

    // Handle the case when precision is 0 and the number is zero
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
    {
        buffer[ind] = padd = ' '; // Display width with padding ' '
    }

    // Pad the number with zeros for precision
    if (prec > 0 && prec < length)
        padd = ' ';

    while (prec > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    // If an extra character is present, increase the length
    if (extra_c != 0)
        length++;

    // Handle width formatting
    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ')
        {
            // Extra character is assigned to the left of the buffer
            if (extra_c)
                buffer[--ind] = extra_c;

            return (write(1, &buffer[ind], length) +
                    write(1, &buffer[1], i - 1));
        }
        else
        {
            // Extra character is assigned to the left of the padding
            if (extra_c)
                buffer[--ind] = extra_c;

            return (write(1, &buffer[1], i - 1) +
                    write(1, &buffer[ind], length));
        }
    }

    // If an extra character is present, assign it to the left of the buffer
    if (extra_c)
        buffer[--ind] = extra_c;

    return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Handles the writing of an unsigned number.
 * @is_negative: Indicates if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters written.
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
                  int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    // Handle the case when precision is 0 and the number is zero
    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0); // printf(".0d", 0) - no character is printed

    // Pad the number with zeros for precision
    if (precision > 0 && precision < length)
        padd = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    // Check if zero-padding is required
    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    // Handle width formatting
    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS)
        {
            // Extra character is assigned to the left of the buffer [buffer > padd]
            return

