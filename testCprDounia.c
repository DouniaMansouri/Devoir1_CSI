/*------------------------------------------------------------
Fichier: cpr.c

Nom: Dounia Mansouri, Sacha Chow-Cloutier
Numero d'etudiant:      ,300017286

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
	if (prcNum < 1){
		printf("Nombre de processus invalide! \n");
		exit(1);
	}
	
	pid_t pid;
	int ret;
	int mypipefd[2];
	char writeMessage[BUFFER_SIZE] = "Processus %d commence\n";
	char termineMessage[BUFFER_SIZE] = "Processus %d termine";
	char readMessage[BUFFER_SIZE];

	char buf2[10];
	sprintf(buf2, "%d", (prcNum-1));
	char **arg[]={"./a.out", buf2, NULL};

	ret = pipe(mypipefd);

	if (ret == -1){
		perror("pipe has an error");
		exit(1);
	}

	pid = fork(); //crée le processus enfant
		
	if (pid < 0){
		printf("Fork failed");
	    exit(1);
	}
	if (pid ==0){
		close(mypipefd[WRITE_END]);
		dup2(mypipefd[0], mypipefd[1]);
		read(mypipefd[WRITE_END], readMessage, BUFFER_SIZE);
		printf(readMessage, prcNum);
		sleep(5);
	    if (prcNum > 1){ //si prcNum >1, on continue de créer des enfants
			int status = execvp(arg[0], arg);
	        if (status == -1) {
	        	printf("Execvp doesn't work");
	        }
	    }
	    else {
			exit(0);	
		}
		sleep(10);
		}

		else { //processus parent
			close(mypipefd[READ_END]);
			write(mypipefd[WRITE_END], writeMessage, strlen(writeMessage)+1);
			sleep(5);
			wait(NULL);
			printf("Processus %d termine\n", prcNum);
			close(mypipefd[WRITE_END]);
		}
}
