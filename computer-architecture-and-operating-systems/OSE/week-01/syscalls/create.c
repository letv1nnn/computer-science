/*
The create system call is used to create a new empty file in C
and is provided as create() function. We can specify the permission
and the name of the file which we want to create using the create() function.
*/

#include <unistd.h> // create() definition
#include <fcntl.h> // for flags that are passed as arguments
#include <stdio.h>

int main(int argc, char **argv) {
    // File permissions: rw-r--r--
    int fd = creat("newfile.txt", 0644);

    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    printf("File 'newfile.txt' created successfully \n"
	       "File descriptor: %d\n", fd);

    close(fd);

    return 0;
}
