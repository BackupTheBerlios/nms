#ifndef msgerror
#define msgerror
/********
* Liste des codes d'erreur
*/
#define ERR_SYNT 1
#define ERR_MALL 2
#define ERR_OP_FILE 3
#define ERR_CL_FILE 4
#define ERR_ARG 5
#define ERR_SCK 6
#define ERR_WT_FL 7
#define ERR_PROTO 8


/********
* Fonction msgError()
* recoit : 
*	un entier correspondant au code d'erreur.
* preCondition : 
*	NULL.
* postCondition : 
*	Affiche un message d'erreur et quitte le programme.
*/
extern void msgError(int);
#endif
