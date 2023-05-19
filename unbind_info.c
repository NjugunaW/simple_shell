#include "chwa.h"


/**
 * finf - fnctn that frees members in a sturc based on parameters set
 * @inf_ptr: pointer to a struct
 * @my_bool: true or false parameter
 */
void finf(exec_info *inf_ptr, int my_bool)
{
/*fnctn to free mem allocate for 'argv' in the struct*/
	ffree(inf_ptr->argv);
	inf_ptr->argv = NULL;
	inf_ptr->path = NULL;
/*fnctn executes if 'my_bool' parameter is true*/
	if (my_bool)
	{
		if (!inf_ptr->cmand_buff)
			free(inf_ptr->arg);
/*'listFree' frees 'env', 'history' and 'alias' if they are not NULL*/
		if (inf_ptr->env)
			listFree(&(inf_ptr->env));
		if (inf_ptr->history)
			listFree(&(inf_ptr->history));
		if (inf_ptr->alias)
			listFree(&(inf_ptr->alias));
/*'ffree' frees the mem allocated for 'environ' in struct and sets to NULL*/
		ffree(inf_ptr->environ);
			inf_ptr->environ = NULL;
/*'cmand_buff' is freed using 'ptrFree'*/
		ptrFree((void **)inf_ptr->cmand_buff);
		if (inf_ptr->rd_filedes > 2)
			close(inf_ptr->rd_filedes);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clinf -  fnctn that initializess members of a pointer to a struct
 * @inf_ptr: pointer to a struct
 */
void clinf(exec_info *inf_ptr)
{
/*fnctn sets struct members to NULL and '0' to avoid bugs or errors*/
	inf_ptr->arg = NULL;
	inf_ptr->argv = NULL;
	inf_ptr->path = NULL;
	inf_ptr->arg_count = 0;
}

/**
 * setinf - fnctn that initializes members of a struct based on args provided
 * @inf_ptr: pointer to a struct
 * @av: argument
 */
void setinf(exec_info *inf_ptr, char **av)
{
/*Declaration of variables*/
	int numbr = 0;

	inf_ptr->finame = av[0];
/*fnctn to check if 'arg' member of 'exec_info' is NULL or not*/
	if (inf_ptr->arg)
	{
		inf_ptr->argv = str2wrd(inf_ptr->arg, " \t");
/*fnctn to check if inf_ptr->argv is NULL so as to allocate memory*/
		if (!inf_ptr->argv)
		{

			inf_ptr->argv = malloc(sizeof(char *) * 2);
/*if malloc is successful the fnctn copies 'arg' to 'duplicate_str'*/
			if (inf_ptr->argv)
			{
				inf_ptr->argv[0] = duplicate_str(inf_ptr->arg);
				inf_ptr->argv[1] = NULL;
			}
		}
/*fnctn to loop thru 'inf_ptr->argv' and count numbr of elements in it*/
		for (numbr = 0; inf_ptr->argv && inf_ptr->argv[numbr]; numbr++)
			;
		inf_ptr->arg_count = numbr;
/*fnctns to perform alias and var substitutions on 'argv' array respectively*/
		aliSub(inf_ptr);
		varSub(inf_ptr);
	}
}
