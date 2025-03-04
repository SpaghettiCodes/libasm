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
long        ft_atoi_base(char *str, char *base);

int         find(char *haystack, char needle);

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

int cmp_int(int *one, int *two) {
  return (*one - *two);
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

void printIntList(t_list *start) {
  while (start) 
  {
    printf("%d | ", *((int *) start->data));
    start = start->next;
  }
  printf("\n");
}

int main()
{
  printf("=== ft_atoi_base ==\n");
  printf("%ld\n", ft_atoi_base(" \t\r\n   +++---483a465", "0123456789"));
  printf("%ld\n", ft_atoi_base("abc12", "0123456789abcdef")); // 703506

  char *one = "one";
  char *two = "two";
  char *three = "three";
  char *abc = "abc";
  char *def = "def";

  t_list *head = ft_list_create(one);
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

  printf("=== ft_list_remove_if ==\n");
  head = ft_list_create(one);
  ft_list_push_front(&head, two);
  ft_list_push_front(&head, three);
  ft_list_remove_if(&head, "123", cmp_str, free_node); // one and two should be removed

  printf("%d\n", ft_list_size(head)); // 1
  if (head) {
    printf("%s\n", (char *) head->data); // three
    free(head);
  } else {
    printf("lmao head set to null\n");
  }

  printf("=== ft_list_sort ==\n");
  // int ints[] = {0,1,2,3,4,5,6,7};
  // https://numbergenerator.org/randomnumberlist-1-10#!numbers=100&low=1&high=100&unique=true&csv=csv&oddeven=&oddqty=0&sorted=false&addfilters=
  int ints[] = {69,66,63,99,87,6,13,37,23,35,81,80,2,29,28,94,95,44,32,67,16,12,47,74,84,89,41,56,98,17,7,25,48,100,72,70,46,91,71,11,34,14,27,24,20,40,26,79,22,36,76,61,86,57,59,43,93,54,78,42,62,82,5,85,51,10,1,21,52,75,60,31,8,55,50,58,3,38,53,39,65,96,83,77,19,92,97,49,4,30,18,64,15,45,90,33,88,68,9,73};
  // int ints[] = {0, 1};
  // int ints[] = {1, 0};
  // int ints[] = {0, 1, 2};

  head = ft_list_create(&ints[0]);
  for (int i = 1; i < sizeof(ints) / sizeof(int); ++i) {
    ft_list_push_front(&head, &ints[i]);
  }
  
  printf("Before\n");
  printIntList(head);
  ft_list_sort(&head, cmp_int);
  printf("After\n");
  printIntList(head);
}