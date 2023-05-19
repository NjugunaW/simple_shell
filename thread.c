#include "chwa.h"


/**
 * str_compare - This function compares two strings.
 * @my_str1: the first string
 * @my_str2: the second string
 *
 * Return: Negative if string 1 is lesser than string 2
 * Positive if string 1 is greater than string 2
 * Zero if both strings are the same
 */
int str_compare(char *my_str1, char *my_str2)
{
	while (*my_str1 && *my_str2) /*This makes sure the function will run with both
						*strings
						*/
	{
		if (*my_str1 != *my_str2)
			return (*my_str1 - *my_str2);
		my_str1++;
		my_str2++;
	}
	if (*my_str1 == *my_str2)
		return (0);
	else
		return (*my_str1 < *my_str2 ? -1 : 1);
}

/**
 * str_length - This function finds the length of a string
 * @my_str: The string to check
 * Return: The length of the string in integers
 */
int str_length(char *my_str)
{
	int j = 0; /*J will be the incremental length value starting from 0*/

	if (!my_str)
		return (0);

	while (*my_str++)
		j++;
	return (j);
}

/**
 * str_starts_with - This function checks if a string starts with a substring
 * @my_str: The string
 * @my_substr: The substring
 * Return: The address of next char of the string or NULL
 */
char *str_starts_with(const char *my_str, const char *my_substr)
{
	while (*my_substr)
		if (*my_substr++ != *my_str++)
			return (NULL);
	return ((char *)my_str);
}

/**
 * str_concat - This function concatenates two strings
 * @cpyto: The string to be concatenated
 * @cpyfrm: The additional string(s)
 *
 * Return: pointer to destination buffer
 */
char *str_concat(char *cpyto, char *cpyfrm)
{
	char *result = cpyto;

	while (*cpyto)
		cpyto++;
	while (*cpyfrm)
		*cpyto++ = *cpyfrm++;
	*cpyto = *cpyfrm;
	return (result);
}
