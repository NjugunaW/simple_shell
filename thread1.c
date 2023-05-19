#include "chwa.h"


/**
 * duplicate_str - This function duplicates a string
 * @my_str: The string
 * Return: The duplicated string
 */
char *duplicate_str(const char *my_str)
{
	int length = 0; /*The length of the string */
	char *result; /*The duplicated string*/

	if (my_str == NULL)
		return (NULL);
	while (*my_str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--my_str;
	return (result);
}

/**
 * copy_string - This function copies a string
 * @dest: The string destination
 * @src: The string source
 * Return: Returns a pointer to the destination
 */
char *copy_string(char *dest, char *src)
{
	int numbr = 0; /*This will be used to copy the string char by char */

	if (dest == src || src == 0)
		return (dest);
	while (src[numbr])
	{
		dest[numbr] = src[numbr];
		numbr++;
	}
	dest[numbr] = 0; /*This returns the pointer to the first char*/
	return (dest);
}



