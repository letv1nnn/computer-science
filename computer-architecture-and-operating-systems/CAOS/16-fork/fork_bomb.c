#include <sys/types.h>
#include <unistd.h>

// do not run
int main(int argc, char **argv) {
    while (1) {
        fork();
        sleep(2);
    }
}
