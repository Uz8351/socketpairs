/*
Socket_Pair.c
*/


#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "variables.h"

#define MENSAJE1 "VERITAS FILIA TEMPORIS -SAECULA SAECULORUM"
#define MENSAJE2 "NO ENTIENDO MUY BIEN EL LATIN"

int main(int argc, char const *argv[])
{

int Socket_PADRE[2], Socket_HIJO;
unsigned char CONTENEDOR_BUFFER [1048];

/*
Función socketpair
*****************
#include <sys/socket.h>

 int socketpair(int domain, int type, int protocol, int sv[2]);

La función socketpair() crea un par de sockets del tipo especificado
que no tienen nombre y están conectados en el dominio indicado
y utilizando el protocolo especificado.

Argumentos descripción.
----------------------
dominio:(PF_UNIX,  AF_UNIX, PF_LOCAL, AF_LOCAL)
El dominio: en el que abrir el socket.
Aunque se pueden obtener pares de sockets para sockets de dominio AF_INET,
se recomienda utilizar sockets de dominio:PF_UNIX, AF_UNIX para pares de sockets.

El tipo: de socket creado, ya sea SOCK_STREAM o SOCK_DGRAM.

Protocolo:El protocolo solicitado debe ser 0.
sv:Array, con los descriptores utilizados
para referirse a los sockets obtenidos.
*/
if(socketpair(PF_UNIX,SOCK_STREAM,0,Socket_PADRE)<0) //SOCK_STREAM, orientado a conexión.

{
perror("Error abriendo los sockets");
exit(1);
}

/*Ahora  Socket_PADRE va a crear el proceso Socket_HIJO*/

if ((Socket_HIJO=fork())== -1)
perror("Error creando Socket_HIJO");

else if (Socket_HIJO)
{

/*Si el Socket_HIJO es creado cerraremos el primer
descriptor padre Socket_PADRE[0]*/
	close(Socket_PADRE[0]);

/*Comprobamos que el Socket_PADRE[1]-segundo descriptor lee el mensaje
de CONTENEDOR_BUFFER y lo imprimimos*/

if(read(Socket_PADRE[1],CONTENEDOR_BUFFER,1048)<0)
	perror("Error Socket_PADRE[1] leyendo el mensaje");


printf("Imprimimos CONTENEDOR_BUFFER de Socket_PADRE[1] \n");
printf("Dirección de inicio de Buffer Socket_PADRE[1]:[%p]\n",&CONTENEDOR_BUFFER );
printf("--------------------------------------------------------------------------\n");
Imprimir_Buffer(CONTENEDOR_BUFFER , 192); //Llamamos a la función de volcado.
printf("***************************************************************************\n" );

/*Ahora comprobamos que Socket_PADRE[1] puede leer el MENSAJE2*/
if(write(Socket_PADRE[1],MENSAJE2, strlen(MENSAJE2)+1)<0)
perror("Socket_PADRE[1] tuvo un error escribiendo el mensaje");

/* Cerramos el descriptor Socket_PADRE[1]*/

close(Socket_PADRE[1]);
}

else{
/* Pasamos al control del descriptor Socket_HIJO*/

if(write(Socket_PADRE[0],MENSAJE1,strlen(MENSAJE1)+1)<0)
	perror("Error Socket_HIJO escribiendo MENSAJE");

if(read(Socket_PADRE[0],CONTENEDOR_BUFFER,1048)<0)
perror("Error Socket_HIJO leyendo MENSAJE");	

printf("Imprimimos CONTENEDOR_BUFFER de Socket_HIJO (cerrado Socket_PADRE[1]) \n");
printf("Dirección de inicio de Buffer Socket_HIJO:[%p]\n",&CONTENEDOR_BUFFER );
printf("*************************************************************************\n");
printf("\n");
Imprimir_Buffer(CONTENEDOR_BUFFER , 192); //Llamamos de nuevo a nuestra función de volcado.

 close(Socket_PADRE[0]);


}
exit(2);
}

