#include "chwa.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 (Success) or 1 on error
 */
int main(int ac, char **av)
{
/*Declaration of variables*/
	exec_info info[] = { _init_ };
	int filedes = 2;
/*assembly code to add '3' to the value of 'filedes'*/
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filedes)
		: "r" (filedes));
/*checks if the program was called with exactly one aregument*/
	if (ac == 2)
	{
/*if above is true, the fnctn tries to open the argument in read-only mode*/
		filedes = open(av[1], O_RDONLY);
/*if open operation failes, fnctn checks 'errno' value and exits*/
		if (filedes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				shputs(av[0]);
				shputs(": 0: Can't open ");
				shputs(av[1]);
				shputchar('\n');
				shputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
/*if open operation is successful, 'rd_filedes' is set as first element*/
		info->rd_filedes = filedes;
	}
/*initialization of environment variables of shell program*/
	fill_env_list(info);
	readHistFile(info); /* reads shell history file into mem,if it exists*/
	shell_loop(info, av); /*main loop of shell program*/
	return (EXIT_SUCCESS);
}
