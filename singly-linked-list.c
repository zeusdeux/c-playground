#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./zdx_util.h"

typedef int8_t val_t;

typedef struct singly_linked_list {
  val_t value;
  struct singly_linked_list *next;
} sll_t;

/**
 * SINGLY LINKED LISTS OPERATIONS USING POINTERS TO POINTERS
 */
bool insert(sll_t **node, val_t value);
void delete(sll_t **prev, val_t value);
void deinit(sll_t **head);

/**
 * Utility functions
 */
void print(const char* header, sll_t *head);


/**
 * Compile command
 * gcc -std=c17 -g -O2 -Wall -Wpedantic -Wextra -Wdeprecated -pedantic singly-linked-list.c -o singly-linked-list && leaks -atExit -- ./singly-linked-list
 */
int main(void)
{
  sll_t *head = NULL;

  dbg("sizeof(sll_t) = %lu | sizeof(*sll_t) = %lu", sizeof(sll_t), sizeof(head));

  srand(1337);

  for (size_t i = 0; i < 10; i++) {
    // -128 to +127
    val_t value = (rand() % 256) - 128;
    if (!insert(&head, value)) {
      log(L_ERROR, "Insertion failed. (head = 0x%0.16lx, value = % hhd)", (uintptr_t)head, value);
    }
  }

  print("After inserts", head);

  delete(&head, -42);
  delete(&head, -122);
  delete(&head, 63);
  delete(&head, -81);
  delete(&head, 99); // NOT IN LINKED LIST

  print("After removes", head);

  deinit(&head);

  return 0;
}

bool insert(sll_t **node, val_t value)
{
  sll_t *temp = calloc(1, sizeof(*temp));

  if (temp == NULL) {
    return false;
  }

  temp->value = value;
  temp->next = *node;
  *node = temp;

  return true;
}

void delete(sll_t **prev, val_t value)
{
  sll_t *current = *prev;

  while (current) {
    if (current->value == value) {
      // change what either head (in the first iteration) or current->next points to (in later iterations)
      *prev = current->next;
      free(current);
    } else {
      // gimme the address of current->next so that I can indirectly change what next points to above
      prev = &current->next;
    }

    current = current->next;
  }
}

void deinit(sll_t **head)
{
  while (*head) {
    sll_t *temp = (*head)->next;
    free(*head);
    *head = temp;
  }
}

void print(const char* header, sll_t *head)
{
  printf("--------------------------------\n");
  printf("%s\n", header);
  printf("--------------------------------\n");

  while(head) {
    printf("(this = 0x%0.16lx, value = % 0.3hhd, next = 0x%0.16lx)\n", (uintptr_t)head, head->value, (uintptr_t)head->next);
    //                                  ^ this space automatically leaves a space for minus (-) sign
    head = head->next;
  };

  printf("(this = 0x%0.16lx, <empty>)\n", (uintptr_t)head);
}
