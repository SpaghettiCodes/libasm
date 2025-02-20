#include <stdio.h>

typedef struct s_list
{
    void *data;
    struct s_list *next;
}     t_list;

void  ft_list_push_front(t_list **begin_list, void *data);

int main()
{
  t_list start;
  t_list next;
  char *a = "test";

  start.data = (void *) a;
  start.next = &next;

  printf("%s\n", (char *) start.data);
  printf("%p\n", &start);
  printf("%p\n", &start.data);
  printf("%p\n", &start.next);
  printf("%p\n", &next);
  printf("%p\n", &next.data);
  printf("%p\n", &next.next);

}