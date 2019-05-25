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

Un processus zombie est un processus qui est terminé, mais le parent 
ne le sait pas encore. En effet, un processus zombie est toujours retrouvé
dans le table des processus. Pour le retiré de la table, il faudrait
que le processus parent appelle la fonction wait().  

Sources: https://www.developpez.net/forums/d1545567/c-cpp/c/fork-processus-zombie-processus-orphelin/
http://www.groupes.polymtl.ca/inf2610/documentation/notes/chap3.pdf

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

/*	int numProc;
	    printf("Enter number processes: ");
	    scanf("%d", &numProc);
	    creerEnfantEtLire(numProc);*/
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

	    pid_t pid;
		int ret;
		int nombre = 0;
	
		//int ret2;
		int mypipefd[2];
		//int mypipefd2[2];

		char writeMessage[BUFFER_SIZE] = "Processus %d commence\n";
		char termineMessage[BUFFER_SIZE] = "Processus %d termine\n";
		char readMessage[BUFFER_SIZE];

	    char buf2[10];
	    sprintf(buf2, "%d", (prcNum-1));
	    char **arg[]={"./a.out", buf2, NULL};

		ret = pipe(mypipefd);
		//ret2 = pipe(mypipefd2);

		if (ret == -1){
			perror("pipe has an error");
			exit(1);
		}

		pid = fork();
	
		if (pid < 0){
			
			printf("Fork failed");
	        exit(1);
		}
		if (pid ==0){

	

			
			close(mypipefd[WRITE_END]);
			
			dup2(mypipefd[0], mypipefd[1]);
		

			read(mypipefd[READ_END], readMessage, BUFFER_SIZE);
			printf(readMessage, prcNum);
			close(mypipefd[READ_END]);

			

			

		

			

			//close(mypipefd[WRITE_END]);
			
			//close(mypipefd[WRITE_END]);
			
		
			
			//sleep(10);
	
		
			
	        if (prcNum > 1 || prcNum < 1){
				
				
				int status = execvp(arg[0], arg);
				
				
				


	            if (status == -1) {
	            		printf("Execvp doesn't work");

	            }




	        }
	        else {
				exit(0);
				
			}
			
			
			
			

		}
		else {

			close(mypipefd[READ_END]);

			



			write(mypipefd[WRITE_END], writeMessage, strlen(writeMessage)+1);
			sleep(5);
			//int nombre = prcNum;

				printf("Processus %d termine\n", prcNum);
			
			

			


			close(mypipefd[WRITE_END]);
			
			

			//wait(NULL);
			//sleep(5);
			//write(mypipefd[WRITE_END], termineMessage, strlen(termineMessage)+1);

			//printf(close(mypipefd[WRITE_END]));

			//if (close(mypipefd[WRITE_END]) == 0) {
				//printf("Processus %d termine\n", prcNum);
			//}

			
			//sleep(5);
			//close(mypipefd[WRITE_END]);

			
		}






}
