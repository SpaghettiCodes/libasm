// test cases for asm, core
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

extern int ft_strlen(char *str);
extern char *ft_strcpy(char *dest, char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const char *buf, size_t count);
extern ssize_t ft_read(int fd, char *buf, size_t count);
extern char *ft_strdup(const char *s);

#define BRUTE_FORCE_TESTS 1000

char random_char(int index) {
    return index + 32;
}

char *randomString(int length) {
    char *ret = malloc(length + 1);
    for (int i = 0; i < length; ++i) {
        int index = rand() % 95;
        ret[i] = random_char(index);
    }
    ret[length] = 0;
    return ret;
}

void test_StrLen() {
    int ok = 1;
    char *tests[] = {
        "",
        "a",
        "ab",
        "abc",
    };

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(char *); ++i) {
        int gotten = ft_strlen(tests[i]);
        int expected = strlen(tests[i]);

        if (gotten != expected) {
            printf("ERROR! ft_strlen: Gotten %d when Expecting %d\n", gotten, expected);
            ok = 0;
        }
    }

    // randomly generate idk, BRUTE_FORCE_TESTS strings and test
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        char *str = randomString(rand() % 10000);
        int gotten = ft_strlen(str);
        int expected = strlen(str);

        if (gotten != expected) {
            printf("ERROR! ft_strlen: Gotten %d when Expecting %d\n", gotten, expected);
            ok = 0;
        }
        free(str);
    }

    if (ok)
        printf("ft_strlen OK!\n");
}

int equalStr(char *one, char *two) {
    while (*one == *two) {
        if (!(*one)) {
            return 1;
        }
        ++one;
        ++two;
    }
    return 0;
}

void test_StrCpy() {
    // if any two parameter is null, strcpy seg faults.
    int ok = 1;
    char *tests[] = {
        ""
    };
    char buffer[10000];

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(char *); ++i) {
        ft_strcpy(buffer, tests[i]);

        if (!equalStr(buffer, tests[i])) {
            printf("ERROR! ft_strcpy: Saved %s when Expecting %s\n", buffer, tests[i]);
            ok = 0;
        }
        // clear buffer
        memset(buffer, 0, 10000);
    }

    // randomly generate idk, BRUTE_FORCE_TESTS strings and test
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        char *str = randomString(rand() % 10000);

        char *retVal = ft_strcpy(buffer, str);
        if (retVal != buffer) {
            printf("ERROR! ft_strcpy should return dest addr!\n");
            ok = 0;
            break;
        }

        if (!equalStr(buffer, str)) {
            printf("ERROR! ft_strcpy: Saved %s when Expecting %s\n", buffer, str);
            ok = 0;
        }
        // clear buffer
        memset(buffer, 0, 10000);
        free(str);
    }

    if (ok)
        printf("ft_strcpy OK!\n");
}

typedef struct cmpData
{
    char *one;
    char *two;
} t_cmpData;

t_cmpData *newCmpData(char *one, char *two) {
    t_cmpData *new = malloc(sizeof(t_cmpData));
    new->one = one;
    new->two = two;
    return new;
}

void test_StrCmp() {
    int ok = 1;
    t_cmpData *tests[] = {
        // normal testing
        newCmpData("", ""),
        newCmpData("", "\x01"),
        newCmpData("\x01", ""),
        newCmpData("\x01", "\x01"),
        newCmpData("\x01", "\x02"),
        newCmpData("\x02", "\x01"),
        newCmpData("\x01", "\x01\x01"),
        newCmpData("\x01\x01", "\x01"),
        newCmpData("", "\x05\x01"),
        newCmpData("\x05\x01", ""),

        // 255 schenanigans
        // this checks if you extend your 0s properly
        newCmpData("\xff", ""),
        newCmpData("", "\xff"),
        newCmpData("\xff", "\xff"),
        newCmpData("\xff", "\xfe"),
        newCmpData("\xfe", "\xff")
    };

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(char *); ++i) {
        int gotten = ft_strcmp(tests[i]->one, tests[i]->two);
        int expected = strcmp(tests[i]->one, tests[i]->two);

        if (gotten != expected) {
            printf(
                "ERROR! ft_strcmp: Gotten %d when Expecting %d when comparing %s and %s\n", 
                gotten, 
                expected, 
                tests[i]->one, 
                tests[i]->two
            );
            ok = 0;
        }
    }

    // free data
    for (unsigned int i = 0; i < sizeof(tests) / sizeof(char *); ++i) {
        free(tests[i]);
    }

    // randomly generate idk, BRUTE_FORCE_TESTS strings and test
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        char *one = randomString(rand() % 100);
        char *two = randomString(rand() % 100);
        int gotten = ft_strcmp(one, two);
        int expected = strcmp(one, two);

        if (gotten != expected) {
            printf(
                "ERROR! ft_strcmp: Gotten %d when Expecting %d when comparing %s and %s\n", 
                gotten, 
                expected, 
                one, 
                two
            );
            ok = 0;
        }
        free(one);
        free(two);
    }

    if (ok)
        printf("ft_strcmp OK!\n");
}

void test_StrDup() {

    // if any two parameter is null, strcpy seg faults.
    int ok = 1;
    char *tests[] = {
        "",
        "a",
        "abc",
        "abcd"
    };

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(char *); ++i) {
        char *out = ft_strdup(tests[i]);

        if (!equalStr(out, tests[i])) {
            printf("ERROR! ft_strdup: Duplicated %s when Expecting %s\n", out, tests[i]);
            ok = 0;
        }
        free(out);
    }

    // randomly generate idk, BRUTE_FORCE_TESTS strings and test
    for (unsigned int i = 0; i < BRUTE_FORCE_TESTS; ++i) {
        char *str = randomString(rand() % 10000);
        char *retVal = ft_strdup(str);

        if (!equalStr(retVal, str)) {
            printf("ERROR! ft_strdup: Saved %s when Expecting %s\n", retVal, str);
            ok = 0;
        }
        free(retVal);
        free(str);
    }

    if (ok)
        printf("ft_strdup OK!\n");
}

int main() {
    srand(time(NULL));
    test_StrLen();
    test_StrCpy();
    test_StrCmp();
    // pray write works
    // pray read works
    test_StrDup();
}