#include "chwa.h"


/**
 * ffree - Releases a string
 * @str_ptr: The string
 * return: Nothing (Function is void)
 */
void ffree(char **str_ptr)
{
	char **pptrs = str_ptr;

/*We use this pointer to a pointer and assign it*/
/*to **str_ptr so as to free the string */

	if (!str_ptr)
		return;
	while (*str_ptr)
		free(*str_ptr++);
	free(pptrs);
}

/**
 **_memset - Fills the memory spaces
 *with a certain digit
 *@m: This points to the memory area
 *@b: This is the byte to fill the pointer with
 *@n: The number of bytes
 *Return: m
 */
char *_memset(char *m, char b, unsigned int n)
{
	unsigned int numbr;
/* We use the numbr variable to fill the memory spaces one byte at a time */

	for (numbr = 0; numbr < n; numbr++)
		m[numbr] = b;
	return (m);
}

/**
 * _realloc - This function reapportions a block of memory.
 * @m_ptr: This points to a block of memory that was previously mannually
 * allocated
 * @obs: Size of the previous block in bytes
 * @nbs: Size of the new block in bytes
 * Return: A pointer to the old block
 */
void *_realloc(void *m_ptr, unsigned int obs, unsigned int nbs)
{
	char *ptrs;

	/*These checks for the existance of a value in the pointer *ptrs and*/
	/*The new size*/
	/*The conditions are expected to be true*/
	if (!m_ptr)
		return (malloc(nbs));
	if (!nbs)
		return (free(m_ptr), NULL);
	if (nbs == obs)
		return (m_ptr);

	ptrs = malloc(nbs); /*This is where we assign the new size*/
	if (!ptrs)
		return (NULL);

	obs = obs < nbs ? obs : nbs;
	while (obs--)
		ptrs[obs] = ((char *)m_ptr)[obs];
	free(m_ptr);
	return (ptrs);
}
