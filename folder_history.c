#include "chwa.h"


/**
 * write2histFile - fnct that writes a list of string to a file then newline
 * @inf_ptr: pointer to struct
 * Return: 1 on success or -1 for otherwise
 */
int write2histFile(exec_info *inf_ptr)
{
	ssize_t filedes;
	char *fi_name = getHistFile(inf_ptr);
	pass_list *n = NULL;
/*functn to check whether 'fi_name' is NULL and if so, to return '-1'*/
	if (!fi_name)
		return (-1);
/*open sys call and assigns the results to 'filedes'*/
	filedes = open(fi_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
/*memory assigned to 'fi_name' is de-allocated*/
	free(fi_name);
	if (filedes == -1)
		return (-1);
/*loop to iterate over the linked list 'ínfo->history' writng each string*/
	for (n = inf_ptr->history; n; n = n->next)
	{
		shputsfd(n->string, filedes);
		shputfd('\n', filedes);
	}
	shputfd(BUF_FLUSH, filedes);
	close(filedes);
	return (1);
}

/**
 * refreshHistList - fnctn that updates the numbering of hisory list
 * @inf_ptr: pointer to a struct
 * Return: updated numbering of history
 */

int refreshHistList(exec_info *inf_ptr)
{
/*Declaratio of variables*/
	pass_list *n = inf_ptr->history;
	int numbr = 0;
/*while loop to iterate over the history list so long as 'n' is not NULL*/
	while (n)
	{
		n->numbr = numbr++;
		n = n->next;
	}
	return (inf_ptr->count_history = numbr);
}


/**
 * readHistFile - that reads history from file into linked lists of string
 * @inf_ptr: pointer to a struct
 * Return: count_history on success, 0 otherwise
 */
int readHistFile(exec_info *inf_ptr)
{
	int numbr, end = 0, numCount = 0;
	ssize_t filedes, readLn, fileSize = 0;
	struct stat inf;
	char *buffer = NULL, *fi_name = getHistFile(inf_ptr);

	if (!fi_name) /*checks if 'fi_name'is empty*/
		return (0);
	filedes = open(fi_name, O_RDONLY);/*open sys call*/
	free(fi_name); /*mem allocated for 'fi_name' var is freed*/
	if (filedes == -1) /*checks if open() call was successful*/
		return (0);
	if (!fstat(filedes, &inf))/*to get inf_ptr about file*/
		fileSize = inf.st_size;
	if (fileSize < 2) /*checks if file is less than 2 bytes*/
		return (0);
/*memory allocation of 'buffer' in heap using malloc*/
	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);
	readLn = read(filedes, buffer, fileSize); /*read system call*/
	buffer[fileSize] = 0; /* adds null terminator at end of buffer*/
	if (readLn <= 0) /*checks if read() was successful*/
		return (free(buffer), 0);
	close(filedes); /*closes file associated with 'filedes'*/
	for (numbr = 0; numbr < fileSize; numbr++) /*loop to iterate over 'buffer'*/
		if (buffer[numbr] == '\n')
		{
			buffer[numbr] = 0;
			genHistList(inf_ptr, buffer + end, numCount++);
			end = numbr + 1;
		}
	if (end != numbr)
		genHistList(inf_ptr, buffer + end, numCount++);
	free(buffer); /*frees mem allocated to 'buffer'*/
	inf_ptr->count_history = numCount;
/*nodes from 'history' deleted until numbr of nodes is <= 'HIST_MAX'*/
	while (inf_ptr->count_history-- >= HIST_MAX)
		delNode(&(inf_ptr->history), 0);
	refreshHistList(inf_ptr);
	return (inf_ptr->count_history);
}


/**
 * getHistFile - fnctn that a dynamic string with history file path
 * @inf_ptr: pointer to a struct
 * Return: a strring contaning history of file
 */

char *getHistFile(exec_info *inf_ptr)
{
	char *buffer, *directory;

	directory = shgetenv(inf_ptr, "HOME=");
/*fnctn to check whether 'directory' is NULL*/
	if (!directory)
		return (NULL);
/*memory allocation in  the heap using malloc*/
	buffer = malloc(sizeof(char) *
	(str_length(directory) + str_length(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
/*'buffer is set to '0'  to show that it is an empty string*/
	buffer[0] = 0;
	copy_string(buffer, directory); /*copies cal of 'directory' to  'buffer'*/
	str_concat(buffer, "/");
	str_concat(buffer, HIST_FILE); /*concats val of 'HIST_FILE'*/
	return (buffer);
}

/**
 * genHistList - fnctn adds an entry to a linked list of cmd history
 * @inf_ptr: pointer to a struct
 * @buf: buffer
 * @linecount: parameter
 * Return: 0 (Success)
 */
int genHistList(exec_info *inf_ptr, char *buf, int linecount)
{
/*Declaration of variables*/
	pass_list *n = NULL;
/*fnctn setes 'n'to address of first node in linked list*/
	if (inf_ptr->history)
		n = inf_ptr->history;
/*fnctn to append a new node to the linked list*/
	nodeAppend(&n, buf, linecount);
/*if fnctn to check whether 'inf_ptr->history' is NULL*/
	if (!inf_ptr->history)
		inf_ptr->history = n;
	return (0);
}
