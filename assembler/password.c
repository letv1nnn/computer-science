#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char password[16];
    printf("Enter password: ");
    int res = scanf("%15s", password);
    if (!res)
        abort();
    if (strcmp(password, "secret1010") != 0) {
        printf("Permission denied.\n");
        return 0;
    }
    printf("Access granted!\n");
    return 0;
}
