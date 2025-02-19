#include <stdio.h>

typedef struct s_list
{
    void *data;
    struct s_list *next;
}     t_list;

int main()
{
  t_list start;
  t_list next;
  char *a = "test";

  start.data = (void *) a;
  start.next = &next;

  printf("%s\n", (char *) start.data);
}