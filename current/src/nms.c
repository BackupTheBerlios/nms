#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "include/struct.h"
#include "include/structconf.h"
#include "include/file.h"
#include "include/msgerror.h"
#include "include/test.h"
#include "include/readconf.h"


int  
main(int argc, char *argv[]) {
	list *ptrList, *adrPtrList;
	conf confNMs;
	int n, verbose=0;
	
	/*
	 * :INFO: Gestion des arguments passé au programme
	 *  Vérification des arguments...
	 */
	if(argc > 1) {
		if(!strcmp(argv[1], "-h"))
			msgError(5);
		else if(!strcmp(argv[1], "-v"))
			verbose = 1;
		else
			msgError(5);
	}

	/*
	 * :INFO: Configuration générale de NMs
	 */
	confNMs = readConf( verbose );
	wLog( confNMs , "NMs" , " Program" , 1 ); // NMs started!
	
	/*
	 * :INFO: lit et parse de fichier des serveurs
	 */
	ptrList = readFile( confNMs , verbose );


	testConnect( ptrList , confNMs , verbose );
	
	
	/* 
	 * :INFO: Fin du programme
	 *  Cette partie ne sert pas à grand chose car le programme doit être
	 *  killé (kill -9 Numero_PID_NMs).
	 * :TODO: Voir si avec les signeaux on peut forcer le programmer à
	 *  passer par ici.
	 */
	adrPtrList = ptrList;
	do {
		free(adrPtrList->sProto);
		free(adrPtrList->sName);
		free(adrPtrList->sIp);
		for (n = 0; adrPtrList->sPort[n][0] != -9999; n++)
			free(adrPtrList->sPort[n]);
		free(adrPtrList->sPort);
		adrPtrList++;
	} while (strcmp(adrPtrList->sName,"NULL"));
	free(ptrList);
	if(verbose==1)
		printf("End of NMs\n");

	return 0;
}
