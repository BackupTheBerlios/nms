#MAKEFILE

CC	=	cc
FLAGS	=	-Wall
EXEC	=	nms

all:		nms.o parse.o perror.o tcp.o file.o libchar.o sendmail.o test.o readconf.o
		cd src/
		$(CC) -o $(EXEC) $(FLAGS) nms.o parse.o perror.o tcp.o file.o libchar.o sendmail.o test.o readconf.o
		cp nms ../
		cd ..

nms.o:		src/nms.c
		cd src/
		$(CC) $(FLAGS) -c nms.c
parse.o:	src/parse.c
		cd src/
		$(CC) $(FLAGS) -c parse.c
perror.o:	src/perror.c
		cd src/
		$(CC) $(FLAGS) -c perror.c
tcp.o:		src/tcp.c
		cd src/
		$(CC) $(FLAGS) -c tcp.c
file.o:		src/file.c
		cd src/
		$(CC) $(FLAGS) -c file.c
libchar.o:	src/libs/libchar.c
		cd src/
		$(CC) $(FLAGS) -c libs/libchar.c
test.o:		src/test.c
		cd src/
		$(CC) $(FLAGS) -c test.c
sendmail.o:	src/sendmail.c
		cd src/
		$(CC) $(FLAGS) -c sendmail.c
readconf.o:	src/readconf.c
		cd src/
		$(CC) $(FLAGS) -c readconf.c

clean:
		rm -Rf src/*.o
		rm -Rf src/*~
		rm -Rf srinclude/*~
mrproper: 	clean
		rm -rf $(EXEC)
