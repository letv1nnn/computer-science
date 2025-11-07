// MIPT (2023-2024), seminar 5.2
// Problem RXM - approximate search
// Reverse all substrings for a given regular expression
// POSIX
// a.c: abc, aac, acc
// [azc]: a, c, z
// [a-z]: a, b, ..., z
// [^a-c]: d, e, f, ...
// ^abc, bcd$: abcd
// ab*c: abc, abbc, abb...c
// a\{3\}: aaa
// a\{3,\}: aaa, aaaa, aaaaa, ...

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

typedef struct Strings { char **strs; int len; } Strings;

bool posix_match(const char *, const char *);
void reverseStr(char *, int);
Strings splitWhitespace(const char *, int);
void strNcpy(const char *, char *, int, int);

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: <program> <size-of-reg-expr> <reg-expr> <size-of-string> <\"string\">\n");
        return 1;
    }
    int rxSize = atoi(argv[1]), strSize = atoi(argv[3]);
    const char *expr = argv[2], *str = argv[4];

    Strings s = splitWhitespace(str, strSize);

    for (int i = 0; i < s.len; ++i) {
        if (posix_match(expr, s.strs[i])) {
            reverseStr(s.strs[i], strlen(s.strs[i]));
        }
    }

    for (int i = 0; i < s.len; ++i) {
        printf("%s ", s.strs[i]);
        free(s.strs[i]);
    }
    printf("\n");
    free(s.strs);
    return 0;
}

bool posix_match(const char *expr, const char *str) {
    regex_t regex;
    if (regcomp(&regex, expr, REG_EXTENDED | REG_NOSUB) != 0)
        return false;
    int result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

Strings splitWhitespace(const char *str, int n) {
    int spaces = 0;
    for (int i = 0; i < n; ++i)
        if (str[i] == ' ') spaces++;

    int total = spaces + 1;
    char **strings = malloc(sizeof(char *) * total);
    if (!strings) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int from = 0, idx = 0;
    for (int to = 0; to <= n; ++to) {
        if (str[to] == ' ' || to == n) {
            int len = to - from;
            strings[idx] = malloc(len + 1);
            strNcpy(str, strings[idx], from, to);
            strings[idx++][len] = '\0';
            from = to + 1;
        }
    }

    Strings s = {strings, total};
    return s;
}

void reverseStr(char *str, int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        char tmp = str[l]; str[l] = str[r]; str[r] = tmp;
        l++; r--;
    }
}

void strNcpy(const char *origin, char *str, int from, int to) {
    int j = 0;
    for (int i = from; i < to; i++)
        str[j++] = origin[i];
}

