#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{
  struct list_node * new_node = malloc(sizeof(struct list_node));
  if (new_node == NULL)
  {
    return NULL;
  }
  new_node -> value = value;
  new_node -> next = NULL;

  return new_node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * node = new_node(value);
  if (node == NULL)
  {
    return;
  }
  struct list_node * save_node = list -> head;
  list -> head = node;
  if (list -> head != NULL)
  {
    list -> head -> next = save_node;
  }
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node * node = new_node(value);
  if (node == NULL)
  {
    return;
  }
  if (list == NULL)
  {
    return;
  }
  if (list -> head == NULL)
  {
    list -> head = node;
    return;
  }
  struct list_node * curr_node = list -> head;
  while (curr_node -> next != NULL)
  {
    curr_node = curr_node -> next;
  }
  curr_node -> next = node;
}

size_t remove_from_head(struct linked_list *list) 
{
  if (list -> head == NULL)
  {
    return 0; 
  }
  size_t value = list -> head -> value;

  struct list_node * save_node = list -> head;
  list -> head = list -> head -> next;

  free(save_node);

  return value;
}

size_t remove_from_tail(struct linked_list *list) 
{
  if (list -> head == NULL)
  {
    return 0;
  }
  size_t value = 0;
  if (list -> head -> next == NULL)
  {
    value = list -> head -> value;
    free(list -> head);
    return value;
  }
  struct list_node * curr_node = list -> head;
  while (curr_node -> next -> next != NULL)
  {
    curr_node = curr_node -> next;
  }
  value = curr_node -> next -> value;
  free(curr_node -> next);
  curr_node -> next = NULL;

  return value;

}

void free_list(struct linked_list list) 
{
  struct list_node * node;
  while ((list.head != NULL))
  {
    node = list.head;
    list.head = list.head -> next;
    free(node);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
