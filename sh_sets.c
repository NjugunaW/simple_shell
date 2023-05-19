#include "chwa.h"

/**
 * shputfd - fnctn that writes a char to a file descriptor
 * @c: character to be printed
 * @fd: file descriptor
 * Return: On success 1, -1 on error and errno is set appropriately
 */
int shputfd(char c, int fd)
{
/*Declaration of variables*/
	static int numbr;
	static char buffer[WRITE_BUF_SIZE];
/*if ststement to check whether 'c' is equal to 'BUF_FLUSH'*/
/*and if numbr is eqaul ro greater than 'WRITE_BUF_SIZE'*/
	if (c == BUF_FLUSH || numbr >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, numbr);
		numbr = 0;
	}
/*if statement to check whether 'c' is not equal to 'BUF_FLUSH'*/
	if (c != BUF_FLUSH)
		buffer[numbr++] = c;
	return (1);
}

/**
 * shputsfd - a fnctn that prints a string to a file descriptor
 * @string: string to be printed
 * @fd: file descriptor
 * Return: the number of characters written in file descriptor
 */
int shputsfd(char *string, int fd)
{
/*Declaration of variables*/
	int numbr = 0;
/*if statement to check whether 'string' is NULL*/
	if (!string)
		return (0);
/*while loop to iterate over all chars in the string '*string'*/
	while (*string)
	{
		numbr += shputfd(*string++, fd);
	}
	return (numbr);
}

/**
 * shputs - fnctn takes a ptr to a string and prints the string to std output
 * @string: string
 */
void shputs(char *string)
{
/*Declaration of variables*/
	int numbr = 0;
/*fnctn to check whether 'string' is NULL*/
	if (!string)
		return;
/*while loop to iterate over the each char in the '*string' until ('\0')*/
	while (string[numbr] != '\0')
	{
		shputchar(string[numbr]);
		numbr++;
	}
}

/**
 *_puts - This function prints an input string
 *@string: The input string
 * Return: Nothing (Function is Void)
 */
void _puts(char *string)
{
	int numbr = 0; /*This is for printing the string char by char*/

	if (!string)
		return;
	while (string[numbr] != '\0')
	{
		_putchar(string[numbr]);
		numbr++;
	}
}
