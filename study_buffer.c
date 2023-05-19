#include "chwa.h"

/**
 * inBuff - fnctn that reads input data and stores it in a buffer
 * @inf_ptr: pointer to a struct
 * @p_buf: ponter to a char
 * @len: pointer to a variable
 * Return: number of bytes read
 */
ssize_t inBuff(exec_info *inf_ptr, char **p_buf, size_t *len)
{
/*Declaration of variables*/
	ssize_t a = 0;
	size_t lng = 0;
/*fnctn that checks if value of 'len' is '0'*/
	if (!*len)
	{
/*code executes if 'len' is '0' and mem pointed to by 'p_buf' is deallocated*/
		free(*p_buf);
		*p_buf = NULL;
		signal(SIGINT, signalInterruptH);
/*code t check whether 'USE_GETLINE' is defined*/
#if USE_GETLINE
		a = getline(p_buf, &lng, stdin);
/*if 'USE_GETLINE' is not defined, fnctn calls 'lineGet' to read input*/
#else
		a = lineGet(inf_ptr, p_buf, &lng);
#endif
/*fnctn to check whether 'a' is greater than '0' and if so,*/
/*newline is removed from buffer pointed to by 'buf'*/
		if (a > 0)
		{
			if ((*p_buf)[a - 1] == '\n')
			{
				(*p_buf)[a - 1] = '\0';
				a--;
			}
/*fnctn to show that line has been read*/
			inf_ptr->count_flag = 1;
/*fnctn to remove comment in buffer*/
			delComments(*p_buf);
/*fnctn to add input in history list*/
			genHistList(inf_ptr, *p_buf, inf_ptr->count_history++);
			{
				*len = a;
				inf_ptr->cmand_buff = p_buf;
			}
		}
	}
	return (a);
}



/**
 * readBuffer - a function that takes in three parameters
 * @inf_ptr: pointer to a struct
 * @p_buf: char
 * @i: variale
 * Return: value of ssize_t
 */
ssize_t readBuffer(exec_info *inf_ptr, char *p_buf, size_t *i)
{
/*Declaration of variables*/
	ssize_t a = 0;
/*fnctn to check whether '*i' is '0'*/
	if (*i)
		return (0);
/*system call read() is called and returned value is stored in 'a'*/
	a = read(inf_ptr->rd_filedes, p_buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * lineGet - function that represents the size of pre-allocated buffer
 * @inf_ptr: pointer to a struct
 * @ptr: double pointer to a char buffer
 * @length: var that reps the size of pre-allocted buffer
 * Return: integer value s
 */
int lineGet(exec_info *inf_ptr, char **ptr, size_t *length)
{
/*Declaration of variables*/
	static char buffer[READ_BUF_SIZE];
	static size_t size_1, len;
	size_t k;
	ssize_t a = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
/*if 'p' and 'length' are not NULL, the val of 'length' is assigned to 's'*/
	p = *ptr;
	if (p && length)
		s = *length;
/*if buffer is full 'size_1' and 'len' are reset to '0'emptying the  buffer*/
	if (size_1 == len)
		size_1 = len = 0;
/*'readBuffer() is called to read data in the 'buffer'*/
	a = readBuffer(inf_ptr, buffer, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);
/*'chrLoc' is used to locate the position of next newline char in 'buffer'*/
	c = chrLoc(buffer + size_1, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
/*fnctn checks if malloc was successful*/
	if (!new_p)
		return (p ? free(p), -1 : -1);
/*fnctn to concat date to the end of exisitng string*/
	if (s)
		catStr(new_p, buffer + size_1, k - size_1);
	else
		cpystr(new_p, buffer + size_1, k - size_1 + 1);
/*updaating values*/
	s += k - size_1;
	size_1 = k;
	p = new_p;
/*updating 'length' parameter if it is not NULL*/
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * signalInterruptH - function that handles SIGINT signal
 * @sig_num: integer parameter
 */
void signalInterruptH(__attribute__((unused))int sig_num)
{
/*function calls to print chars in std output*/
	_puts("\n"); /*newline*/
	_puts("$ "); /*shell prompt*/
	_putchar(BUF_FLUSH); /*flushes output buffer*/
}

/**
 * gInput - fnctnthat readus user input and parses to separate commands
 * @inf_ptr: pointer to a struct
 * Return:number of read bytes
 */
ssize_t gInput(exec_info *inf_ptr)
{
/*Declaration of variables*/
	static char *buffer;
	static size_t size_1, size_2, len;
	ssize_t a = 0;
	char **buf_p = &(inf_ptr->arg), *p;
/*fnctn to write flush char to std output and reads input using inBuff*/
	_putchar(BUF_FLUSH);
	a = inBuff(inf_ptr, &buffer, &len);
/*checks if numbr of byts read is '-1'. If so, it ret '-1' to show EOF*/
	if (a == -1)
		return (-1);
/*if length of buffer is not '0' there are still cmds left in chain bufer*/
	if (len)
	{
/*initialization of new iterator to present position of buffer*/
		size_2 = size_1;
		p = buffer + size_1;
		chainer(inf_ptr, buffer, &size_2, size_1, len);
/*while loop to check whether en of buffer has been reached*/
		while (size_2 < len)
		{
			if (chainTester(inf_ptr, buffer, &size_2))
				break;
			size_2++;
		}

		size_1 = size_2 + 1;
		if (size_1 >= len)
		{
			size_1 = len = 0;
			inf_ptr->cmand_buff_tp = CMD_NORM;
		}
/*fnctn then passes pointer back to current command position*/
		*buf_p = p;
		return (str_length(p));
	}

	*buf_p = buffer;
/*fnctn returns numbr of bytes read*/
	return (a);
}
