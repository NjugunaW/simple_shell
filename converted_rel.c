#include "chwa.h"

/**
 * err2int - a fnctn that converts a string input into an integer
 * @s: the string
 * Return: 0 if theres is no numbr in string or converted number
 *       -1 on error
 */
int err2int(char *s)
{
/*Declaration of variables initialized to '0'*/
	int numbr = 0;
	unsigned long int res = 0;
/*if fncnt to check whether chars in s are '+'*/
	if (*s == '+')
		s++;
/*for loop to iterate over chars in 's' and convert to integers*/
	for (numbr = 0;  s[numbr] != '\0'; numbr++)
	{
		if (s[numbr] >= '0' && s[numbr] <= '9')
		{
			res *= 10;
			res += (s[numbr] - '0');
			if (res > INT_MAX)
				return (-1);
		}
/*fcntn returns '-1' if the conversion was not successful*/
		else
			return (-1);
	}
	return (res);
}



/**
 * numConverter - converts the numbr into a string rep in specified base
 * @numbr: number
 * @base: base
 * @flags: set of flags
 * Return: string representation
 */
char *numConverter(long int numbr, int base, int flags)
{
/*Declaration of variables*/
	static char *ptr_arr;
	static char buffer[50];
	char sym = 0;
	char *ptrs;
	unsigned long i = numbr;
/*checking whether 'CONVERT_UNSIGNED'flag is set in flags*/
/*and whether numbr is negative*/
	if (!(flags & CONVERT_UNSIGNED) && numbr < 0)
	{
		i = -numbr;
		sym = '-';

	}
/*setting 'ptr_arr' depending on the whether 'CONVERT_LOWERCASE' flag is set*/
	ptr_arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';

/*do while loop to divide i by base*/
	do	{
		*--ptrs = ptr_arr[i % base];
		i /= base;
	} while (i != 0);
/*fnctn to check if 'sym' is '0' or not*/
	if (sym)
		*--ptrs = sym;
	return (ptrs);
}

/**
 * delComments - takes ptr to string & replaces # with null terminator
 * @buf_ptr: pointer
 * Return: 0 (Success)
 */
void delComments(char *buf_ptr)
{
/*Declaration of variables*/
	int numbr;
/*for loop to iterate over chars in string 'buf_ptr' until ('\0')*/
	for (numbr = 0; buf_ptr[numbr] != '\0'; numbr++)
/*if char is '#' and is preceded by ' ' the fnctn replaces '#' with ('\0')*/
		if (buf_ptr[numbr] == '#' && (!numbr || buf_ptr[numbr - 1] == ' '))
		{
			buf_ptr[numbr] = '\0';
			break;
		}
}
