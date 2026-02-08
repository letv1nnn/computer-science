#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    // passing the binary path, name of the program and arguments terminated by NULL 
    // int status = execl("/usr/bin/echo", "echo", "hello world", NULL);
    
    // passing the binary path(trying to find the path itself), name of the program and arguments terminated by NULL 
    // PATH env var that has a list of all directories with binary files.
    // int status = execlp("echo", "echo", getenv("$PATH"), NULL);
 
    // passing the binary path(trying to find the path itself) and an array from the heap
    // char *params[] = {"echo", "hello world", NULL};
    // int status = execvp("echo", params);

    // adding an array of environment variables that has a NULL as a last argument.
    // char *envs[] = {"PWD=password1234", NULL};
    // int status = execle("/usr/bin/printenv", "printenv", NULL, envs);

    // sh -c `cmd` runs some command
    // this approach has some disadvantages, specifically that we do not have an access to
    // the child process that shell creates later.
    // so we area creating to child processes this way, one by ourselves and the other shell creates itself.
    // const char *cmd = "sleep 3; ls -la";
    // int status = execl("/bin/sh", "sh", "-c", cmd, NULL);

    // envarinoment variables are responsible for colors
    const char *cmd = "echo -e \"${RED}hello${NC} world\"";
    setenv("RED", "\033[0;31m", 1);
    setenv("NC", "\033[0m", 1);
    int status = execl("/bin/bash", "sh", "-c", cmd, NULL);

    return 0;
}
