/********
* Code d'erreur de udpcont()
*/
#define ERR_DNS 30	// Echec résolution DNS : ERR_DNS (30),
#define SRV_DOWN 31	// Serveur Down : SRV_DOWN (31),
#define SRV_UP 32	// Serveur UP : SRV_UP (32);

int 
udpcont(char * , int , int *);
