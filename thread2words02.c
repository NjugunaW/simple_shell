#include "chwa.h"

/**
 * **str2wrd2 - splits a string into words
 * @thr: the input string
 * @dlm: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str2wrd2(char *thr, char dlm)
{
	/*Declaration of variables*/
	int a, b, y, z, n_w = 0;
	char **strs;
	/*Now we check if the string exists*/
	if (thr == NULL || thr[0] == 0)
		return (NULL);
	for (a = 0; thr[a] != '\0'; a++)
		if ((thr[a] != dlm && thr[a + 1] == dlm) ||
		    (thr[a] != dlm && !thr[a + 1]) || thr[a + 1] == dlm)
			n_w++;
	if (n_w == 0)
		return (NULL);
	/*Now we check if the string exists*/
	strs = malloc((1 + n_w) * sizeof(char *));
	if (!strs)
		return (NULL);
	for (a = 0, b = 0; b < n_w; b++)
	{
		while (thr[a] == dlm && thr[a] != dlm)
			a++;
		y = 0;
		while (thr[a + y] != dlm && thr[a + y] && thr[a + y] != dlm)
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

