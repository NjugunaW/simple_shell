#include "chwa.h"

/**
 * exec_builtin - function to execute a built-in command in shell
 * @inf_pt: pointer to a struct
 * Return: -1 if built_in not found,0 if built_in executed successfully,
 *         1 if built_in found isn't successful,-2 if built_in signals exit()
 */
int exec_builtin(exec_info *inf_pt)
{
/*Declaration of variables*/
	int j, result = -1;
/*array of 'built_in table' structs is defined*/
/*each struct has a 'ty_pes' and a 'fnctn'*/
	built_in_table builtintbl[] = {
		{"exit", shExit},
		{"env", shenv},
		{"help", shhelp},
		{"history", shhistory},
		{"setenv", shsetenv},
		{"unsetenv", shunsetenv},
		{"cd", shcd},
		{"alias", shalias},
		{NULL, NULL}
	};
/*for loop to iterate over 'builtintbl'*/
	for (j = 0; builtintbl[j].ty_pes; j++)
/*statement to check each command entered by the user*/
		if (str_compare(inf_pt->argv[0], builtintbl[j].ty_pes) == 0)
		{
			inf_pt->cnt_line++;
			result = builtintbl[j].fnctn(inf_pt);
			break;
		}
	return (result);
}


/**
 * _spawncmd - fnctn that forks new process and executes cmd in child process
 * @inf_pt: pointer to a struct
 */
void _spawncmd(exec_info *inf_pt)
{
	pid_t inf_pid;
/*'fork' sys call where parent process receives the PID of child process*/
	inf_pid = fork();
/*if 'fork' fails, the fnctn should print error message*/
	if (inf_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (inf_pid == 0) /*shows curr process is child process*/
	{
/*if 'execve' fails, the fnctn should print the error message and exit*/
		if (execve(inf_pt->path, inf_pt->argv, gEnviron(inf_pt)) == -1)
		{
			finf(inf_pt, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
/*else if 'fork' returns a positive val, then curr process is parent process*/
/*parent process shld wait for child process to exit*/
	else
	{
		wait(&(inf_pt->exec_status));
		if (WIFEXITED(inf_pt->exec_status))
		{
			inf_pt->exec_status = WEXITSTATUS(inf_pt->exec_status);
			if (inf_pt->exec_status == 126) /*insufficient permissions*/
				errPrt(inf_pt, "Permission denied\n");
		}
	}
}

/**
 * search_cmd - fnctn that searches for cmd entered by user in the directory
 * @inf_pt: pointer to a struct
 */
void search_cmd(exec_info *inf_pt)
{
/*Declaration of variables*/
	char *fi_path = NULL;
	int j, n;

	inf_pt->path = inf_pt->argv[0];
/*if count_flag is set to '1', 'cnt_line' is incremented by '1'*/
/*and 'count_flag is set to '0'*/
	if (inf_pt->count_flag == 1)
	{
		inf_pt->cnt_line++;
		inf_pt->count_flag = 0;
	}
/*for loop to count the numbr of non-delim arg in array*/
	for (j = 0, n = 0; inf_pt->arg[j]; j++)
		if (!dChecks(inf_pt->arg[j], " \t\n"))
			n++;
/*function to check if there are no non-delim args*/
	if (!n)
		return;

	fi_path = pathLoc(inf_pt, shgetenv(inf_pt, "PATH="), inf_pt->argv[0]);
	if (fi_path)/*checks if 'fi_path'is NULL is or not*/
	{
		inf_pt->path = fi_path;
		_spawncmd(inf_pt);
	}
	else
	{
/*if fnctn check whether shell is running in interactive mode*/
		if ((IntaractiveStatus(inf_pt) || shgetenv(inf_pt, "PATH=")
			|| inf_pt->argv[0][0] == '/') && isExec(inf_pt, inf_pt->argv[0]))
			_spawncmd(inf_pt);/*spawn new process to exec cmd*/
		else if (*(inf_pt->arg) != '\n')
		{
			inf_pt->exec_status = 127;
			errPrt(inf_pt, "not found\n");
		}
	}
}


/**
 * shell_loop - provides info about a fnctn, its parameters and return value
 * @inf_pt: pointer to a struct
 * @av: double pointer to an array of strings
 * Return: 0 (Success), 1 on error, or an error code
 */
int shell_loop(exec_info *inf_pt, char **av)
{
/*Declaration of variables*/
	ssize_t len = 0;
	int result = 0;
/*while loop that will run until 'len'is -1 and 'result' is -2*/
	while (len != -1 && result != -2)
	{
/*function to clear some date from the struct*/
		clinf(inf_pt);
/*function to check if shell is running in interactive mode*/
		if (IntaractiveStatus(inf_pt))
			_puts("$ ");
		shputchar(BUF_FLUSH); /*std output buffer*/
/*line of input form user is read and the length of input is returned*/
		len = gInput(inf_pt);
		if (len != -1)
		{
			setinf(inf_pt, av);
/*fncnt to check whether user input is a built-in cmd and executes if it is*/
			result = exec_builtin(inf_pt);
			if (result == -1)
				search_cmd(inf_pt);
		}
		else if (IntaractiveStatus(inf_pt))
			_putchar('\n');
		finf(inf_pt, 0); /*clearing of some data from struct*/
	}
	write2histFile(inf_pt); /*writes the user's command history to a file*/
	finf(inf_pt, 1);
/*statement to check if shell is not running in interactive mode*/
	if (!IntaractiveStatus(inf_pt) && inf_pt->exec_status)
		exit(inf_pt->exec_status);
	if (result == -2)
	{
		if (inf_pt->error_numb == -1)
			exit(inf_pt->exec_status);
		exit(inf_pt->error_numb);
	}
	return (result);
}
