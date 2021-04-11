
/*  Written by Danish Amjad Alvi
    University College London
    Department of Computer Science

    Elements of Programming Interviews
    Adnan Aziz, Tsung Hsien Lee, Amit Prakash
    Version 1.5.9

    8.6 - 'Delete a node from a Singly Linked List' (Page 118)
*/
#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node *link;
};


/* This function creates a new node */

struct node *create(struct node *next, int data)
{
  struct node *new_node = malloc(sizeof(*new_node));
  if(new_node == NULL)
  {
    printf("ERROR! Memory Allocation was unsucessful!");
    exit(0);
  }
  new_node->data = data;
  new_node->link = next;

  return new_node;
}

void prepend(struct node **head, int data)
{
  struct node *new_node = create(*head, data);
  *head = new_node;
}

void display(struct node **head)
{
  struct node *temp = *head;
  if(*head == NULL)
  {
    printf("ERROR! Linked List is empty!");
    exit(0);
  }
  else
  {
    printf("\n%i ", temp->data);
    while(temp->link != NULL)
    {
      temp = temp->link;
      printf("%i ", temp->data);
    }
  }
}

void search(struct node **head, struct node **cursor, int value)
{
  struct node *iterator = *head;
  while(iterator->data != value)
  {
    if(iterator->link == NULL)
    {
      printf("\nERROR! Element %i was not found!", value);
      break;
    }
    iterator = iterator->link;
  }
  *cursor = iterator;
}

void delete_front(struct node **head)
{
  struct node *temp = (*head)->link;
  free(*head);
  *head = temp;
}

void delete_any(struct node **head, struct node **cursor)
{
  if(*cursor == *head)
  {
    delete_front(head);
  }
  else
  {
    struct node *back, *iterator = *head;
    while(iterator != *cursor)
    {
      back = iterator;
      iterator = iterator->link;
    }
    back->link = iterator->link;
    free(iterator);
  }
}

int main()
{
  struct node *LinkedList = NULL;
  
  for(int i = 9; i >= 0; i++)
  {
    prepend(&LinkedList, i);
  }
  
  struct node *cursor;
  search(&LinkedList, &cursor, 5);
  display(&LinkedList);
  printf("\nDeleting element %i:", cursor->data);
  delete_any(&LinkedList, &cursor);
  display(&LinkedList);
  printf("\n");
}
