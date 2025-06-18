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
	FILE *fpTdC = NULL;
	char op;
	int nbS, errArg;
	/* procesar argumentos */
	if( (errArg=argumentos1(argc , argv, &op, &fpIn, &fpOut, &fpTdC)) != TODO_OK )
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
			if ( codificarConTabla(  fpIn, fpOut, TablaCod, nbS) != TODO_OK )
				printf("Error en CODIFICAR\n");
			break;
		case 'D':
			if ( decodificarConTabla( fpIn, fpOut, TablaCod, nbS) != TODO_OK )
				printf("Error en DECODIFICAR\n");
			break;
		case 'T':
			/* leertablacodificaciontxt(fpTdC, &TablaCod,  &nbS); */
			salvar_codigos(TablaCod, nbS,  fpOut);
			break;

		case 'P': /* prueba de indiceEntabla  */
			{
				int nbS;
				int codigo = 0xe26e27b3;
				int nbits  = 4;
				leertablacodificaciontxt(fpTdC,  &TablaCod, &nbS) ;
				if( indiceEnTabla(codigo, nbits, TablaCod, nbS) > -1 )
					printf( " OK ");
				else
					printf( " NO ESTA ");
				codigo = 0x926e27b3; 
				nbits  = 4;
				leertablacodificaciontxt(fpTdC,  &TablaCod,  &nbS) ;
				if( indiceEnTabla(codigo, nbits, TablaCod, nbS) > -1 )
					printf( " OK ");
				else
					printf( " NO ESTA ");
			}
	}
	
return 0;
}


CodigoError argumentos1(int argc , char **argv, char *op, FILE **fpIn, FILE **fpOut, FILE **fpTdC )
{
	/* Analizo argumentos y abro archivos */

	if(  argc < 5 ) return ERRORARGUMENTOS;
	*op =  *argv[1];  /* comando */
	if( *op != 'C' && *op != 'D' && *op != 'T' && *op != 'P' ) return ERRORARGUMENTOS;
	if (  (*fpTdC = fopen( argv[4],"rb")) == NULL ) return ARCHIVO_INEXISTENTE;
	switch((int)*op)
	{
		case 'C':
			*fpIn=fopen(argv[2], "rb");
			*fpOut=fopen(argv[3],"w+b");
			if( *fpIn==NULL || *fpOut==NULL )
			   	return ARCHIVO_INEXISTENTE;
			break;
		case 'D':
			if( !strcmp( argv[3], "stdout") )
				*fpOut = stdout;
			else
				*fpOut=fopen(argv[3],"w+b");
			*fpIn=fopen(argv[2] ,"rb");
			if( *fpOut == NULL || *fpIn == NULL )
				return ARCHIVO_INEXISTENTE ;
			break;

		case 'T': /* segun letra se ignoran los archivos, pero el de salida seria donde se imprimen */
		case 'P':
			if( !strcmp( argv[2], "stdout") )
				*fpOut = stdout;
			else
			{
				*fpOut=fopen(argv[2],"w+b");
				if( *fpOut ==NULL )
					return ARCHIVO_INEXISTENTE ;
			}
			break;

		default:
			return ERRORARGUMENTOS; /* error en argumentos */
	}
	
	return TODO_OK;
}



