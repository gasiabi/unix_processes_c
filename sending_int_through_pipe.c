#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    int fd[2];
    // fd[0] -> read
    // fd[1] -> write

    if (pipe(fd) == -1) {
        perror("The pipe was not successful.");
        return 1;
    }

    int id = fork();

    if (id < 0) {
        perror("The fork was not successful.");
        return 4;
    } else if (id == 0) { // The child process
        close(fd[0]);
        int x;
        printf("CHILD: Input a number: \n");
        scanf("%d", &x);

        if (write(fd[1], &x, sizeof(int)) == -1) {
            perror("The pipe was not successful.");
            return 2;        
        }

        close(fd[1]);

    } else if (id > 0) { // The main process
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1) {
            perror("The pipe was not successful.");
            return 3;
        }
        close(fd[0]);
        printf("MAIN: The value given by the child process: %d\n", y);

    }

    return 0;
}