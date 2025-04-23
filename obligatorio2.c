/*
PIE -- TAREA-2

Programa principal "obligatorio2"   

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits.h>
#include <libHuf.h>


int argumentos1(int , char **,char *,char * , char *,char *); /* procesa argumentos */
FILE * arch1, arch2 , arch3; /*  segun comando C o D */
char cmd;  /* cmd = 'C' o 'D' */


int main(int argc , char **argv )
{
	SIMBOLO TablaCod= NULL;
	char filetxt[100], filecodificado[100], fileCodigos[100];
	char op;
	/* procesar argumentos */
	if( argumentos1(argc , argv, &op, filetxt, filecodificado, fileCodigos) )
	{
	   	printf("Error en argumentos\n \
				Use: obligatorio2 comando archivo1.[txt][cod] archivo2.[cod][txt] archivo3.[codigos]\n \
				donde comando : [C] o [D] \
				");
		exit(1);
	}
	
return 0;
}


int argumentos1(int argc , char **argv, char *op, char *filetxt, char *filecodificado, char *fileCodigos )
{
	/* open TablaDeCodificacion256.txt */
	/* calcular la tablaCod */
	if( argc < 5 ) return 1; /* error en cantidad de argumentos */
	*op =  *argv[1]; /* comando */
	strcpy( fileCodigos,argv[4]); /* file Codigos */
	switch((int)*op)
	{
		case 'C':
			strcpy( filetxt, argv[2]); /* file in "nombreArchivo.txt */
			strcpy( filecodificado,argv[3]); /* file out"ArchivoCodificado */
			break;
		case 'D':
			strcpy( filecodificado, argv[3]); /* file in "ArchivoCodificado */
			strcpy( filetxt,argv[2]); /* file out "ArchivoDecodificado.txt */
			break;
		default:
			return 2; /* error en argumentos */
	}
	/* check archivos si existen y si no existen. */
	/* stat files */
	
	
	return 0;
}


/*
3+4+5+6+7+8+9+10+11+12+13 = 88
32-13= 19 gaps
*/
