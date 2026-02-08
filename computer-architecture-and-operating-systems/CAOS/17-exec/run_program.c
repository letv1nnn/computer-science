#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// specify the checksum of some binary ro tun only relevant programs.
const unsigned good_checksum = 0; 

unsigned compute_checksum(int fd) {
    unsigned sum = 0;
    char buf[32];
    ssize_t res;
    while ((res = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i != res; ++i)
            sum += buf[i];
    }
    return sum;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
    }
    unsigned checksum = compute_checksum(fd);
    if (checksum != good_checksum) {
        printf("Hach prevented!\n");
        exit(1);
    }
    
    // sleep(10); // during this sleep the given file can be changed!
    // execl(argv[1], argv[1], NULL);

    // using fexecve to pass file descriptor instead of a path, prevents such vulnerabilities
    // however, it's still can cause a disaster
    char *env[] = {NULL};
    char *args[] = {"My Program", NULL};
    fexecve(fd, args, env);
}
