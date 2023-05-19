#include "chwa.h"

/**
 * strListPrt - fnctn that prints conents of each node in a linked list
 * @lst_ptr: pointer to alinked list
 * Return: number of nodes in list
 */
size_t strListPrt(const pass_list *lst_ptr)
{
/*Declaration of variables*/
	size_t size_1 = 0;
/*while loop to iterate over the linked lsit as long as 'h' is not NULL*/
	while (lst_ptr)
	{
		_puts(lst_ptr->string ? lst_ptr->string : "(nil)");
		_puts("\n");
		lst_ptr = lst_ptr->next;
		size_1++;
	}
	return (size_1); /*returns numbr of nodes in list*/
}


/**
 * listFree - function that frees the memory allocated for linked list
 * @head_ptr: double pointet to linked list
 */
void listFree(pass_list **head_ptr)
{
/*Declaration of variables*/
	pass_list *n, *n_nde, *head;
/*fnctn to check whether the linked list is empty*/
	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	n = head;
/*while loop to iterate over the linked list */
	while (n)
	{
		n_nde = n->next;
		free(n->string); /*'freeing mem allocated for 'string'' field*/
/*of node being deleted*/
		free(n); /*freeing me allocated for node itself*/
		n = n_nde;
	}
	*head_ptr = NULL; /*ensures head pointer points to a free memory*/
}
