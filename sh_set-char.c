#include "chwa.h"


/**
 * shputchar - a fnctn that writes a char to the std error output
 * @c: character to be printed
 * Return: On success 1, -1 on error and errno is set appropriately
 */
int shputchar(char c)
{
/*Declaration of variables*/
	static int numbr;
	static char buffer[WRITE_BUF_SIZE];
/*if ststement to check whether 'c' is equal to 'BUF_FLUSH'*/
/*and if numbr of chars is greater than or equal to 'WRITE_BUF_SIZE'*/
	if (c == BUF_FLUSH || numbr >= WRITE_BUF_SIZE)
	{
		write(2, buffer, numbr);
		numbr = 0;
	}
/*if statement to check whether 'c' is not equal to 'BUF_FLUSH'*/
	if (c != BUF_FLUSH)
		buffer[numbr++] = c;
	return (1);
}

/**
 * _putchar - This function prints the character presented to the function
 * @c: The character
 * Return: On success 1.
 */
int _putchar(char c)
{
	static int numbr;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || numbr >= WRITE_BUF_SIZE)
	{
		write(1, buffer, numbr);
		numbr = 0;
	}
	if (c != BUF_FLUSH)
		buffer[numbr++] = c;
	return (1);
}
