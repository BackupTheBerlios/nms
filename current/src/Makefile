#MAKEFILE

CC	=	cc
FLAGS	=	-Wall -g
EXEC	=	nms

.KEEP_STATE:

all:		nms.o parse.o perror.o netsock.c file.o libchar.o sendmail.o test.o readconf.o
		$(CC) -o $(EXEC) $(FLAGS) nms.o parse.o perror.o netsock.c file.o libchar.o sendmail.o test.o readconf.o

nms.o:		nms.c
		$(CC) $(FLAGS) -c nms.c
parse.o:	parse.c
		$(CC) $(FLAGS) -c parse.c
perror.o:	perror.c
		$(CC) $(FLAGS) -c perror.c
netsock.o:		netsock.c
		$(CC) $(FLAGS) -c netsock.c
file.o:		file.c
		$(CC) $(FLAGS) -c file.c
libchar.o:	libs/libchar.c
		$(CC) $(FLAGS) -c libs/libchar.c
test.o:		test.c
		$(CC) $(FLAGS) -c test.c
sendmail.o:	sendmail.c
		$(CC) $(FLAGS) -c sendmail.c
readconf.o:	readconf.c
		$(CC) $(FLAGS) -c readconf.c

clean:
		rm -Rf *.o
		rm -Rf *~
		rm -Rf include/*~
mrproper: 	clean
		rm -rf $(EXEC)
