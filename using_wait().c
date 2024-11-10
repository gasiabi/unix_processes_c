#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int id = fork(); // We are creating a new child process.
    int n;
    
    if (id < 0) { // The fork fail
        perror("The fork was not successful.\n");
        return 1;
    } else if (id == 0) { // The child process
        n = 1;
    } else { // The main process
        wait(NULL); // The main process is forced to wait for the child process to end
        n = 6;
    }

    int i;
    for (i = n; i < n + 5; i++) {
        printf("%d ", i);    
        fflush(stdout);
    }
    return 0;
}