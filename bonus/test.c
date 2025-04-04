// test cases for asm, core
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
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
