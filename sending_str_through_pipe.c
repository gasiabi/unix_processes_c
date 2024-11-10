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

        char str[200];
        printf("CHILD: Input a text: \n");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';

        int n = strlen(str) + 1; 
        if (write(fd[1], &n, sizeof(int)) == -1) {
            perror("The pipe was not successful.");
            return 2;  
        }

        if (write(fd[1], str, sizeof(char) * n) == -1) {
            perror("The pipe was not successful.");
            return 6;        
        }

        close(fd[1]);

    } else if (id > 0) { // The parent process
        close(fd[1]);
        char str[200];
        int n;

        if (read(fd[0], &n, sizeof(int)) == -1) {
            perror("The pipe was not successful.");
            return 3;
        }

        if (read(fd[0], str, sizeof(char) * n) == -1)  {
            perror("The pipe was not successful.");
            return 5;
        }

        close(fd[0]);
        wait(NULL);
        printf("\n");
        printf("MAIN: The value given by the child process: %s\n", str);

    }

    return 0;
}