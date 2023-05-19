#include "chwa.h"

/**
 * isExec - function that determines if a file is executable or not
 * @inf_ptr: pointer to a struct
 * @path: file path
 * Return: 1 if true or 0 for Otherwise
 */
int isExec(exec_info *inf_ptr, char *path)
{
/*Declaration of variables*/
	struct stat file_path;
/*line to make compiler ignore the fact that 'inf_ptr' argument is unused*/
	(void)inf_ptr;
/*fnctn to check whether 'path' is  NULL/if 'stat' system call is successful*/
	if (!path || stat(path, &file_path))
		return (0);
/*fnctn to check 'st_mode' field of 'file_path' to det if file @'path' is reg*/
	if (file_path.st_mode & S_IFREG)
	{
		return (1); /*shows file is reg and can be executed*/
	}
	return (0); /*indicates file is not executable*/
}

/**
 * charDuplicate - duplicates characters
 * @path_S: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *charDuplicate(char *path_S, int start, int stop)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (path_S[a] != ':')
			buffer[b++] = path_S[a];
	buffer[b] = 0;
	return (buffer);
}

/**
 * pathLoc - function that searches the full path of a cmd in list
 * @inf_ptr: pointer to a struct
 * @path_S: string containing list of directories
 * @sh_cmd: string containing name of command to be found
 * Return: full path of cmd if found or NULL
 */
char *pathLoc(exec_info *inf_ptr, char *path_S, char *sh_cmd)
{
/*Declaration of variables*/
	int numbr = 0, position = 0;
	char *fullPath;
/*fnctn to check whether 'path_S' is NULL*/
	if (!path_S)
		return (NULL);
/*fnctn checks whether the sh_cmd is a relative path and if it is executable*/
	if ((str_length(sh_cmd) > 2) && str_starts_with(sh_cmd, "./"))
	{
		if (isExec(inf_ptr, sh_cmd))
			return (sh_cmd);
	}
/*while loop to search for the command in each directory*/
	while (1)
	{
		if (!path_S[numbr] || path_S[numbr] == ':')
		{
/*a new string is created by dup a section of the path to curr pos*/
			fullPath = charDuplicate(path_S, position, numbr);
			if (!*fullPath)
/*command name is concatenated to full path*/
				str_concat(fullPath, sh_cmd);
			else
			{
				str_concat(fullPath, "/");
				str_concat(fullPath, sh_cmd);
			}
/*fnctn checks if 'fullPath' is executable*/
			if (isExec(inf_ptr, fullPath))
				return (fullPath);
/*fnctn checks whether curr char is at end of string and if so*/
/*the loop breaks, otherwise pos for next dup is set to curr pos*/
			if (!path_S[numbr])
				break;
			position = numbr;
		}
		numbr++;
	}
	return (NULL);
}
