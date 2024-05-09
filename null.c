#include <stdio.h>

// gcc -std=c17 -Wall -Wpedantic -Wextra -Wdeprecated -pedantic -g -O2 null.c -o null && ./null
int main(void)
{
  int *i = NULL;
  int **j = &i;

  printf("\ti = %p\t\t *j = %p\t  j = %p\n", (void *)i, (void *)*j, (void *)&j);

  int k = 10;
  *j = &k;

  printf("*i = %d i = %p  *j = %p j = %p\n", *i, (void *)i, (void *)*j, (void *)&j);

  return 0;
}

/**
 *  OUTPUT:
 *           i = 0x0          *j = 0x0	       j = 0x16b64b1a0
 *   *i = 10 i = 0x16b64b19c  *j = 0x16b64b19c j = 0x16b64b1a0
 */
