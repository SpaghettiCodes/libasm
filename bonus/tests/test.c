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
void        ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));
void        ft_list_sort(t_list **begin_list, int (*cmp)());

#define BRUTE_FORCE_TESTS 1000

// whaat the heck, why string.h no strdup
char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) return NULL;
    strcpy(dst, src);
    return dst;
}

int list_size(t_list *data) {
    int i = 0;
    while (data) {
        ++i;
        data = data->next;
    }
    return i;
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

int generateLessThanFiveHundred() {
    return rand() % 500;
}

int generateMoreThanFiveHundred() {
    return rand() % 10000 + 501;
}

t_list *create_random_lessthan_list(int lessThanCount, int moreThanCount) {
    int i = 0;
    int total = lessThanCount + moreThanCount;
    t_list *ret = NULL;
    t_list *prev = NULL;

    while (i < total) {
        int value;
        if (lessThanCount == 0) {
            value = generateMoreThanFiveHundred();
            moreThanCount -= 1;
        } else if (moreThanCount == 0) {
            value = generateLessThanFiveHundred();
            lessThanCount -= 1;
        } else {
            if (rand() % 2) {
                value = generateLessThanFiveHundred();
                lessThanCount -= 1;
            } else {
                value = generateMoreThanFiveHundred();
                moreThanCount -= 1;
            }
        }

        t_list *next = ft_list_create(create_intNode(value));
        if (prev) {
            prev->next = next;
        }
        if (!ret) {
            ret = next;
        }
        prev = next;
        i++;
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

int functionThatAlwaysReturnTrue(void *one, void *data_ref) {
    (void) one;
    (void) data_ref;
    return 0;
}

int functionThatAlwaysReturnFalse(void *one, void *data_ref) {
    (void) one;
    (void) data_ref;
    return 1;
}

int intIsEqual(void *one, void *data_ref) {
    return *(int *) one != *(int *) data_ref;
}

// returns 0 if its one is more than data_ref
int intLessThan(void *one, void *data_ref) {
    return *(int *) one < *(int *) data_ref;
}

void test_ft_RemoveIf() {
    int ok = 1;

    // null test
    ft_list_remove_if(NULL, NULL, functionThatAlwaysReturnTrue, free_node);
    
    // empty test
    t_list *empty = NULL;
    ft_list_remove_if(&empty, NULL, functionThatAlwaysReturnTrue, free_node);

    // given a random list of stuff, remove everything test
    t_list *random = create_random_int_list((rand() % 1000) + 1);
    ft_list_remove_if(&random, NULL, functionThatAlwaysReturnTrue, free_node);
    // shouldnt have any leaks
    if (random != NULL) {
        printf("ERROR! ft_list_remove_if not removing properly\n");
        ok = 0;
        // bruh
        free_list(random);
    }

    // given a random list of stuff, do not remove anything
    int size = (rand() % 1000) + 1;
    random = create_random_int_list(size);
    ft_list_remove_if(&random, NULL, functionThatAlwaysReturnFalse, free_node);
    if (random == NULL || list_size(random) != size) {
        printf("ERROR! ft_list_remove_if removed something\n");
        ok = 0;
    }
    free_list(random);

    // given a list, remove the first element only
    int one = 1;
    t_list *firstElem = ft_list_create(create_intNode(1));
    t_list *firstElem_b = ft_list_create(create_intNode(2));
    firstElem->next = firstElem_b;
    ft_list_remove_if(&firstElem, &one, intIsEqual, free_node);
    if (list_size(firstElem) == 2) {
        printf("ERROR! ft_list_remove_if didnt remove anything\n");
        ok = 0;
    } else {
        if (firstElem == NULL || *(int *)firstElem->data != 2) {
            printf("ERROR! ft_list_remove_if removed unintended target\n");
            ok = 0;
        }
    }
    free_list(firstElem);

    // given a list, remove the last element only
    t_list *lastElem = ft_list_create(create_intNode(2));
    t_list *lastElem_b = ft_list_create(create_intNode(1));
    lastElem->next = lastElem_b;
    ft_list_remove_if(&lastElem, &one, intIsEqual, free_node);
    if (list_size(lastElem) == 2) {
        printf("ERROR! ft_list_remove_if didnt remove anything\n");
        ok = 0;
    } else {
        if (lastElem == NULL || *(int *)lastElem->data != 2) {
            printf("ERROR! ft_list_remove_if removed unintended target\n");
            ok = 0;
        }
    }
    free_list(lastElem);

    // given a list, remove the middle element
    t_list *middleElem = ft_list_create(create_intNode(2));
    t_list *middleElem_b = ft_list_create(create_intNode(1));
    t_list *middleElem_c = ft_list_create(create_intNode(3));
    middleElem->next = middleElem_b;
    middleElem_b->next = middleElem_c;
    ft_list_remove_if(&middleElem, &one, intIsEqual, free_node);
    if (list_size(middleElem) == 3) {
        printf("ERROR! ft_list_remove_if didnt remove anything\n");
        ok = 0;
    } else {
        if (
            middleElem == NULL || 
            list_size(middleElem) != 2 ||
            *(int *)middleElem->data != 2 ||
            *(int *)middleElem->next->data != 3
        ) {
            printf("ERROR! ft_list_remove_if removed unintended target\n");
            ok = 0;
        }
    }
    free_list(middleElem);

    if (ok) {
        printf("ft_remove_if OK!\n");
    }
}

int main() {
    srand(time(NULL));
    // just use main.c for ft_atoi_base
    test_ft_pushFront();
    test_ft_ListSize();
    test_ft_RemoveIf();
    test_ft_ListSort();
}
