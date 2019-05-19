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
    read(0,buf,4);
    printf(buf);
    makeChild(numProc);
    
}

void makeChild(int prcNum){
    int pid;
    int mypipefd[2];
    int ret;
    char buf[30];
    ret = pipe(mypipefd);

    if (ret == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if(pid < 0) {
        printf("Error");
        exit(1);
    }
    else if (pid == 0){
        printf("Child process \n");

        close(mypipefd[1]);
        read(mypipefd[0], buf, 4);

        printf("buf; %s\n", buf);
    }
    else {
        printf("Processus (%d) commence \n", prcNum);

        close(mypipefd[0]);
        write(mypipefd[1], "hello", 4);
        sleep(5);

        printf("Processus (%d) terminé \n", prcNum);
        sleep(10);
    }
}



