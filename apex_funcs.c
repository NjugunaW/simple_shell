#include "chwa.h"

/**
 * nodeAdd - function that adds anew node to the beginnning of a linked list
 * @head_pptr: double pointer to linked list
 * @string: char
 * @num: int
 * Return: pointer to new head node
 */
pass_list *nodeAdd(pass_list **head_pptr, const char *string, int num)
{
/*Declaration of variables*/
	pass_list *n_hd;
/*fnctn to check whether 'head' is NULL*/
	if (!head_pptr)
		return (NULL);
/*memory is allocated fo the new node using malloc*/
	n_hd = malloc(sizeof(pass_list));
/*fncnt to check whether malloc was successful*/
	if (!n_hd)
		return (NULL);
/*'memset' fncnt initializes the me allocated for the new node to '0'*/
	_memset((void *)n_hd, 0, sizeof(pass_list));
	n_hd->numbr = num;
/*so long as 'string'is not null, a copy of string is created*/
/*and address of new string is assigned*/
	if (string)
	{
		n_hd->string = duplicate_str(string);
/*if 'duplicate_str' fails, the mem allocated for new node is freed*/
		if (!n_hd->string)
		{
			free(n_hd);
			return (NULL);
		}
	}
	n_hd->next = *head_pptr;
	*head_pptr = n_hd; /*pointer is updated to point to new head node*/
	return (n_hd);
}


/**
 * delNode - function that deletes node at specified index
 * @head_pptr: double pointer to a linked list
 * @index: index of node to be deleted
 * Return: 1 for success or 0 for failure
 */
int delNode(pass_list **head_pptr, unsigned int index)
{
/*Declaraton of variables*/
	pass_list *n, *pr_node;
	unsigned int num = 0;

/*function to check if the linked list is empty*/
	if (!head_pptr || !*head_pptr)
		return (0);
/*fnctn shows where the fisrt node needs to be deleted*/
	if (!index)
	{
		n = *head_pptr;
/*update '*head_pptr' to point to next node*/
		*head_pptr = (*head_pptr)->next;
/*mem de-allocation for first node */
		free(n->string);
		free(n);
		return (1);
	}
/*fnctn shows where another node needs to be deleted*/
	n = *head_pptr;
/*while loop to iterate over the list unti last node is reached*/
	while (n)
	{
		if (num == index)
		{
/*updating the 'next' pointer of previous node*/
			pr_node->next = n->next;
/*mem deallocation of 'string' field of deleted node*/
			free(n->string);
			free(n); /*frees mem allocated for node itself*/
			return (1);
		}
		num++;
		pr_node = n;
		n = n->next;
	}
	return (0);
}


/**
 * nodeAppend - function that adds a new node to the end of a linked list
 * @head_pptr: double pointer to the head node of list
 * @string: string to be added to the new node
 * @num: integer value to be added to new node
 * Return: pointer to new node added at the end of the list
 */
pass_list *nodeAppend(pass_list **head_pptr, const char *string, int num)
{
/*Declaration of variables*/
	pass_list *n_nde, *n;
/*fnctn to check if '*head' is NULL*/
	if (!head_pptr)
		return (NULL);

	n = *head_pptr;
/*mem is allocated for the new node using malloc*/
	n_nde = malloc(sizeof(pass_list));
	if (!n_nde)/*checks if malloc was successful*/
		return (NULL);
/*'memset' fncnt initializes the me allocated for the new node to '0'*/
	_memset((void *)n_nde, 0, sizeof(pass_list));
	n_nde->numbr = num;
/*as long as 'string'is not null, a copy of string is created*/
/*and address of new string is assigned*/
	if (string)
	{
		n_nde->string = duplicate_str(string);
		if (!n_nde->string)
		{
			free(n_nde);
			return (NULL);
		}
	}
	if (n) /*checks wether the list is empty*/
	{
/*while loo to iterate over the list until last node is reached*/
		while (n->next)
			n = n->next;
		n->next = n_nde;
	}
	else
		*head_pptr = n_nde; /*pointer is updated to point to new node*/
	return (n_nde);
}
