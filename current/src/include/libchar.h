/********
* Fonction strrpl()
* recoit : 
*	un pointeur sur une chaine de caracteres,
*	un pointeur sur une sous chaine de caracteres,
*	un pointeur sur une sous chaine de caracteres;
* preCondition : 
*	NULL.
* postCondition : 
*	NULL.
* include :
* description :
*	#include <string.h>
*	#include "include/libchar.h" 
*	Remplace tous les [string] dans [sentence] par [strnew];
* usage :
*	strrpl(sentence, strnew, string);
*/
extern void strrpl(char *, char *, char *);


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
extern char* pmalloc(char *, int);
extern char* prealloc(char *, int);
char* myitoa( int );
