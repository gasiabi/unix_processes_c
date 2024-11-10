#include <stdio.h>
#include <unistd.h>

int main() {
    int pd_t = fork();

    if (pd_t < 0) {
        perror("Fork failed.\n");
        return 1;    
    } else if (pd_t == 0) {
        printf("I am a child with ID %d, my parent ID is %d.\n", getpid(), getppid());
    } else {
        printf("I am a parent with ID %d.\n", getpid());
    }
    return 0;
}