#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "include/tcp.h"
#include "include/sendmail.h"

void 
sendMsg( int *sSocket , char *buffer ) {
	int value;

	value = send( *sSocket , buffer , strlen( buffer ) , 0 );

	if( -1 == value ) {
		printf( "SendMsg: erreur!\n" );
	}
}

void 
recvMsg( int *sSocket , char *buffer , char *code ) {
	int value;

	value = recv( *sSocket , buffer , 255 , 0 );

	if( -1 == value ) {
		printf( "RecvMsg: erreur!\n" );
	}
	
	if( NULL == strstr( buffer , code ) ) {
		printf( "RecvMsg: erreur!!\n Invalide code : %s\n" , code );
	}
}

int 
sendMail(char *to, char *from, char *subject, char *message, int verbose) {
	int sSocket; /* descripteur de fichier (socket) */
	char buffer[256];
	
	sconnect("192.168.1.10", 25, &sSocket);

	if( 1 == verbose ) {
		printf("   - HELLO Mail Server!\n");
	}
	recvMsg(&sSocket, buffer, SM_HELLO);

	strcpy(buffer,"HELO tyneo.com\n");
	sendMsg(&sSocket, buffer);
	recvMsg(&sSocket, buffer, RECV_GOOD);

	sprintf(buffer,"MAIL FROM: <%s>\n", from);
	sendMsg(&sSocket, buffer);       
	recvMsg(&sSocket, buffer, RECV_GOOD);

	sprintf(buffer,"RCPT TO: <%s>\n", to);
	sendMsg(&sSocket, buffer);
	recvMsg(&sSocket, buffer, RECV_GOOD);

	strcpy(buffer,"DATA\n");  
	sendMsg(&sSocket, buffer);
	recvMsg(&sSocket, buffer, ACT_START);
 
	if( 1 == verbose ) {
		printf("   - Send mail...\n");
	}
	sprintf(buffer,"FROM: %s\r\nTO: %s\r\nsubject: %s\r\n%s\r\n.\r\n", from, to, subject, message);
	sendMsg(&sSocket, buffer);
	recvMsg(&sSocket, buffer, RECV_GOOD);

	if( 1 == verbose ) {
		printf("   - BYE Mail Server!\n");
	}
	strcpy(buffer,"QUIT\n");
	sendMsg(&sSocket, buffer);
	recvMsg(&sSocket, buffer, SM_QUIT);

	sclose(sSocket);

	return 0;
}

