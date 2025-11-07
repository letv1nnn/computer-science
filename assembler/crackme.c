#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int g_code;
int g_code2;

int check() {
    return (g_code == g_code2);
}

int main() {
    int code, res;
    printf("Enter the code: ");
    res = scanf("%d", &code);
    if (!res)
        abort();
    g_code = code;
    g_code2 = code + 1;
    if (!check()) {
        abort();
    }
    printf("Victory!\n");
}

