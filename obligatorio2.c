/*
PIE -- TAREA-2

Programa principal "obligatorio2"   

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits.h>
#include <libHuf.h>


CodigoError argumentos1(int , char **,char *,FILE **, FILE **, FILE **); /* procesa argumentos */


int main(int argc , char **argv )
{
	simbolo *TablaCod = NULL;
	FILE *fpIn  = NULL;
	FILE *fpOut = NULL;
	FILE *fpTdC = NULL ;
	char op;
	int nbS, errArg;
	/* procesar argumentos */
	if( (errArg=argumentos1(argc , argv, &op, &fpIn, &fpOut, &fpTdC)) != TODOOK )
	{
		printf("Error en argumentos:\n"
                "    Use: obligatorio2 comando archivo1.[txt][cod] archivo2.[cod][txt] archivo3.[codigos]\n"
                "            donde comando : [C] [D] [T]\n"
                "                            [T] archivo1.sal pueder ser -t stdout\n");
		exit(1);
	}

	leertablacodificaciontxt(fpTdC, &TablaCod,  &nbS);
	switch ( op )
	{
		case 'C':
			if ( codificarConTabla(  fpIn, fpOut, TablaCod, nbS) != TODOOK )
				printf("Error en CODIFICAR\n");
			break;
		case 'D':
			if ( decodificarConTabla( fpIn, fpOut, TablaCod, nbS) != TODOOK )
				printf("Error en DECODIFICAR\n");
			break;
		case 'T':
			/* leertablacodificaciontxt(fpTdC, &TablaCod,  &nbS); */
			salvar_codigos(TablaCod, nbS,  fpOut);
			break;
	}
	
return 0;
}


CodigoError argumentos1(int argc , char **argv, char *op, FILE **fpIn, FILE **fpOut, FILE **fpTdC )
{
	/* Analizo argumentos y abro archivos */
	char fileCodigos[100], filetxt[100], filecodificado[100];

	if(  argc < 5 ) return ERRORARGUMENTOS;
	*op =  *argv[1];  /* comando */
	if( *op != 'C' && *op != 'D' && *op != 'T' ) return ERRORARGUMENTOS;
	strcpy( fileCodigos,argv[4]); /* file Codigos */
	if (  (*fpTdC = fopen( fileCodigos,"rb")) == NULL ) return ARCHIVOINEXISTENTE;
	switch((int)*op)
	{
		case 'C':
			strcpy( filetxt, argv[2]); /* file in "nombreArchivo.txt */
			strcpy( filecodificado,argv[3]); /* file out"ArchivoCodificado */
			*fpIn=fopen(filetxt, "rb");
			*fpOut=fopen(filecodificado,"w+b");
			if( *fpIn==NULL || *fpOut==NULL )
			   	return ARCHIVOINEXISTENTE;
			break;
		case 'D':
			strcpy( filecodificado, argv[2]); /* file in "ArchivoCodificado */
			strcpy( filetxt,argv[3]); /* file out "ArchivoDecodificado.txt */
			if( !strcmp( filetxt, "stdout") )
				*fpOut = stdout;
			else
				*fpOut=fopen(filetxt,"w+b");
			*fpIn=fopen(filecodificado ,"rb");
			if( *fpOut == NULL || *fpIn == NULL )
				return ARCHIVOINEXISTENTE ;
			break;
		case 'T': /* segun letra se ignoran los archivos, pero el de salida seria donde se imprimen */
			strcpy( filetxt,argv[2]); /* file out "ArchivoDecodificado.txt */
			if( !strcmp( filetxt, "stdout") )
				*fpOut = stdout;
			else
			{
				*fpOut=fopen(filetxt,"w+b");
				if( *fpOut ==NULL )
					return ARCHIVOINEXISTENTE ;
			}
			break;

		default:
			return ERRORARGUMENTOS; /* error en argumentos */
	}
	
	return TODOOK;
}



