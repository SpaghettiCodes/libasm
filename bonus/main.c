#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    void *data;
    struct s_list *next;
}     t_list;


extern void ft_list_push_front(t_list **begin_list, void *data);
int       	ft_list_size(t_list *begin_list);
void        ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void        ft_list_sort(t_list **begin_list, int (*cmp)());
void        func_run(void (*test)());

t_list *ft_list_create(void *data) {
  t_list *ret = malloc(sizeof(t_list));
  ret->data = data;
  ret->next = NULL;
  return ret;
}

int ft_strlen(char *str) {
  int i = 0;
  while (str[i]) {
    i++;
  };
  return i;
}

int cmp_str(char *one, char *two) {
  return ft_strlen(one) != ft_strlen(two);
}

void free_node(void *data) {
  printf("removing %s\n", (char *) data);
  // free(data);
  // printf("freed\n");
}

void garbage() {
  printf("called from garbage 101\n");
}

int main()
{
  char *one = "one";
  char *two = "two";
  char *three = "three";
  char *abc = "abc";
  char *def = "def";

  t_list *head = ft_list_create(one);
  printf("%s\n", (char *) head->data);

  printf("=== ft_list_push_front ==\n");
  ft_list_push_front(&head, (void *) two);
  printf("%s\n", (char *) head->data);
  printf("%s\n", (char *) head->next->data);

  free(head->next);
  free(head);

  printf("=== ft_list_size ==\n");
  head = ft_list_create(one);
  printf("%d\n", ft_list_size(head)); // 1
  ft_list_push_front(&head, two);
  printf("%d\n", ft_list_size(head)); // 2
  ft_list_push_front(&head, three);
  printf("%d\n", ft_list_size(head)); // 3
  printf("%d\n", ft_list_size(NULL)); // 0
  free(head->next->next);
  free(head->next);
  free(head);

  printf("=== testing stuff ===\n");
  printf("%d\n", cmp_str("one", "two")); // true
  char *test = malloc(4);
  free_node((void *) test);
  func_run(garbage);

  printf("=== ft_list_remove_if ==\n");
  head = ft_list_create(one);
  ft_list_push_front(&head, two);
  ft_list_push_front(&head, three);
  ft_list_remove_if(&head, "123", cmp_str, free_node); // one and two should be removed

  printf("%d\n", ft_list_size(head)); // 1
  if (head) {
    printf("%s\n", (char *) head->data); // three
  } else {
    printf("lmao head set to null\n");
  }
}