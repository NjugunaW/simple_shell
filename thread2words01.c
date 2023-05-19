#include "chwa.h"

/**
 * **str2wrd - splits a string into words. Repeat delimiters are ignored
 * @thr: the input string
 * @dlm: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str2wrd(char *thr, char *dlm)
{
	/*Declaration of variables*/
	int a, b, y, z, n_w = 0;
	char **strs;
	/*Now we check if the string exists*/
	if (thr == NULL || thr[0] == 0)
		return (NULL);
	if (!dlm)
		dlm = " ";
	for (a = 0; thr[a] != '\0'; a++)
		if (!dChecks(thr[a], dlm) && (dChecks(thr[a + 1], dlm) || !thr[a + 1]))
			n_w++;

	if (n_w == 0)
		return (NULL);
	/*We are allocating memory for the pointer*/
	strs = malloc((1 + n_w) * sizeof(char *));
	if (!strs)
		return (NULL);
	for (a = 0, b = 0; b < n_w; b++)
	{
		while (dChecks(thr[a], dlm))
			a++;
		y = 0;
		while (!dChecks(thr[a + y], dlm) && thr[a + y])
			y++;
		strs[b] = malloc((y + 1) * sizeof(char));
		if (!strs[b])
		{
			for (y = 0; y < b; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			strs[b][z] = thr[a++];
		strs[b][z] = 0;
	}
	strs[b] = NULL;
	return (strs);
}
