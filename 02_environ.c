#include "chwa.h"


/**
 * fill_env_list - a function that fills a linked list with the environ vars
 * @inf_ptr: a pointer to a structure
 * Return: 0 (Success)
 */
int fill_env_list(exec_info *inf_ptr)
{
/*Declaration of variables*/
	pass_list *n = NULL;
	size_t i;
/*loop to iterate over the 'environ' array*/
	for (i = 0; environ[i]; i++)
/*appending of new node to the linked list after each iteration of the loop*/
		nodeAppend(&n, environ[i], 0);
	inf_ptr->env = n;
	return (0);
}


/**
 * shenv - fnctn that takes a ptr to a struct as an arg and returns an int val
 * @inf_ptr: pointer to a sturct
 * Return: 0 (Success)
 */
int shenv(exec_info *inf_ptr)
{
/*function to rint cntents of a string*/
	strListPrt(inf_ptr->env);
	return (0);
}


/**
 * shsetenv - fnctn that initializes a new env var or modifies an exisitng one
 * @inf_ptr: pointer to a structure
 * Return: 0 (Success)
 */
int shsetenv(exec_info *inf_ptr)
{
/*if fnctn that checks whether the numbr of args passed i equal to '3'*/
	if (inf_ptr->arg_count != 3)
	{
		shputs("Incorrect number of arguements\n");
		return (1);
	}
/*if fnctn to set the value of the envrinment variable*/
	if (sEnviron(inf_ptr, inf_ptr->argv[1], inf_ptr->argv[2]))
		return (0);
	return (1);
}


/**
 * shgetenv - fnctn that retrieves the val of th environment  var
 * @inf_ptr: pointer to a structure
 * @name_ptr: pointer to a constant character
 * Return: ptr to char string with the value env var
 */
char *shgetenv(exec_info *inf_ptr, const char *name_ptr)
{
/*Declaration of variables*/
	pass_list *n = inf_ptr->env;
	char *ptrs;
/*while loop that iterates over the linked list */
	while (n)
	{
		ptrs = str_starts_with(n->string, name_ptr);
/*if fnctn to check whether 'ptrs' and '*ptrs' are NULL*/
		if (ptrs && *ptrs)
			return (ptrs);
		n = n->next;
	}
	return (NULL);
}

/**
 * shunsetenv - fcnt that removes an environ var from current environ
 * @inf_ptr: pointer to a structure
 *  Return: 0 (Success)
 */
int shunsetenv(exec_info *inf_ptr)
{
/*Declaration of variables*/
	int numbr;
/*if fncnt to check whether argcument count is equal to '1'*/
	if (inf_ptr->arg_count == 1)
	{
		shputs("Too few arguements.\n");
		return (1);
	}
/*for loop to remove each environ var listed as an argument to the function*/
	for (numbr = 1; numbr <= inf_ptr->arg_count; numbr++)
		uSetEnv(inf_ptr, inf_ptr->argv[numbr]);

	return (0);
}
