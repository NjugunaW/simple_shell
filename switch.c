#include "chwa.h"

/**
 * aliSub - function that substitutes an alias on the cmd line arguement
 * @inf_ptr:pointer to struct
 * Return: 1 if substituted or 0 for otherwise
 */
int aliSub(exec_info *inf_ptr)
{
/*Declaratio of variables*/
	int numbr;
	pass_list *n;
	char *ptrs;
/*for loop which iterates upto 10 times looking for alias associated*/
/*with 'inf_ptr->argv'*/
	for (numbr = 0; numbr < 10; numbr++)
	{
		n = prefixSearch(inf_ptr->alias, inf_ptr->argv[0], '=');
		if (!n) /*checks if search fails hence no subs performed*/
			return (0);
/*mem allocated is freed if search was successful*/
		free(inf_ptr->argv[0]);
		ptrs = chrLoc(n->string, '=');/*sets 'ptrs'to substring of alias*/
		if (!ptrs)/*checks whether '=' char is in substring*/
			return (0);
/*'duplicate_str' is used to set 'ptrs'to a copy of substring*/
		ptrs = duplicate_str(ptrs + 1);
		if (!ptrs) /*checks if malloc was succesful*/
			return (0);
		inf_ptr->argv[0] = ptrs;/*subing original cmd with new sub alias*/
	}
	return (1);
}

/**
 * varSub - fnctn that performs var substitution on cmd lie argument
 * @inf_ptr:pointer to a sturct
 * Return: 1 if substituted and 0 for otherwise
 */
int varSub(exec_info *inf_ptr)
{
/*Declaration of variables*/
	int numbr = 0;
	pass_list *n;
/*for loop to iterate overall command line arguments*/
	for (numbr = 0; inf_ptr->argv[numbr]; numbr++)
	{
/*loop continues to next argument if first char in argument is not $ or*/
/*if argument only has one char*/
		if (inf_ptr->argv[numbr][0] != '$' || !inf_ptr->argv[numbr][1])
			continue;
/*if curr argm is '"$"', it is subbed with exit exec_status of prev command*/
		if (!str_compare(inf_ptr->argv[numbr], "$?"))
		{
			stringSub(&(inf_ptr->argv[numbr]),
				duplicate_str(numConverter(inf_ptr->exec_status, 10, 0)));
			continue;
		}
/*if curr argm is '"$0"', it is subbed with the process ID of shell*/
		if (!str_compare(inf_ptr->argv[numbr], "$$"))
		{
			stringSub(&(inf_ptr->argv[numbr]),
				duplicate_str(numConverter(getpid(), 10, 0)));
			continue;
		}
		n = prefixSearch(inf_ptr->env, &inf_ptr->argv[numbr][1], '=');
/*if curr arg starts with '$' and next str matches an anviron var*/
/*it is subbed with the val of envrion var*/
		if (n)
		{
			stringSub(&(inf_ptr->argv[numbr]),
				duplicate_str(chrLoc(n->string, '=') + 1));
			continue;
		}
/*arg is subbed with empty str if above is false*/
		stringSub(&inf_ptr->argv[numbr], duplicate_str(""));

	}
	return (0);
}

/**
 * stringSub - function that replaces a string with a new one
 * @old_S: pointer to address of old string
 * @new_s: a new string that eill repace the old one
 * Return: 1 if substotuted or 0 for otherwise
 */
int stringSub(char **old_S, char *new_s)
{
/*fnctn fress mem allocated to old_S string and assigns the new string*/
/*to the '*old'*/
	free(*old_S);
	*old_S = new_s;
	return (1);
}
