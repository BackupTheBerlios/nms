/*
***************************************************************
* STRUCTURE list; 
* desc: structure comportant 
* un pointeur sur le nom du serveur,
* un pointeur sur l'adresse mail,
* un pointeur sur l'ip,
* un pointeur sur le protocol,
* unn pointeur sur le port.
*/  
typedef struct
{
  char *sName; /* Nom du serveur */
  char *sMail; /* Adresse de MSG si changement de status */
  char *sIp; /* Adresse IP du serveur */

  char  *sProto; /* TCP ou UDP */
  int   **sPort; /* Tableau de ports [NUM][STATUS] */
} list;
