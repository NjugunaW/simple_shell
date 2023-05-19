#include "chwa.h"

/**
 * ptrFree - fnctn that takes a double pointer as input and returns integer
 * @pptr: double pointer
 * Return: 1 if memory is frees or 0 for otherwise
 */
int ptrFree(void **pptr)
{
/*fcntn checks if 'pptr' and '*pptr' are NULL*/
	if (pptr && *pptr)
	{
		free(*pptr); /*frees mem pointed to by '*pptr'*/
		*pptr = NULL; /*setting val pointed to by 'pptr' as NULL*/
		return (1); /*if mem was successfully freed*/
	}
	return (0); /*shows no memory was freed*/
}
