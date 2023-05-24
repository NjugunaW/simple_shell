#include "chwa.h"



/**
 * ali2str - a function that sets a substitute name to a string
 * @inf_ptr: struct
 * @string: the string
 * Return: 0 (Success) and 1 on error
 */
int ali2str(exec_info *inf_ptr, char *string)
{
/*Declararion of Variables*/
	char *ptrs, l;
	int retn;

/*function to find the location of '=' in the string and assign address*/
	ptrs = chrLoc(string, '=');
	if (!ptrs)
		return (1);
/*function to save the char at the '=' location in 'l' variable*/
	l = *ptrs;
	*ptrs = 0;
/*system calls 'inf_ptr->alias' and prefixSearch are used*/
/*'getIndex' takes the result of above sys calls and passes it to delNode*/
	retn = delNode(&(inf_ptr->alias),
		getIndex(inf_ptr->alias, prefixSearch(inf_ptr->alias, string, -1)));
	*ptrs = l;
	return (retn);
}


/**
 * aliasPtr - a function that prints a string rep of an alias node
 * @ali_node: the alias node
 * Return: 0(Success) or 1 on error
 */
int aliasPtr(pass_list *ali_node)
{
/*Declaration of variables which are initialized to NULL*/
	char *ptrs = NULL, *a = NULL;
/*Function to check if 'pass_list' is NULL*/
/*then uses 'chrLoc' to find the location of '=' in pass_list and 'string'*/
	if (ali_node)
	{
		ptrs = chrLoc(ali_node->string, '=');
		for (a = ali_node->string; a <= ptrs; a++)
/*fnctn prints all chars preceding '=' in the string*/
			_putchar(*a);
		_putchar('\'');
		_puts(ptrs + 1);
		_puts("'\n");
/*fnctn returns '0' if 'pass_list' ptr is not NULL and '1' if it is*/
		return (0);
	}
	return (1);
}

/**
 * setAlias - a function that sets an alias to a string
 * @inf_ptr: struct
 * @string: string
 * Return: 0 (Success) and 1 on error
 */
int setAlias(exec_info *inf_ptr, char *string)
{
/*Declaration of variables*/
	char *ptrs;

/*function to find the location of '=' in the string and assign address*/
	ptrs = chrLoc(string, '=');
	if (!ptrs)
		return (1);
/*Function increments 'ptrs' to next char and check whether it is NULL*/
	if (!*++ptrs)
		return (ali2str(inf_ptr, string));
/*'ali2str' function del exisitng alias with same name from 'inf_ptr->alias'*/
/*fnctn then appends 'string' to the end of 'inf_ptr->alias'*/
	ali2str(inf_ptr, string);
	return (nodeAppend(&(inf_ptr->alias), string, 0) == NULL);
}



/**
 * shalias - a function that mimiic 'alias' in Unix-based shell environments
 * @inf_ptr: Struct
 *  Return: 0 (Success)
 */
int shalias(exec_info *inf_ptr)
{
/*Declaration of variables*/
	int numbr = 0;
	char *ptrs = NULL;
	pass_list *ali_node = NULL;
/*if fnctn to check whether arguments in 'shalias' are equal to '1'*/
	if (inf_ptr->arg_count == 1)
	{
		ali_node = inf_ptr->alias;
/*while loop to iterate over the liked list until 'n' is NULL*/
		while (ali_node)
		{
			aliasPtr(ali_node);
			ali_node = ali_node->next;
		}
		return (0);
	}
/*for loop to process each argument passed*/
	for (numbr = 1; inf_ptr->argv[numbr]; numbr++)
	{
		ptrs = chrLoc(inf_ptr->argv[numbr], '=');
		if (ptrs)
			setAlias(inf_ptr, inf_ptr->argv[numbr]);
		else
			aliasPtr(prefixSearch(inf_ptr->alias, inf_ptr->argv[numbr], '='));
	}

	return (0);
}

/**
 * shhistory - fnctn that displays the history of previously executed command
 * @inf_ptr: Struct that has arguments
 *  Return: 0 (Success)
 */
int shhistory(exec_info *inf_ptr)
{
/*calling the 'lstPrt' function with the 'inf_ptr->history' argument*/
	lstPrt(inf_ptr->history);
	return (0);
}
