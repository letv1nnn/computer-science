#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

int main(int argc, char **argv) {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("\033[1;33mEnter command\033[0m$ ");
        int serr = scanf("%1023s", cmd);
        if (serr != 1) {
            perror("scanf");
        }
        
        pid_t pid = fork();
        if (pid == 0) {
            execlp(cmd, cmd, NULL);
            perror("exec");
            _exit(1);
        }

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                printf("Non zero exit status\n");
            }
        }
    }
}
