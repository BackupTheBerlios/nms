#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "include/tcp.h"

/*
 * :INFO: sconnect()
 * Cette fonction se connect au serveur sName sur le port sPort.
 * Elle fait la résolution DNS de sName si nécessaire et renvoit
 * un code pour chaque étapes :
 *	- Echec résolution DNS : ERR_DNS (30),
 *	- Serveur Down : SRV_DOWN (31),
 *	- Serveur UP : SRV_UP (32);
 */
int sconnect(char *sName, int sPort, int *sSocket)
{
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt;
	unsigned long hostAddr;

	*sSocket = -1;
	
	bzero((void *)&serverSockAddr, sizeof(serverSockAddr)); // Pour BSD

	hostAddr = inet_addr(sName);

	/*
	 * :INFO: Résolution DNS si sName n'est pas une adresse IP.
	 */
	if((long)hostAddr != (long)-1)
		bcopy((void *)&hostAddr, (void *)&serverSockAddr.sin_addr, sizeof(hostAddr));
	else
	{
		if((serverHostEnt = gethostbyname(sName)) == NULL)
		{
			return ERR_DNS; // Impossible de faire la résolution DNS
		}
		else
			bcopy((void *)serverHostEnt->h_addr, (void *)&serverSockAddr.sin_addr, serverHostEnt->h_length);
	}
	
	serverSockAddr.sin_port = htons(sPort);
	serverSockAddr.sin_family = AF_INET;

	*sSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	/*
	* :INFO: Connexion au Serveur:Port
	*/
	if( connect( *sSocket , ( struct sockaddr * ) &serverSockAddr , sizeof( serverSockAddr ) ) != 0 )
	{
		return SRV_DOWN; // Serveur:Port indisponible
	}
	
	return SRV_UP; // Serveur:Port accecible
}


void sclose(int sSocket)
{
	shutdown(sSocket,2);
	close(sSocket);
}
