#define SK_ERR_PROTO -1001
#define SK_ERR_SOCKET -1002
#define SK_ERR_CONCT -1002
#define SK_ERR_DNS -1003

/* 
 * :INFO: SETSOCK()
 * retourne un entier (un socket);
 * exemples d'utilisation :
 * socket = setsock( "192.168.1.10" , 80 , "tcp" );
 * socket = setsock( "www.tyneo.com" , 80 , "udp" );
 */
int
setsock( char * , int , char * );
