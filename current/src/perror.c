#include <stdio.h>
#include <stdlib.h>

/*
 * :INFO: Gestion des erreurs
 *  Cette fonction gère les erreurs et termine le programme.
 */
int 
msgError(int codeError) {
	switch(codeError) {
		case 1:
			printf("error: syntaxt configuration file error.\n");
			break;
		case 2:
			printf("error: unable to malloc().\n");
			break;
		case 3:
			printf("error: unable to open file.\n");
			break;
		case 4:
			printf("error: unable to open file.\n");
			break;
		case 5:
			printf("NMs help :\n");
			printf("usage: nms [OPTIONAL OPTION]\n");
			printf("-v\tverbose mode\n");
			printf("-h\tthis help\n");
			break;
		case 7:
			printf("error: Impossible d'ecrire dans le fichier de destination.\n");
			break;
		default:
			printf("error: invalid error code. Please report bug.\n");
	}
	printf("Program exited!\n");
	exit(-1);
}
