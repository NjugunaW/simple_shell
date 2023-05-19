#include "chwa.h"

/**
 * shExit - a function to exit the shell program
 * @inf_ptr: Struct that has arguments
 *  Return: exits with a given exit exec_status
 *         (0) if inf_ptr.argv[0] != "exit"
 */
int shExit(exec_info *inf_ptr)
{
	int exitChecker;
/*If function that checks whether 'inf_ptr->argv[1]' exists or not*/
	if (inf_ptr->argv[1])
	{
		exitChecker = err2int(inf_ptr->argv[1]);
/*If function to check whether the argi=ument passed is a valid integer*/
		if (exitChecker == -1)
		{
			inf_ptr->exec_status = 2;
			errPrt(inf_ptr, "Illegal number: ");
			shputs(inf_ptr->argv[1]);
			shputchar('\n');
			return (1);
		}
/*if the argument passed is a valid integer the val oof struct is set*/
		inf_ptr->error_numb = err2int(inf_ptr->argv[1]);
		return (-2);
	}
/*if the exit command is called without any argument, shell shld auto exit*/
	inf_ptr->error_numb = -1;
	return (-2);
}

/**
 * shcd - function that changes the current working directory
 * @inf_ptr: Struct that has arguments
 * Return: 0 (Success)
 */
int shcd(exec_info *inf_ptr)
{
	char *strr, *directory, buffer[1024];
	int cd_return;
/*Function that calls the 'getcwd' sys call to get the cwd as string*/
	strr = getcwd(buffer, 1024);
	if (!strr)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf_ptr->argv[1])
	{
		directory = shgetenv(inf_ptr, "HOME=");
		if (!directory)
			cd_return = /* TODO: what should this be? */
				chdir((directory = shgetenv(inf_ptr, "PWD=")) ? directory : "/");
		else
			cd_return = chdir(directory);
	}
	else if (str_compare(inf_ptr->argv[1], "-") == 0)
	{
		if (!shgetenv(inf_ptr, "OLDPWD="))
		{
			_puts(strr);
			_putchar('\n');
			return (1);
		}
		_puts(shgetenv(inf_ptr, "OLDPWD=")), _putchar('\n');
		cd_return = /* TODO: what should this be? */
			chdir((directory = shgetenv(inf_ptr, "OLDPWD=")) ? directory : "/");
	}
	else
		cd_return = chdir(inf_ptr->argv[1]);
	if (cd_return == -1)
	{
		errPrt(inf_ptr, "can't cd to ");
		shputs(inf_ptr->argv[1]), shputchar('\n');
	}
	else
	{
		sEnviron(inf_ptr, "OLDPWD", shgetenv(inf_ptr, "PWD="));
		sEnviron(inf_ptr, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shhelp - a function that provides help information to a user
 * @inf_ptr: Struct that has arguments
 *  Return: 0 (Success)
 */
int shhelp(exec_info *inf_ptr)
{
	char **arguments;
/*function to take in arguments for providing help info*/
	arguments = inf_ptr->argv;
	_puts("help call works. Function not yet implemented \n");
/*if statement for a compiler warning or error*/
	if (0)
		_puts(*arguments); /* temp att_unused workaround */
	return (0);
}
