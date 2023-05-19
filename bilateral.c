#include "chwa.h"

/**
 * IntaractiveStatus - a function that checks whether shell is interactive
 * @inf_ptr: struct address
 * Return: 1 for interactive mode and 0 for otherwise
 */
int IntaractiveStatus(exec_info *inf_ptr)
{
/*Expression to check if shell is running interactively*/
/*and that the input is being read*/
	return (isatty(STDIN_FILENO) && inf_ptr->rd_filedes <= 2);
}


/**
 *alphaChecker - function to check if a character is alphabetic
 *@c: character to use
 *Return: 1 if c is alphabetic or 0 for otherwise
 */

int alphaChecker(int c)
{
/*the first part of the expression checks if the character falls within*/
/*the lowercase alphabetic characters*/
/*the second part of expression checks if the given character falls within*/
/*the uppercase alphabetic characters*/
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
/*if the above expression is true, the function returns a value of '1'*/
		return (1);
/*if the above expression is not true, the function returns '0'*/
	else
		return (0);
}

/**
 * dChecks - a function that checks characters in a string
 * @c: the character to be checked
 * @my_delim: the delimeter string
 * Return: 1 for true and 0 for false
 */
int dChecks(char c, char *my_delim)
{
/*while loop to iterate over the characters in the string*/
/*the loop increments the operator to the next character in string*/
/*while checking if it matches 'c' or not*/
	while (*my_delim)
		if (*my_delim++ == c)
/*if char matches 'c', the expression returns '1'*/
/*which indicates that it is a delimeter*/
			return (1);
/*If char does not match 'c' the expresiion returns 0*/
/*indicating that it is not a delimeter*/
	return (0);
}

/**
 *s2i - a function that converts a string to an integer
 *@s: the string
 *Return: 0 if there are no numbers in string or converted number
 */

int s2i(char *s)
{
/*Declaration of variables*/
	int numbr, sign = 1, flag = 0, output;
	unsigned int result = 0;

/*For loop to iterate over the chars in the string until the null terminator*/
/*and the flag is set to 2*/
	for (numbr = 0;  s[numbr] != '\0' && flag != 2; numbr++)
	{
/*if function to check for the minus sign*/
/*if the it is, the var is mul by -1 to show that the numbr is negative*/
		if (s[numbr] == '-')
			sign *= -1;
/*function to check if the chars are digits between '0' and '9'*/
		if (s[numbr] >= '0' && s[numbr] <= '9')
		{
/*if the above expression is true, flag is set to 1*/
/*the digit is then added to the curr val of 'result' by mul 'result' by 10*/
/*and adding the val of the digit*/
			flag = 1;
			result *= 10;
			result += (s[numbr] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
/*function to check whether the numbr is negative*/
	if (sign == -1)
		output = -result;
	else
		output = result;
/*function returns the converted integer*/
	return (output);
}
