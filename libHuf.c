/*
 * libhuf.c  Huffman
 *
*/
#include <stdio.h>
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



union  CodEncod2 {  /* ver2 */
	unsigned int regA;
	struct { bittypes vec : 1; } v[32]; /* vecotor de un 1 probar */
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
	return ret;
}


CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM)
{
	CodigoError ret = TODOOK;
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

