#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

// mettre ensemble

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
    int mypipefd[2];
    int ret;
    char buf[30];

    ret = pipe(mypipefd);

    if (ret == -1){
        perror("pipe");
        exit(1);
    }


    else if (pid == 0){


        macheChild(i-1);
    }
    else {
        close(mypipefd[0]);
        write(mypipefd[1], "hello", 5);
    }



    for(i = 0; i < 5; i++) {
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0) {
        printf("Child (%d): %d\n", i + 1, getpid());
        close(mypipefd[1]);
        read(mypipefd[0], buf, 8);
        printf("Entering new loop \n");
    } else  {
        printf("Terminating child (%d) \n ", i);
        exit(0);
    }

}

}