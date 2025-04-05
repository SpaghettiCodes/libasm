// test cases for asm, bonus
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

long        ft_atoi_base(char *str, char *base);
extern void ft_list_push_front(t_list **begin_list, void *data);
int       	ft_list_size(t_list *begin_list);
void        ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void        ft_list_sort(t_list **begin_list, int (*cmp)());

#define BRUTE_FORCE_TESTS 1000

// whaat the heck, why string.h no strdup
char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) return NULL;
    strcpy(dst, src);
    return dst;
}

t_list *ft_list_create(void *data) {
    t_list *ret = malloc(sizeof(t_list));
    ret->data = data;
    ret->next = NULL;
    return ret;
}

int cmp_int(int *one, int *two) {
    return (*one - *two);
}

int printf_cmpInt(int *one, int *two) {
    printf(""); // yes, this is intended, if you didnt align stack frame, your ft_list_remove_if will crash
    return (*one - *two);
}

void free_node(void *data) {
    free(data);
}

int *create_intNode(int value) {
    int *store = malloc(sizeof(int));
    *store = value;
    return store;
}

t_list *create_random_int_list(int listSize) {
    t_list *ret = NULL;
    t_list *prev = NULL;
    for (int i = 0; i < listSize; ++i) {
        t_list *next = ft_list_create(create_intNode(rand() % 10000));
        if (prev) {
            prev->next = next;
        }
        if (!ret) {
            ret = next;
        }
        prev = next;
    }
    return ret;
}

void free_list(t_list *head) {
    t_list *temp;
    while (head) {
        free(head->data);
        temp = head->next;
        free(head);
        head = temp;
    }
}

void printIntList(t_list *start) {
    while (start) 
    {
      printf("%d | ", *((int *) start->data));
      start = start->next;
    }
    printf("\n");
  }

int isSorted(t_list *head) {
    while (head) {
        if (!head->next) {
            return 1;
        }
        if (*(int *)head->data > *(int *)head->next->data) {
            printf("%d and %d is in the wrong position!\n", *(int *)head->data, *(int *)head->next->data);
            return 0;
        }
        head = head->next;
    }
    // uhh, no way we will reach here actually
    return 0;
}

void test_ft_pushFront() {
    // yeah no, im letting this crash, push front to NULL makes no sense
    // ft_list_push_front(NULL, strdup("nope"));

    int ok = 1;

    // test empty
    t_list *empty = NULL;
    char *str = strdup("Test");
    ft_list_push_front(&empty, str);
    if (empty != NULL) {
        // yes, im comparing pointer values here, it should be equal
        if (empty->data != str) {
            printf("ERROR! ft_push_front not assigning data properly!\n");
            ok = 0;
        }
    } else {
        printf("ERROR! ft_push_front not creating new nodes!\n");
        ok = 0;
    }
    free_list(empty); // here will free str also, dont double free

    // test one existing
    char *str2 = strdup("test");
    t_list *one = ft_list_create(str2);
    str = strdup("newTest");
    ft_list_push_front(&one, str);
    if (one) {
        if (one->data != str) {
            printf("ERROR! ft_push_front not adding values\n");
            ok = 0;
        } 
        if (one->next == NULL) {
            printf("ERROR! ft_push_front not setting next value properly\n");
            ok = 0;
        } else {
            if (one->next->data != str2) {
                printf("ERROR! ft_push_front modifying subsequent values\n");
                ok = 0;
            }
        }
    } else {
        printf("ERROR! ft_push_front setting original nodes to NULL!\n");
        ok = 0;
    }
    free_list(one);

    // test two existing
    str2 = strdup("test2");
    char *str3 = strdup("test3");
    t_list *two_a = ft_list_create(str2);
    t_list *two_b = ft_list_create(str3);
    two_a->next = two_b;
    str = strdup("test1");
    ft_list_push_front(&two_a, str);

    if (two_a) {
        if (two_a->data != str) {
            printf("ERROR! ft_push_front not adding values\n");
            ok = 0;
        } 
        if (two_a->next == NULL) {
            printf("ERROR! ft_push_front not setting next value properly\n");
            ok = 0;
        } else {
            if (two_a->next->data != str2) {
                printf("ERROR! ft_push_front modifying subsequent values\n");
                ok = 0;
            }
            if (two_a->next->next == NULL) {
                printf("ERROR! ft_push_front deleting existing data!\n");
                ok = 0;
            } else {
                if (two_a->next->next->data != str3) {
                    printf("ERROR! ft_push_front modifying subsequent values\n");
                    ok = 0;
                }
            }
        }
    } else {
        printf("ERROR! ft_push_front setting original nodes to NULL!\n");
        ok = 0;
    }
    free_list(two_a);

    if (ok) {
        printf("ft_push_front OK!\n");
    }
}

void test_ft_ListSize() {
    int ok = 1;
    // test empty
    if (ft_list_size(NULL) != 0) {
        printf("ERROR! ft_list_size returing value for NULL head!\n");
        ok = 0;
    }

    // random testing
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        int size = (rand() % 1000) + 1;
        t_list *random = create_random_int_list(size);
        int gotten = ft_list_size(random);
        if (gotten != size) {
            printf("ERROR! ft_list_size returing wrong value, expected %d gotten %d\n", size, gotten);
            ok = 0;
        }
        free_list(random);
    }

    if (ok) {
        printf("ft_list_size OK!\n");
    }
}

void test_ft_ListSort() {
    int ok = 1;

    // test NULL
    // uhh idk if this is supposed to crash, ig it should? 
    // just make it not crash just in case ba
    ft_list_sort(NULL, cmp_int);

    // test empty
    t_list *empty = NULL;
    ft_list_sort(&empty, cmp_int);
    // should not crash

    // test one element only
    t_list *one = ft_list_create(create_intNode(1));
    ft_list_sort(&one, cmp_int);
    free_list(one);

    // test two sorted element
    t_list *two_sorted_a = ft_list_create(create_intNode(1));
    t_list *two_sorted_b = ft_list_create(create_intNode(2));
    two_sorted_a->next = two_sorted_b;

    ft_list_sort(&two_sorted_a, cmp_int);

    if (*(int *)two_sorted_a->data > *(int *)two_sorted_a->next->data) {
        printf("ERROR! ft_list_sort sorting when its not supposed to!");
        ok = 0;
    }

    free_list(two_sorted_a);

    // test two unsorted element
    t_list *two_unsorted_a = ft_list_create(create_intNode(2));
    t_list *two_unsorted_b = ft_list_create(create_intNode(1));
    two_unsorted_a->next = two_unsorted_b;

    ft_list_sort(&two_unsorted_a, cmp_int);

    if (*(int *)two_unsorted_a->data > *(int *)two_unsorted_a->next->data) {
        printf("ERROR! ft_list_sort not sorting at all!");
        ok = 0;
    }

    free_list(two_unsorted_a);

    // random testing
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        t_list *random = create_random_int_list((rand() % 1000) + 2);
        ft_list_sort(&random, cmp_int);
        if (!isSorted(random)) {
            printf("ERROR! ft_list_sort is not sorting the list\n");
            ok = 0;
        }
        free_list(random);
    }

    if (ok) {
        printf("ft_list_sort OK!\n");
    }
}

int main() {
    srand(time(NULL));
    // just use main.c for ft_atoi_base
    test_ft_pushFront();
    test_ft_ListSize();
    test_ft_ListSort();
}
