#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/libchar.h"
//#include "include/parse.h"
#include "include/struct.h"
#include "include/msgerror.h"

extern int parse( char* , list* );
#define LN_WITH_NOTE 2

/********
* Fonction strparse()
* recoit : 
*	une pointeur sur une chaine de caractere.
*	un motif.
* preCondition : 
*	les deux variables recu ne sont pas null.
* postCondition : 
*	retourne une pointeur sur la chaine hachee.
*	
*/
char * 
strparse( char *line,  char *motif) {
	int indice;
	char *dest; /* Pointeur sur la chaine hachee */
	char *ptr; /* Pointeur temporaire */

	ptr = strstr(line, motif); /* Recherche le motif dans la chaine */
	indice = ptr - line;
	dest = pmalloc(dest, indice+1); /* Alloue la memoire necessaire pour 
						recevoir la chaine hachee */
	strncpy(dest, line, indice);
	dest[indice] = '\0'; /* Ajoute le caractere de fin de chaine */
	strcpy(line, ptr + strlen(motif));  /* Retourne le reste de la chaine
							sans le hachage */
	return dest;
}

/********
* Fonction comptePort()
* recoit : 
*	un pointeur sur une chaine de caractere.
* preCondition : 
*	le pointeur ne doit pas etre NULL.
* postCondition : 
*	renvoit un entier
* description :
*	cette fonction compte le nombre de port dans une chaine de caractere
*	donnee.
*/
int 
comptePort(char *line) {
	char *ptr;
	int nbPorts=0; /* variable contenant le nombre de port 
						initialise a 0 */
	while(strstr(line, ",") != NULL) { /* chaque port est separe par 
						une virgule */
		ptr = strstr(line, ",");
		nbPorts++;
		ptr += 1;
		line = ptr;
	}
	return nbPorts+1;
}

/********
* Fonction triPorts()
* recoit : 
*	un pointeur sur une chaine de caractere.
* preCondition : 
*	le pointeur recu n'est pas NULL.
* postCondition : 
*	Retourne un entier contenant le premier numero de port de la chaine.
*/
int 
triPorts(char *listPort) {
	char *ptr;
	char tmp[12];
	ptr = strstr(listPort, ",");
	if(ptr != NULL) {
		ptr += 1;
		strncpy(tmp, listPort, ptr-listPort+1);
		tmp[ptr-listPort-1] = '\0';
		strcpy(listPort, ptr);
	}
	else
		strcpy(tmp, listPort);
	return atoi(tmp);
}

/********
* Fonction parsePort()
* recoit : 
*	un pointeur sur une chaine de caractere.
* preCondition : 
*	le pointeur recu ne doit pas etre NULL.
* postCondition : 
*	retourne un tableau d'entier contenant les numeros de ports.
*/
int ** 
parsePort(char *line) {
	int nbPorts, i;
	char *listPort;
	int **ptr;

	listPort = strparse(line, "}=>");  
	nbPorts  = comptePort(listPort);
	ptr = (int **) malloc(sizeof(int)*(nbPorts+1)*2);
	if(ptr == NULL) /* si ptr est null : probleme lors de l'allocation */
		msgError(2);
	for (i = 0; i < nbPorts+1; i++) {
		ptr[i] = (int*) malloc(sizeof(int));
		if(ptr[i] == NULL) /* si ptr est null : probleme lors de l'allocation */
			msgError(2);
	}
	for(i=0; i < nbPorts; i++) {
		ptr[i][0]=triPorts(listPort); /* appel la fonction triePorts pour 
						recevoir le prochain numero de
						port de la chaine listPort */
		ptr[i][1]=0;
	}
	ptr[nbPorts][0] = -9999; /* ceci est une sentinelle */
	return ptr;
}

/********
* Fonction parse()
* recoit : 
*	un pointeur sur une chaine de caractere (une instruction de config).
*	un pointeur sur la structure list (les parametres y sont stockes).
* preCondition : 
*	le pointeur sur la chaine de caractere ne doit pas etre NULL.
* postCondition : 
*	retourne 0 : tout c'est bien passe.
*/
int 
parse(char *line, list *ptrList) {
	strrpl(line, "", " ");
	if(line[0] == '#')
		return LN_WITH_NOTE;
	else  if(line[0] == '\0')
		return LN_WITH_NOTE;
	
	ptrList->sName   =  strparse(line, ":");
	ptrList->sProto  =  strparse(line, "://");
	ptrList->sIp     =  strparse(line, ":{");
	ptrList->sPort   =  parsePort(line);
	return 0;
}

