/********
* Code d'erreur de sconnect(char *, int)
*/
#define ERR_DNS 30	// Echec résolution DNS : ERR_DNS (30),
#define SRV_DOWN 31	// Serveur Down : SRV_DOWN (31),
#define SRV_UP 32	// Serveur UP : SRV_UP (32);

/********
* Fonction cTestTcp()
* recoit : 
*	un pointeur sur une chaine de caractere,
*	un tableau d'entier a deux dimmensions.
*	un entier.
* preCondition : 
*	NULL.
* postCondition : 
*	NULL.
*/
extern int sconnect( char *, int , int *);
extern void sclose( int );
