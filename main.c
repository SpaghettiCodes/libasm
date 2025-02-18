#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int ft_strlen(char *str);
extern char *ft_strcpy(char *dest, char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const char *buf, size_t count);
extern ssize_t ft_read(int fd, char *buf, size_t count);
extern char *ft_strdup(const char *s);

int main() {
    printf("%d\n", ft_strlen("123456789"));

    char buffer[100];
    char *test = "test test test, fuck you fuck you";
    char *out = ft_strcpy(buffer, test);
    printf("%s\n", out);
    printf("%s\n", test);
    printf("%s\n", buffer);

    char *one = "test";
    char *two = "test";
    char *three = "tes";
    char *four = "teste";
    printf("%d\n", strcmp(one, two));
    printf("%d\n", ft_strcmp(one, two));
    printf("%d\n", strcmp(one, three));
    printf("%d\n", ft_strcmp(one, three));
    printf("%d\n", strcmp(one, four));
    printf("%d\n", ft_strcmp(one, four));

    int res = ft_write(1, "test\n", 5);
    printf("Wrote %d characters\n", res);
    res = ft_write(-12, "test\n", 5);
    printf("%d\n", res);
    printf("%s\n", strerror(errno));

    int fd = open("testfile", O_CREAT);
    res = ft_read(fd, buffer, 4);
    printf("%d\n", res);
    buffer[res] = 0;
    printf("Read: %s\n", buffer);

    res = ft_read(-69, buffer, 4);
    printf("%d\n", res);
    printf("%s\n", strerror(errno));

    char *malloced = ft_strdup("0123456789abcdefghijk lmnopqrsTUVWXYZ");
    printf("%s\n", malloced);
    free(malloced);
}