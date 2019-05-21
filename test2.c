#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

// pour tester la création des enfants

void makeChild(int);

int main ( int argc, char *argv[] )
{
    int numProc;
    printf("Enter number processes: ");
    scanf("%d", &numProc);

    makeChild(numProc);
    
}

void makeChild(int i){
    int pid;
    for(i = 0; i < 5; i++) {
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0){
        printf("Child (%d): %d\n", i + 1, getpid());
        printf("Entering new loop \n");
    } else  {
        printf("Terminating child (%d) \n ", i);
        exit(0);
    }
}

}