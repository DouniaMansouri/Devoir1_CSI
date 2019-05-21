/*------------------------------------------------------------
Fichier: cpr.c

Nom:
Numero d'etudiant:

Description: Ce programme contient le code pour la creation
             d'un processus enfant et y attacher un tuyau.
	     L'enfant envoyera des messages par le tuyau
	     qui seront ensuite envoyes a la sortie standard.

Explication du processus zombie
(point 5 de "A completer" dans le devoir):

	(s.v.p. completez cette partie);

-------------------------------------------------------------*/
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 50
#define READ_END 0
#define WRITE_END 1
/* Prototype */
void creerEnfantEtLire(int );

/*-------------------------------------------------------------
Function: main
Arguments:
	int ac	- nombre d'arguments de la commande
	char **av - tableau de pointeurs aux arguments de commande
Description:
	Extrait le nombre de processus a creer de la ligne de
	commande. Si une erreur a lieu, le processus termine.
	Appel creerEnfantEtLire pour creer un enfant, et lire
	les donnees de l'enfant.
-------------------------------------------------------------*/

int main(int ac, char **av)
{
/*    int numeroProcessus;

    if(ac == 2)
    {
       if(sscanf(av[1],"%d",&numeroProcessus) == 1)
       {
           creerEnfantEtLire(numeroProcessus);
       }
       else fprintf(stderr,"Ne peut pas traduire argument\n");
    }
    else fprintf(stderr,"Arguments pas valide\n");*/

	int numProc;
	    printf("Enter number processes: ");
	    scanf("%d", &numProc);
	    creerEnfantEtLire(numProc);
   // return(0);
}


/*-------------------------------------------------------------
Function: creerEnfantEtLire
Arguments:
	int prcNum - le numero de processus
Description:
	Cree l'enfant, en y passant prcNum-1. Utilise prcNum
	comme identificateur de ce processus. Aussi, lit les
	messages du bout de lecture du tuyau et l'envoie a
	la sortie standard (df 1). Lorsqu'aucune donnee peut
	etre lue du tuyau, termine.
-------------------------------------------------------------*/

void creerEnfantEtLire(int prcNum)
{

		/*int pid;
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
	        write(mypipefd[1], "hello", 5);
	    }
	    else {
	        printf("Parent \n");
	        read(mypipefd[0], buf, 8);
	        printf("buf; %s\n", buf);
	    }*/

	pid_t pid;
	int tuyau;
	int pipes[2];
	int num = prcNum;
	int ancienNum=0;
	char writeMessage[BUFFER_SIZE] = "Processus %d commence\n";
	char readMessage[BUFFER_SIZE];



	tuyau = pipe(pipes);

	if (tuyau == -1){
		perror("pipe has an error");
		exit(1);
	}

	pid = fork();

	if (pid < 0){
		printf("Fork failed");
	}

	if (pid ==0){ //child

		// Faire le dup pour ecrire dans la sortie standard
		// Faire le excepVP pour faire un appel recursif de la fonction

		close(pipes[READ_END]);

		dup2(pipes[1], pipes[0]);

		char c = '0' + num;

		execvp(creerEnfantEtLire, c-1);

		write(pipes[READ_END], writeMessage, strlen(writeMessage)+1);

		printf(writeMessage, num);

		sleep(5);

		printf("Processus %d termine\n", num);




	}
	else { // parent

		// Lire du tuyau

		sleep(5);

		close(pipes[WRITE_END]);

		read(pipes[WRITE_END], readMessage, BUFFER_SIZE);

		printf(readMessage);

		printf("Processus 1 commence\n");

		sleep(5);

		printf("Processus 1 termine");

		close(pipes[WRITE_END]);



	}





}
