#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//#include "include/file.h"
#include "include/struct.h"
#include "include/structconf.h"
#include "include/tcp.h"
#include "include/netsock.h"
#include "include/sendmail.h"
#include "include/msgerror.h"
#include "include/libchar.h"

extern void wLog( conf  , char * , char * , int );


char * 
addsymb( char *strSource ,  char *status , char *server , char *port) {
	char *buffer;
	
	buffer = (char *) malloc( sizeof( char ) * strlen( strSource ) );
	if( NULL == buffer )
		msgError( ERR_MALL );
	strcpy( buffer , strSource );
	strrpl(buffer, status, "%status");
	strrpl(buffer, server, "%server");
	strrpl(buffer, port, "%port");
	
	return buffer;
}
void bla ( list *adrPtrList , conf confNMs , int verbose, int value, int n) {
	char *buff1, *buff2;
	
	if(value > 0) /* serveur UP */
	{
		if( 1 == adrPtrList ->sPort[n][1] ) {
			if( 1 == verbose)
				printf( " Change status to up!\n" );
			adrPtrList ->sPort[n][1] = 0;
			
			buff1 = addsymb( confNMs.mailSubject, "up", adrPtrList ->sIp, myitoa( adrPtrList->sPort[n][0] ) );
			buff2 = addsymb( confNMs.mailMsg, "up", adrPtrList ->sIp, myitoa( adrPtrList->sPort[n][0] ) );
			sendMail("skauffmann@tyneo.net", confNMs.mailFrom, buff1, buff2, verbose);
			/* Libération de la mémoire */
			free(buff1); free(buff2);
			
			//wLog( confNMs , "serveur UP", WL_INFO );
		}
		else
			if( 1 == verbose)
				printf( " Status is always alive.\n" );
		/* ferme le socket */
		close(value);
	}
	
	
	if( 0 == adrPtrList ->sPort[n][1] ) {
		if( 1 == verbose ) {
			printf( " Change status to down!\n" );
		}
		adrPtrList ->sPort[n][1] = 1;
		buff1 = addsymb( confNMs.mailSubject, "down", adrPtrList ->sIp, myitoa( adrPtrList->sPort[n][0] ) );
		buff2 = addsymb( confNMs.mailMsg, "down", adrPtrList ->sIp, myitoa( adrPtrList->sPort[n][0] ) );
		sendMail("skauffmann@tyneo.net", confNMs.mailFrom, buff1, buff2, verbose);
		/* Libération de la mémoire */
		free(buff1); free(buff2);
		
		//wLog( confNMs , "serveur DOWN", WL_WARNING );
	}
	else
	if( 1 == verbose )
		printf(" Status is always down!\n");
}

void 
testConnect( list *ptrList , conf confNMs , int verbose ) {
	int value, n, sSocket;
	list *adrPtrList;
	
	while( 1 ) {
		adrPtrList = ptrList;
		do {
			if( 1 == verbose) {
				printf( "\n#################################\n" );
				printf( "# Server name : %s\n" , adrPtrList ->sName );
				printf( "# Protocol name : %s\n" , adrPtrList ->sProto );
				printf( "# IP address : %s \n" , adrPtrList ->sIp );
				for( n = 0 ; adrPtrList->sPort[n][0] != -9999 ; n++ )
					printf( "# Port number %d : %d\n" , n , adrPtrList->sPort[n][0] );
			}
			
			for( n = 0 ; adrPtrList->sPort[n][0] != -9999 ; n++ ) {
				value = setsock( adrPtrList ->sName , adrPtrList->sPort[n][0] , adrPtrList ->sProto );
				bla(adrPtrList , confNMs, verbose, value, n);
			}
			adrPtrList++;
		} while ( strcmp( adrPtrList->sName , "NULL" ) ); 
		// Tant que la sentinelle n'est pas atteinte on boucle.

		/*
		 * :INFO: Pause 
		 *  Pause dans la boucle afin de ne pas créer de DoS.
		 */
		sleep(60);
	}
}
