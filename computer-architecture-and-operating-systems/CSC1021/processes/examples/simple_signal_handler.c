#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sighandler(int sig) {
    printf("Received a signal: %d\n", sig);
}

int main(int argc, char **argv) {
    signal(SIGINT, sighandler);
    for(;;);
    return 0;
}
