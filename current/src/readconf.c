#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "include/structconf.h"
//#include "include/file.h"
#include "include/msgerror.h"


conf 
readConf( int verbose ) {
	conf confNMs;
	
	char fd[] = "./server.list";
	char fl[] = "./nms.log";
	char mf[] = "nms@tyneo.net";
	char ms[] = "NMs: change status to %status";
	char mm[] = "ALERT : your %server:%port change status to %status";
	char msrv[] = "mail.tyneo.com";


	confNMs.fileLog = (char *) malloc( 1 + strlen( fl ) );
	if( NULL == confNMs.fileLog )
		msgError( ERR_MALL );
	strcpy( confNMs.fileLog , fl );
	
	confNMs.fileData = (char *) malloc( 1 + strlen( fd ) );
	if( NULL == confNMs.fileData )
		msgError( ERR_MALL );
	strcpy( confNMs.fileData , fd );
	
	confNMs.mailFrom = (char *) malloc( 1 + strlen( mf ) );
	if( NULL == confNMs.mailFrom )
		msgError( ERR_MALL );
	strcpy( confNMs.mailFrom , mf );
	
	confNMs.mailSubject = (char *) malloc( 1 + strlen( ms ) );
	if( NULL == confNMs.mailSubject )
		msgError( ERR_MALL );
	strcpy( confNMs.mailSubject , ms );
	
	confNMs.mailMsg = (char *) malloc( 1 + strlen( mm ) );
	if( NULL == confNMs.mailMsg )
		msgError( ERR_MALL );
	strcpy( confNMs.mailMsg , mm );
	
	confNMs.mailServeur = (char *) malloc( 1 + strlen( msrv ) );
	if( NULL == confNMs.mailServeur )
		msgError( ERR_MALL );
	strcpy( confNMs.mailServeur , msrv );
	
	return confNMs;
}
