/*
PIE -- TAREA-2

Programa principal "obligatorio2"   


*/


#include <stdio.h>
#include <bits.h>
#include <libHuf.h>

extern simbolo *tablaCod;

int argumentos1(int, char **); /* procesa argumentos */
FILE * arch1, arch2 , arch3; /*  segun comando C o D */
char cmd;  /* cmd = 'C' o 'D' */

int main(int argc , char **argv )
{
	// procesar argumentos
	if ( argumentos1(argc , argv) ) 
	{
	   	printf("Error en argumentos\nUse: obligatorio2 comando archivo1.[txt][cod] archivo2.[cod][txt] archivo3.[codigos]\n");
		exit(1);
	}

return 0;
}


int argumentos(int argc , char **argv)
{
	/* open TablaDeCodificacion256.txt */

}

