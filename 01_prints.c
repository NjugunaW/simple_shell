#include "chwa.h"

/**
 * errPrt - a fnctn tha prints an error mssge to the std error output
 * @inf_ptr: pointer to a struct
 * @my_str: string
 * Return: 0 if the are no numbers in string, converted numbr
 *        -1 on error
 */
void errPrt(exec_info *inf_ptr, char *my_str)
{
/*fnctn to print the name of file associated with error mssge*/
	shputs(inf_ptr->finame);
	shputs(": ");
/*fnctn to decrement val of linked list then print new val to std err output*/
	decPtr(inf_ptr->cnt_line, STDERR_FILENO);
	shputs(": ");
/*fnctn to rpint the name of the program that produced the error message*/
	shputs(inf_ptr->argv[0]);
	shputs(": ");
/*fnctn that pritns the specifies error*/
	shputs(my_str);
}

/**
 * decPtr - a function that prints a decimal number to a file descriptor
 * @num_input: integer
 * @my_fd: file descriptor
 * Return: number of characters printed
 */
int decPtr(int num_input, int my_fd)
{
/*Declaration of variables*/
	int (*__putchar)(char) = _putchar;
	int numbr, count = 0;
	unsigned int absol, curr;
/*if statement to check if my_fd is equal to STDERR_FILENO & prints std err*/
	if (my_fd == STDERR_FILENO)
		__putchar = shputchar;
/*statement to check if 'input' is less that '0'*/
	if (num_input < 0)
	{
		absol = -num_input;
		__putchar('-');
		count++;
	}
/*'absol' is set to 'input' if input is not negative*/
	else
		absol = num_input;
/*fcntn to keep track of current numbr being printed*/
	curr = absol;
	for (numbr = 1000000000; numbr > 1; numbr /= 10)
	{
		if (absol / numbr)
		{
			__putchar('0' + curr / numbr);
			count++;
		}
		curr %= numbr;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}
