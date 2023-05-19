#include "chwa.h"

/**
 * gEnviron - fnctn to return a string array that is a copy of curr environ
 * @inf_ptr: pointer to a structure
 * Return:0 (Success)
 */
char **gEnviron(exec_info *inf_ptr)
{
/*if statement to check whether the 'environ' memeber of struct is NULL*/
/*or if chnge_envir memeber is true*/
	if (!inf_ptr->environ || inf_ptr->chnge_envir)
	{
		inf_ptr->environ = list2string(inf_ptr->env);
		inf_ptr->chnge_envir = 0;
	}
/*fnctn returns pointer to string array stored in 'environ'*/
	return (inf_ptr->environ);
}


/**
 * sEnviron - fnctn to set or modify an environment variable
 * @inf_ptr: pointer to a struct
 * @st: string
 * @st_2: string
 *  Return: 0 (Success)
 */
int sEnviron(exec_info *inf_ptr, char *st, char *st_2)
{
/*Declaration of variables*/
	char *buffer = NULL;
	pass_list *n;
	char *ptrs;
/*fnctn to check if 'st' and 'st_2' are pointers to  NULL*/
	if (!st || !st_2)
		return (0);
/*memory allocation or buffer, ('\0) and '=' in heap using malloc*/
	buffer = malloc(str_length(st) + str_length(st_2) + 2);
/*fnctn to check whether malloc was successful*/
/*if malloc was successful, copy_string is called and then fnctn concats*/
	if (!buffer)
		return (1);
	copy_string(buffer, st);
	str_concat(buffer, "=");
	str_concat(buffer, st_2);
	n = inf_ptr->env;
/*loops thru list looking for any existing vars thats match 'st' string*/
	while (n)
	{
		ptrs = str_starts_with(n->string, st);
		if (ptrs && *ptrs == '=')
		{
			free(n->string);
			n->string = buffer;
			inf_ptr->chnge_envir = 1;
			return (0);
		}
		n = n->next;
	}
/*fnctn adds 'buffer' string to end of the '*inf_ptr->env'*/
	nodeAppend(&(inf_ptr->env), buffer, 0);
	free(buffer);
	inf_ptr->chnge_envir = 1;
	return (0);
}


/**
 * uSetEnv - fnctn to remove envrion vars fromaa list and keep track of changes
 * @inf_ptr: pointer to a struct
 * @st: ponter to a string
 * Return: 1 on delete or 0 for otherwise
 */
int uSetEnv(exec_info *inf_ptr, char *st)
{
/*Declaration of variables*/
	pass_list *n = inf_ptr->env;
	size_t s = 0;
	char *ptrs;
/*fnctn to check whether 'n' and 'st' are NULL pointers*/
	if (!n || !st)
		return (0);
/*while loop that continues so long as 'n' is not NULL*/
	while (n)
	{
		ptrs = str_starts_with(n->string, st);
/*fnctn checks whther 'ptrs' is not NULL and char following 'st' is '='*/
		if (ptrs && *ptrs == '=')
		{
/*fnctn to delete the node at index 's' from '*inf_ptr->env'*/
			inf_ptr->chnge_envir = delNode(&(inf_ptr->env), s);
			s = 0;
			n = inf_ptr->env;
			continue;
		}
		n = n->next;
		s++;
	}
	return (inf_ptr->chnge_envir);
}
