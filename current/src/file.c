#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "include/msgerror.h"
#include "include/struct.h"
#include "include/libchar.h"
//#include "include/parse.h"
#include "include/structconf.h"

extern int parse( char* , list* );
#define LN_WITH_NOTE 2

/*****************************************************************************/

FILE * 
openFile( char *fileSrc , char *mode ) {
	FILE *fpSrc;
	
	/* Ouverture du fichier .list en lecteur seulement */
	if ((fpSrc = fopen(fileSrc, mode)) == NULL)
		msgError(ERR_OP_FILE);
	
	return fpSrc;
}

void 
wLog( conf confNMs , char *string1 , char *string2 , int status ) {
	char *buffer, *sdate, *ptr;
	int taille;
	
	FILE *fpSrc;
	time_t date;
	
	/* On récuprère la date avec l'heure */
	time( &date );
	
	if( 1 == status ) {
		/*
		 * :INFO: Si status == UP 
		 */
		taille = strlen( ctime( &date ) ) + strlen( string1 ) + strlen( string2 ) + 8;

		buffer = (char *) malloc( taille + 1 );
		if( NULL == buffer ) {
			msgError(ERR_MALL);
		}
		strcpy( buffer , "[" );
		sdate = (char *) malloc( strlen( ctime( &date ) ) + 1 );
		if( NULL == sdate ) {
			msgError(ERR_MALL);
		}
		strcpy( sdate , ctime( &date ) );
		
		/* Supprime le caractère de fin de ligne que ctime() à ajouté */
		ptr = strchr(sdate, '\n');
		*ptr = '\0';
		
		strcat( buffer , sdate );
		strcat( buffer , "] " );
		strcat( buffer , string1 );
		strcat( buffer , ":" );
		strcat( buffer , string2 );
		strcat( buffer , " UP\n");
	}
	else {
		/*
		 * :INFO: Si status == DOWN
		 */
		taille = sizeof( ctime( &date ) ) + sizeof( string1 ) + sizeof( string2 ) + 10;
		buffer = (char *) malloc( taille + 1 );
		if( NULL == buffer ) {
			msgError(ERR_MALL);
		}
		strcpy( buffer , "[" );
		sdate = (char *) malloc( sizeof( ctime( &date ) ) + 1 );
		if( NULL == sdate ) {
			msgError(ERR_MALL);
		}
		strcpy( sdate , ctime( &date ) );
		
		/* Supprime le caractère de fin de ligne que ctime() à ajouté */
		ptr = strchr(sdate, '\n');
		*ptr = '\0';
		
		strcat( buffer , sdate );
		strcat( buffer , "] " );
		strcat( buffer , string1 );
		strcat( buffer , ":" );
		strcat( buffer , string2 );
		strcat( buffer , " DOWN\n");
	}

	/* 
	 * :INFO: Ouverture du fichier en mode append
	 * Si le fichier n'existe pas, il le crée,
	 * Sinon il écrit à la fin de ce fichier.
	 */
	fpSrc = openFile( confNMs.fileLog , "a" );

	if( EOF == fputs( buffer , fpSrc ) ) {
		msgError(ERR_WT_FL);
	}
	
	if(fclose(fpSrc))
		msgError(ERR_CL_FILE);
	
	/* 
	 * :ERROR: *** glibc detected *** free(): invalid next size (fast): 0x0804c198 ***
	 * Quand on libère la mémoire on obtient cette erreur
	 */
	//free(sdate);
	//free(buffer);
}


list * 
readFile( conf confNMs , int verbose ) {
	char *line;
	int n=0, listNbr=0;
	
	FILE *fpSrc;
	list *ptrList;
	list *adrPtrList;

	
	/* Ouverture du fichier */
	fpSrc = openFile( confNMs.fileData , "r" );
	
	ptrList = (list *) malloc(sizeof(list));
	adrPtrList = ptrList;

	
	line = pmalloc(line, 1);
	if( NULL == line ) {
		msgError(ERR_MALL);
	}

	while(!feof(fpSrc)) {
		/* 
		 * :INFO: lit le fichier caractere par caractere
		 */
		do {
			line = (char *)realloc(line, n+1);
			if( NULL == line ) {
				msgError(ERR_MALL);
			}
			
			line[n] = fgetc(fpSrc);
			n++;
		} while(line[n-1] != '\n' && line[n-1] != EOF);

		line[n-1] = '\0';

		/*
		 * :INFO: LN_WITH_NOTE = ligne commentée ou vide
		 */
		if(parse(line, adrPtrList) != LN_WITH_NOTE) {
			listNbr++;
			ptrList = (list *) realloc(ptrList, sizeof(list)*(listNbr+1));
			if(ptrList == NULL)
				msgError(2);
			adrPtrList = ptrList;
			for(n=0; n<listNbr;n++)
				adrPtrList++;
		}

		n = 0;
	}
	
	/* On ajoute une sentinel a list */
	adrPtrList->sName = (char *) malloc(5);
	if(adrPtrList->sName == NULL)
		msgError(2);
	strcpy(adrPtrList->sName,"NULL");
	
	free(line);
	
	if(fclose(fpSrc))
		msgError(ERR_CL_FILE);
	
	return ptrList;
}
