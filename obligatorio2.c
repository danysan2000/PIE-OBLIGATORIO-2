/*
PIE -- TAREA-2

Programa principal "obligatorio2"   

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits.h>
#include <libHuf.h>


int argumentos1(int , char **,char *,FILE **, FILE **, FILE **); /* procesa argumentos */


int main(int argc , char **argv )
{
	simbolo *TablaCod = NULL;
	FILE *fpIn  = NULL;
	FILE *fpOut = NULL;
	FILE *fpTdC = NULL ;
	char op;
	int nbS;
	/* procesar argumentos */
	if( argumentos1(argc , argv, &op, &fpIn, &fpOut, &fpTdC ) != TODOOK )
	{
		printf("Error en argumentos:\n\
Use: obligatorio2 comando archivo1.[txt][cod] archivo2.[cod][txt] archivo3.[codigos]\n\
donde comando : [C] archivo1.txt archivo2.cod\n\
                [D] archivo1.cod archivo2.txt\n\
                [T] archivo1.sal archivo2(seignora) archivo3.[codigos]\n\
           o pueder ser  ^--- stdout\n");
		exit(1);
	}
	switch ( op )
	{
		case 'T':
			leertablacodificaciontxt(fpTdC, &TablaCod,  &nbS);
			salvar_codigos(TablaCod, nbS,  fpOut);
			break;
		default:

	}
	
return 0;
}


int argumentos1(int argc , char **argv, char *op, FILE **fpIn, FILE **fpOut, FILE **fpTdC )
{
	/* Analizo argumentos y abro archivos */
	char fileCodigos[100], filetxt[100], filecodificado[100];

	*op =  *argv[1];  /* comando */
	if( (*op != 'C' && *op != 'D' && *op != 'T' )  || argc < 5 ) return ERRORARGUMENTOS;
	strcpy( fileCodigos,argv[4]); /* file Codigos */
	if (  (*fpTdC = fopen( fileCodigos,"r")) == NULL ) {return ARCHIVOINEXISTENTE; }
	switch((int)*op)
	{
		case 'C':
			strcpy( filetxt, argv[2]); /* file in "nombreArchivo.txt */
			strcpy( filecodificado,argv[3]); /* file out"ArchivoCodificado */
			*fpIn=fopen(filetxt, "r");
			*fpOut=fopen(filecodificado,"w+");
			if( *fpIn==NULL || *fpOut==NULL )
			   	return ARCHIVOINEXISTENTE;
			break;
		case 'D':
			strcpy( filecodificado, argv[3]); /* file in "ArchivoCodificado */
			strcpy( filetxt,argv[2]); /* file out "ArchivoDecodificado.txt */
			*fpOut=fopen(filetxt,"w+");
			*fpIn=fopen(filecodificado ,"r");
			if( *fpOut == NULL || *fpIn == NULL )
				return ARCHIVOINEXISTENTE ;
			break;
		case 'T': /* segun letra se ignoran los archivos, pero el de salida seria donde se imprimen */
			strcpy( filetxt,argv[2]); /* file out "ArchivoDecodificado.txt */
			if( !strcmp( filetxt, "stdout") )
				*fpOut = stdout;
			else
			{
				*fpOut=fopen(filetxt,"w+");
				if( *fpOut ==NULL )
					return ARCHIVOINEXISTENTE ;
			}
			break;

		default:
			return ERRORARGUMENTOS; /* error en argumentos */
	}
	
	return TODOOK;
}


