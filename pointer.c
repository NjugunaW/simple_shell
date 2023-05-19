#include "chwa.h"

/**
 * getIndex - function that returns index of node in linked list
 * @lst_head: pointer to linked list
 * @node_ptr: pointer
 * Return: index of node or -1 for otherwise
 */
ssize_t getIndex(pass_list *lst_head, pass_list *node_ptr)
{
/*declaration of variables and initializes it to zero*/
	size_t size_1 = 0;
/*while loop to iterate over the linked list*/
	while (lst_head)
	{
/*fnctn to chck whether 'head' is equal to 'node'*/
		if (lst_head == node_ptr)
			return (size_1);
/*if above is not true, fnctn advances to next node and increments size_l*/
		lst_head = lst_head->next;
		size_1++;
	}
	return (-1);
}


/**
 * list2string - a fnctn that returns an array of strings
 * @lst_head: pointer to linked list
 * Return: strs
 */
char **list2string(pass_list *lst_head)
{
/*Declaration of variables*/
	pass_list *n = lst_head;
	size_t size_1 = listLength(lst_head), j;
	char **strs;
	char *string;
/*fnctn to check if head and size_l are NULL*/
	if (!lst_head || !size_1)
		return (NULL);
/*memory is allocated for 'strs' using malloc*/
	strs = malloc(sizeof(char *) * (size_1 + 1));
	if (!strs) /*checks if malloc was successful*/
		return (NULL);
/*for loop to iterate over linked list and mem is allocated for each node*/
	for (size_1 = 0; n; n = n->next, size_1++)
	{
		string = malloc(str_length(n->string) + 1);
/*if malloc fails, all previously allocated mem is freed*/
		if (!string)
		{
			for (j = 0; j < size_1; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
/*else, string from current node's 'string' is copied to files 'string'*/
		string = copy_string(string, n->string);
		strs[size_1] = string;
	}
	strs[size_1] = NULL;
	return (strs);
}

/**
 * listLength - function that determines the length of a linked list
 * @h: pointer to linked list
 * Return: length of list
 */
size_t listLength(const pass_list *h)
{
/*Declaration of variables*/
	size_t size_1 = 0;
/*while loop to itrate over 'h' so long as it is not NULL*/
	while (h)
	{
		h = h->next;
		size_1++;
	}
/*return length of list*/
	return (size_1);
}


/**
 * prefixSearch - functn that searches a linked list for a specific prefix
 * @node_ptr: pointer to linked list
 * @prefix: pointer
 * @c: character
 * Return: prefix or null
 */
pass_list *prefixSearch(pass_list *node_ptr, char *prefix, char c)
{
/**p is declared and initialized to NULL*/
	char *p = NULL;
/*while loop to iterate through the linked list*/
	while (node_ptr)
	{
/*'str_starts_with' checks nodes to see if it starts with 'prefix'*/
		p = str_starts_with(node_ptr->string, prefix);
/*fnctn to check the next char if 'prefix' matches 'c'*/
		if (p && ((c == -1) || (*p == c)))
			return (node_ptr);
		node_ptr = node_ptr->next;
	}
	return (NULL);
}


/**
 * lstPrt - a function that prints all contents in a list
 * @h: pointer to linked list
 * Return: size_l
 */
size_t lstPrt(const pass_list *h)
{
/*Declaration of variable*/
	size_t size_1 = 0;
/*while loop to iterate over the linked list as long as 'h' is not NULL*/
	while (h)
	{
		_puts(numConverter(h->numbr, 10, 0)); /*prints numbr mem of list*/
		_putchar(':'); /*prints :*/
		_putchar(' '); /*prints ' '*/
/*prints the 'string' member of linked list node as string*/
		_puts(h->string ? h->string : "(nil)");
		_puts("\n"); /*prints new line*/
		h = h->next; /*updates '*h'*/
		size_1++;
	}
	return (size_1);
}
