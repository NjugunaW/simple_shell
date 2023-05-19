#include "chwa.h"

/**
 * chainTester - function that checks if given char in string is a chain delim
 * @inf_pt: pointer to a struct
 * @b_buf: character buffer
 * @v_pt: pointer to a variable
 * Return: 1 if there is a chain delimeter or 0 for otherwise
 */
int chainTester(exec_info *inf_pt, char *b_buf, size_t *v_pt)
{
/*Declaration of variables*/
	size_t size_1 = *v_pt;
/*checks if chars in string are ('||'), if so, replaces with ('\0')*/
	if (b_buf[size_1] == '|' && b_buf[size_1 + 1] == '|')
	{
		b_buf[size_1] = 0;
		size_1++;
		inf_pt->cmand_buff_tp = CMD_OR;
	}
/*checks if chars in string are &&, if so, replaces with 'size_l'*/
	else if (b_buf[size_1] == '&' && b_buf[size_1 + 1] == '&')
	{
		b_buf[size_1] = 0;
		size_1++;
		inf_pt->cmand_buff_tp = CMD_AND;
	}
/*checks if char at pos 'size_l' is (';'), if so, replcase with ('\0')*/
	else if (b_buf[size_1] == ';')
	{
		b_buf[size_1] = 0;
		inf_pt->cmand_buff_tp = CMD_CHAIN;
	}
/*if char at pos 'size_l'is not a chain delim, fnctn returns '0'*/
	else
		return (0);
	*v_pt = size_1;
	return (1); /*char at pos 'size_l' is a chain delim*/
}

/**
 * chainer - fnctn in shell to check if prev cmd has failed or succeeded
 * @inf_pt: pointer to a struct
 * @b_buf: the character buffer
 * @v_pt: pointer
 * @f: starting position
 * @ln: ln of buffer
 */
void chainer(exec_info *inf_pt, char *b_buf, size_t *v_pt, size_t f, size_t ln)
{
/*Declaration of variables*/
	size_t size_1 = *v_pt;
/*fnctn to check if 'cmand_buff_tp' in struct is set to 'CMD_AND'*/
/*if so, it checks if prev cmd executed successfully*/
	if (inf_pt->cmand_buff_tp == CMD_AND)
	{
		if (inf_pt->exec_status)
		{
			b_buf[f] = 0;
			size_1 = ln;
		}
	}
/*fnctn checks if curr cmd buffer is 'CMD_OR and if prev cmd is false*/
	if (inf_pt->cmand_buff_tp == CMD_OR)
	{
		if (!inf_pt->exec_status)
		{
			b_buf[f] = 0;
			size_1 = ln;
		}
	}

	*v_pt = size_1;/*val pointed to by '*v_pt' is set new val of 'size_1'*/
}
