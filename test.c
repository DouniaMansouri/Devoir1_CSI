#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>


// pour tester les tuyaux

int main (int argc, char *argv[]){

    int pid;
    int mypipefd[2];
    int ret;
    char buf[10];

    ret = pipe(mypipefd);

    if (ret == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == 0){
        printf("Child \n");
        close(mypipefd[1]);
        read(mypipefd[0], buf, 8);
        printf("buf; %s\n", buf);
    }
    else {
        close(mypipefd[0]);
        printf("Parent \n");
        write(mypipefd[1], "hello", 5);
    }


}