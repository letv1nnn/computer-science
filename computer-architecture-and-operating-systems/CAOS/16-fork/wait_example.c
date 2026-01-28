#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int child_function() {
    printf("child pid = %d\n", getpid());
    sleep(10);
    printf("hello world\n");
    _exit(5);
}

int main(int argc, char **argv) {
    pid_t pid = fork();
    if (pid == 0) {
        child_function();
    }

    int status;
    waitpid(pid, &status, 0);

    // Проверка того, завершился ли ребенок
    if (WIFEXITED(status)) {
        // Проверка статуса завершения
        printf("Child exit status: %d\n", WEXITSTATUS(status));
    }
    // Проверка был ли убит ребенок
    if (WIFSIGNALED(status)) {
        // Номер сигнала, при помощи которого убили
        printf("Child exit signal: %d\n", WTERMSIG(status));
    }

    return 0;
}
