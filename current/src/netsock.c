#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "include/netsock.h"


/* *****************************************************************************
 * :INFO: SETSOCK()
 * retourne un entier (un socket);
 * exemples d'utilisation :
 * socket = setsock( "192.168.1.10" , 80 , "tcp" );
 * socket = setsock( "www.tyneo.com" , 80 , "udp" );
 */
int
setsock( char *host , int service , char *protocol ) {

	struct protoent *ppe; /* pointeur sur la structure d'info du protocole */
	struct hostent *phe; /* pointeur sur la structure d'info du host */
	struct sockaddr_in server_in; /* structure d'info sur l'adresse du serveur */
	
	int sock; /* descripteur de socket */
	int sock_type; /* type associé au socket: STREAM ou DADAGRAM */	
	
	int value; /* valeur de retour d'une fonction */
	
	char bufreq[1];
	
	/* initialise la structure server_ini a 0 */
	bzero( (char *)&server_in , sizeof( server_in ) );
	
	/* mise en place de la famille d'adresse, ici INTERNET */
	server_in.sin_family = AF_INET;
	
	/* mise en place du numéro de port du service */
	server_in.sin_port = htons(service);
	
	/*
	 * :INFO: Résolution DNS si sName n'est pas une adresse IP.
	 !!!!!!! A REVOIR SI PRB DNS !!!!!!!
	 */
	if( (phe = gethostbyname( host ) ) )
		bcopy( phe ->h_addr , (char *)&server_in.sin_addr , phe ->h_length );
	else
		server_in.sin_addr.s_addr = inet_addr( host );
	
	/* mise en place de la structure d'information sur le protole */
	if( 0 == (ppe = getprotobyname( protocol ) ) ) {
		return SK_ERR_PROTO;
	}

	/* allocation du socket */
	if( 0 == strcmp( protocol , "udp" ) )
		sock_type = SOCK_DGRAM;
	else if( 0 == strcmp( protocol , "tcp" ) )
		sock_type = SOCK_STREAM;
	else
		return SK_ERR_PROTO;
	
	/* creation du socket avec le bon protocole */
	sock = socket( PF_INET , sock_type , ppe ->p_proto );
	if( sock < 0 )
		return SK_ERR_SOCKET;
	
	/* 
	 * :INFO: CAS TCP (STREAM SOCKET)
	 * On connecte le socket au serveur.
	 */
	if( SOCK_STREAM == sock_type ) {
		value = connect( sock , (struct sockaddr *) &server_in , sizeof( struct sockaddr ) );
		if( value < 0 )
			return SK_ERR_CONCT;
	}

	/* 
	 * :INFO: CAS UDP (DATAGRAM SOCKET)
	 * envoit un message pour communiquer l'adresse du client au serveur.
	 */
	 if( SOCK_DGRAM == sock_type ) {
		value = sendto( sock , bufreq , strlen( bufreq ) , 0 , (struct sockaddr *)&server_in , sizeof( server_in ) );
		if( value < 0 )
			return SK_ERR_CONCT;
	 }
	 
	 return sock;
}
