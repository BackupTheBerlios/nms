#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/msgerror.h"

/********
* description :
*	#include <string.h>
*	#include "include/libchar.h" 
*	Remplace tous les [string] dans [sentence] par [strnew];
* usage :
*	strrpl(sentence, strnew, string);
*/
void strrpl(char *sentence, char *strnew, char *string)
{
	char var2[255];
	char *ptr;

	while(strstr(sentence, string) != NULL)
	{
		ptr = strstr(sentence, string);
		strncpy(var2, sentence, ptr-sentence);
		var2[ptr-sentence] = '\0';
		strcat(var2, strnew);
		ptr += strlen(string);
		strcat(var2, ptr);
		strcpy(sentence, var2);
	}
}

char* myitoa( int num )
{
	char *ptr;
	
	ptr = ( char * ) malloc( sizeof( num ) );
	if( NULL == ptr )
		msgError(ERR_MALL);
	
	sprintf(ptr,"%d", num);
	
	return ptr;
}
/********
* Fonction pmalloc()
* recoit : 
*	un pointeur de type char,
*	un entier.
* preCondition : 
*	NULL.
* postCondition : 
*	Retourne un pointeur char avec une allocation de la taille demande.
*	Si erreur, appel la fonction msgError (code erreur 2)
*/
char* pmalloc(char *ptr, int taille)
{
	ptr = (char *) malloc(taille);
	if(ptr == NULL)
		msgError(ERR_MALL); /* Affiche l'erreur et quitte le programme */
	return ptr;
}

char* prealloc(char *ptr, int taille)
{
	ptr = (char *) realloc(ptr, taille);
	if(ptr == NULL)
		msgError(ERR_MALL); /* Affiche l'erreur et quitte le programme */
	return ptr;
}
