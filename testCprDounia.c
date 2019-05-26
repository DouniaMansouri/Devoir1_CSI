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
Un processus zombie est un processus enfant qui a terminé son exécution, mais qui existe encore dans la table de processus.
Afin de retirer l'enfant de la table, le processus parent doit recevoir un signal que l'enfant a fini son exécution, ensuite
appelle la fonction wait() afin de recevoir le exit status de l'enfant.
On observe ceci en exécutant ce programme: sur la ligne de commande, on remarque que le processus enfant et le processus parent 
existent ensemble pour un moment, même si le processus enfant a fini d'exécuter son programme. Lorsque le prochain processus est mis en marche,
le processus enfant disparaît, et le prochain processus prend son pid.
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
void creerEnfantEtLire2(int );

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
	int     fd[2], nbytes;
	pid_t   childpid;
	char    string[] = "Hello, world!\n";
	char    readbuffer[80];

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
	

	pid_t pid;
	int ret;
	int nombre = 0;
	int numeroProcessus;
	int     fd[2], nbytes;
	pid_t   childpid;
	//char    string[] = "Hello, world!\n";
	char    readbuffer[80];
	
	//int ret2;
	//int fd[2];
	//int mypipefd2[2];

	char writeMessage[BUFFER_SIZE] = "Processus %d commence\n";
	char termineMessage[BUFFER_SIZE] = "Processus %d termine\n";
	char readMessage[BUFFER_SIZE];

	char buf2[10];
	sprintf(buf2, "%d", (prcNum-1));
	//printf(buf2);
	char **arg[]={"./a.out", buf2, NULL};

	//printf("pcNum: %d", prcNum);
	if (prcNum < 1){
		printf("Numéro de processus non valide! \n");
		exit(1);
	}


	pipe(fd);
	
	if((childpid = fork()) == -1)
	{
			perror("fork");
			exit(1);
	}
	

	if(childpid == 0)
	{

		 close(fd[0]);
		 char buf3[100];
		 sprintf(buf3, writeMessage, (prcNum));
		 //printf(buf3);
		 write(fd[1], buf3, (strlen(buf3)+1));


			dup2(fd[0], fd[1]);
			/* Read in a string from the pipe */
			
			if (prcNum > 1){
				execvp("./a.out", arg);

			}
			
			/* Child process closes up input side of pipe */
			

			/* Send "string" through the output side of pipe */
			//terminate
			

	}
	else
	{
			/* Parent process closes up output side of pipe */
			sleep(5);
			close(fd[1]);

			
			
			nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
			printf( "%s \n", readbuffer);

			
	}

	

	nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
	if (nbytes <=0 && prcNum >= 1) {
		char buf4[100];
		sprintf(buf4, termineMessage, (prcNum));
		printf( "%s\n", buf4);
		exit(0);
	}


	
}




	
	
	
	
	




