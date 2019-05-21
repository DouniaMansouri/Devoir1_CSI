#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

// mettre ensemble

void creerEnfantEtLire(int);

int main(int ac, char **av)
{
    int numeroProcessus;

    if(ac == 2)
    {
       if(sscanf(av[1],"%d",&numeroProcessus) == 1)
       {
           creerEnfantEtLire(numeroProcessus);
       }
       else fprintf(stderr,"Ne peut pas traduire argument\n");
    }
    else fprintf(stderr,"Arguments pas valide\n");
    return(0);
    
}

void creerEnfantEtLire(int prcNum){
    int pid;
    int mypipefd[2];
    int ret;
    char buf2[10];
    char buf[30];
    sprintf(buf2, "%d", (prcNum-1));
    char* arg[]={"./a.out", buf2, NULL};

    ret = pipe(mypipefd);

    if (ret == -1){
        perror("pipe");
        exit(1);
    }
   
    pid = fork();

    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0){
        close(mypipefd[1]);
        printf("Processus (%d) commence \n", prcNum);
        sleep(5);
        printf("Processus (%d) terminé \n", prcNum);
        dup2(0, mypipefd[1]);
        sprintf(buf2, "%d", (prcNum-1));
        printf("%s", buf2);
        execvp(arg[0], arg);
    } else  { 
        close(mypipefd[0]);
        read(mypipefd[0], buf, 30);
        printf("Heres the buf: (%s) \n", buf);
    }
}



