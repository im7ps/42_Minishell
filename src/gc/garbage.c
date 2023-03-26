#include "../../inc/minishell.h"

// Funzione per aggiungere un nuovo nodo alla lista
void add_node(t_garbage** head, void* ptr) 
{
    t_garbage* new_node = (t_garbage*) malloc(sizeof(t_garbage));
    new_node->ptr = ptr;
    new_node->next = *head;
    *head = new_node;
}

// Funzione per liberare la memoria allocata per ogni nodo della lista
void ft_garbage_collector(t_garbage* head) 
{
	t_garbage* temp;

	temp = NULL;
    while (head != NULL) 
	{
        free(head->ptr);
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Funzione per allocare la memoria per una nuova variabile e aggiungere un nuovo nodo alla lista
void* gc_alloc(t_garbage** head, int size, int count)
{
    void* ptr = malloc(size);
	if (count != 0)
	{
		ft_bzero(ptr, count);
	}
    add_node(head, ptr);
    return (ptr);
}
