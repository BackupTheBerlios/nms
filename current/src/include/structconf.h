typedef struct
{
	char *fileData; 	/* Chemin vers fichier de données */
	char *fileLog; 		/* Chemin vers le fichier log */
	char *mailFrom; 	/* E-Mail depuis lequel NMs envoit ex: nms@tyneo.net */
	char *mailSubject; 	/* Sujet de l'email */
	char *mailMsg; 		/* Message de l'email */
	char *mailServeur; 	/* Adresse du serveur SMTP en IP ou domaine */
	int   nmsPause; 	/* Pause entre chaque boucle (ex: 60 pour 60 seconde) */
} conf;
