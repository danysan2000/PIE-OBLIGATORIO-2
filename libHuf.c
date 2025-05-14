/*
 * libhuf.c  Huffman
 *
*/
#include <stdio.h>
#include <stdalign.h>
#include <libHuf.h>



/* struct auxliar Procesamiento record para Codificar y Decodificar */
typedef unsigned int bittypes;
union  CodEncod {
	bittypes regA; /* 32 bits */
	struct { bittypes b3:  3 ; } b03;
	struct { bittypes b4:  4 ; } b04;
	struct { bittypes b5:  5 ; } b05;
	struct { bittypes b6:  6 ; } b06;
	struct { bittypes b7:  7 ; } b07;
	struct { bittypes b8:  8 ; } b08;
	struct { bittypes b9:  9 ; } b09;
	struct { bittypes b10: 10; } b10;
	struct { bittypes b11: 11; } b11;
	struct { bittypes b12: 12; } b12;
	struct { bittypes b13: 13; } b13;
	struct { bittypes gap: 19; } gap;
};


CodigoError leertablacodificaciontxt(FILE *fpTdC, simbolo **tablaCod, int* nbS) 
{
	int ix,err;

	fscanf(fpTdC, "%d", nbS);
	*tablaCod = malloc( (sizeof(simbolo) * *nbS) );

	if (*tablaCod == NULL) return ERRORMEMORIA;
	
	for( ix=0; ix < *nbS ; ix++)
	{
		err=fscanf(fpTdC, "%x %d %x",
	(unsigned int*) &( (*tablaCod)[ix].valor),
					&( (*tablaCod)[ix].nbits),
					&( (*tablaCod)[ix].codigo) );
		if( err == EOF ) return ERRORLECTURA;
	}
	return TODOOK;
}


CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, simbolo *tablaCod, int nbS)
{
	CodigoError ret = TODOOK;

	unsinged char *Msj, aux_char;
	int nbM, curs_nbm, err;

	int ix,ij;
	alignas (int) unsigned char buff_work[500]; /* buff_work espacio de trabajo en memoria */
	unsigned int *buf2; /* auxiliar de buff_work */
	int curBit; /* cursor bit dentro del int : acumula los bit concatenados  */
	unsigned int aux_codigo;  /* cargo aca el simbolo.codigo */
	unsigned int aux_nbits;   /* cargo el simbolo.nbits */
	unsigned int curs_buf; /* cursor buff_work */
	typedef sturct {
		int nbits;
		unsigned int codigo;
	} MAQTAB; /* struct especial para codificacion */
	MAQTAB *maqtab ; /* struct array donde el indicie es el valor char del texto a codificar */


	if ( (err = leerArchivotxt( fpIn,  &Msj, &nbM) ) != TODOOK ) return err;
	/* Inicializo MaqCodec */
		/* desde tablaCod genero una nueva structura array */
	maqtab = malloc( nbS * sizeof( MAQTAB ) );
	if( maqtab == NULL ) return ERRORMEMORIA;

	for(ix=0; ix < nbS ; ix++)
	{
		ij = tablaCod[ix].valor;
		maqtab[ij].nbits =  tablaCod[ix].nbits;
		maqtab[ij].codigo = tablaCod[ix].codigo;
	}
	/* Comienzo Codificacion. */
	curs_buf = 0; /* indice que representa un pack de 4 bytes */
	curs_nbm = 0; /* indice de Msj */
	buf2= ((int * )buff_work)+curs_buf ;   /* ahora buf2 apunta a 4 bytes de buff_work */
	*buf2 = 0;
	curBit = 0;
	while( true )
	{

		aux_char = Msj[ curs_nbm++ ];
		aux_nbits =   maqtab[aux_char].nbits;
		aux_codigo =  maqtab[aux_char].codigo;

		if ( (curBit + aux_nbits ) > 32 ) /* problemas de bordes */
		{
			/* curBit podria  ser justo 32 ;; dejo aca preparado para seguir cargando buf2 */

		}
		else
		{
			*buf2 = concatena ( *buf2 , aux_codigo, aux_nbits );
			curBit += aux_nbits;
		}
	

		if( curs_buf > 124 ) /* grabar el buffer codificado al archivo de salida  */
		{

		}
		if( curs_nbm  < nbM ) /* chequeando si se termina el buffer de entrada */
		{
			/* grabar el buffer de salida pendiente */

		}
	}

	free(maqtab);
	return ret;
}


CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM)
{
	CodigoError ret = TODOOK;
	/* calculo la longitud del archivo */
	 *nbM = fseek( fpIn, (long ) 0, -1 ); /* final del archivo */
	 if( *nbM == 0 ) return ERRORLECTURA;
	/* pido Memoria */
	*Msj = malloc( *nbM );
	/* asigno el contenido del archivo a Msj */
	if (  fread( Msj, 1, *nbM , fpIn) != *nbM ) return ERRORLECTURA;
	return ret;
}


CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo *Tabla, int NbS)
{
	CodigoError ret = TODOOK;
	return ret;
}


int indiceEnTabla(unsigned int codigo, int nbits, simbolo *tablaCod, int NbS)
{
	int valret = 0;
	/*  CodigoError ret = TODOOK; */
	return valret;
}


CodigoError salvar_codigos(simbolo *TablaCod, int NbS, FILE* out)
{
	CodigoError ret = TODOOK;
	int ix;
	fprintf(out,"%03d\n",NbS);
	for(ix=0; ix<NbS ; ix++)
	{
		fprintf( out , "%x %d %x\n", 
				TablaCod[ix].valor,
				TablaCod[ix].nbits,
				TablaCod[ix].codigo );
	}
	return ret;
}


void liberarTabla()
{
	return;
}

