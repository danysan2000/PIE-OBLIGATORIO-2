/*
PIE -- TAREA-2

Programa principal "obligatorio2"   

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits.h>
#include <libHuf.h>


int argumentos1(int , char **,char *,FILE *, FILE *, FILE *); /* procesa argumentos */


int main(int argc , char **argv )
{
	simbolo *TablaCod= NULL;
	FILE *fpIn, *fpOut, *fpTdC;
	char op;
	/* procesar argumentos */
	if( argumentos1(argc , argv, &op, fpIn, fpOut, fpTdC ) != TODOOK )
	{
	   	printf("Error en argumentos:\n \
	Use: obligatorio2 comando archivo1.[txt][cod] archivo2.[cod][txt] archivo3.[codigos]\n \
	donde comando : [C] o [D] o [T]\n\n ");
		exit(1);
	}
	switch ( op )
	{
		case 'T':
			leerTabla
			break;
		default:

	}
	
return 0;
}


int argumentos1(int argc , char **argv, char *op, FILE *fpIn, FILE *fpOut, FILE *fpTdC )
{
	/* Analizo argumentos y abro archivos */
	char fileCodigos[100], filetxt[100], filecodificado[100];

	if( argc < 2) return ERRORARGUMENTOS; /* error en cantidad de argumentos */

	*op =  *argv[1]; /* comando */
	if( (*op != 'C' && *op != 'D' && *op != 'T' )  || argc < 5 ) return ERRORARGUMENTOS;
			
	strcpy( fileCodigos,argv[4]); /* file Codigos */
	if (  (fpTdC = fopen( fileCodigos,"r")) == NULL ) {return ARCHIVOINEXISTENTE; }
	switch((int)*op)
	{
		case 'C':
			strcpy( filetxt, argv[2]); /* file in "nombreArchivo.txt */
			strcpy( filecodificado,argv[3]); /* file out"ArchivoCodificado */
			if( ((fpIn=fopen(filetxt, "r"))==NULL) || (fpOut=fopen(filecodificado,"r"))==NULL)
			   	return ARCHIVOINEXISTENTE;
			break;
		case 'D':
			strcpy( filecodificado, argv[3]); /* file in "ArchivoCodificado */
			strcpy( filetxt,argv[2]); /* file out "ArchivoDecodificado.txt */
			if( ((fpOut=fopen(filetxt,"r")) == NULL) || ( (fpIn=fopen(filecodificado ,"r")) == NULL ))
				return ARCHIVOINEXISTENTE ;
			break;
		case 'T': /* horror segun letra se ignoran los archivos */
			break;

		default:
			return ERRORARGUMENTOS; /* error en argumentos */
	}
	
	return TODOOK;
}


