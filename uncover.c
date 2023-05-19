#include "chwa.h"

/**
 * catStr - fnctn that concats two strings
 * @catto: string 1
 * @catfrm: string 2
 * @n: int that specifies the max numbr of bytes to be used
 * Return: the concatenated string
 */
char *catStr(char *catto, char *catfrm, int n)
{
/*Declaration of variables*/
	int a, b;
	char *strn = catto;

	a = 0;
	b = 0;
/*while loop to find the end of the 'dest' by incrmnting 'a' until ('\0')*/
	while (catto[a] != '\0')
		a++;
/*while loop to concat chars from 'src'to end of 'dest' up to 'n' bytes*/
	while (catfrm[b] != '\0' && b < n)
	{
		catto[a] = catfrm[b];
		a++;
		b++;
	}
/*if fnctn to check whether 'b' is greater than 'n'*/
	if (b < n)
		catto[a] = '\0';
	return (strn);
}


/**
 * cpystr - a fnctn that copies a string from src string to dest string
 * @catto: pointer destination string where coped chars will be stored
 * @catfrm: pointer to the source string from where the chars will be copied
 * @n: int that specifies the max numbr of chars
 * Return: dest
 */
char *cpystr(char *catto, char *catfrm, int n)
{
/*Declaration of variables*/
	int a, b;
	char *strn = catto;
/*while loop copy chars from 'src' to 'dest' until '\0' or n chars are copied*/
	a = 0;
	while (catfrm[a] != '\0' && a < n - 1)
	{
		catto[a] = catfrm[a];
		a++;
	}
/*loop to check whether 'a' is less than numbr of copied chars*/
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			catto[b] = '\0';
			b++;
		}
	}
/*fnctn returns '*strn' which points to 'dest'*/
	return (strn);
}

/**
 * chrLoc - a function that locates the occurrence of a char in a given string
 * @strn: pointer to a string
 * @c: the character to be located
 * Return: pointer to the location in mem where char is found
 */
char *chrLoc(char *strn, char c)
{
/*do-while loop to iterate over the string until ('\0') or 'c' is located*/
	do {
		if (*strn == c)
			return (strn);
	} while (*strn++ != '\0');
/*if 'c' char was not located, the fnctn returns NULL*/
	return (NULL);
}
