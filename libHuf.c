/*
 * libhuf.c  Huffman
 *
*/
#include <stdio.h>
#include <libHuf.h>


struct Simbolo
{
	unsigned char valor;
	int nbits;
	unsigned int codigo;
};

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

/*
3+4+5+6+7+8+9+10+11+12+13 = 88
32-13= 19 gaps
*/


union  CodEncod2 {  /* ver2 */
	unsigned int regA;
	struct { bittypes vec : 1; } v[32]; /* vecotor de un 1 probar */
}


/* Prototitpos */
/* funciones a implementar */
CodigoError leertablacodificaciontxt(FILE *fpTdC, SIMBOLO tablaCod, int* nbS); /* <---???? simbolo ** */
CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, SIMBOLO tablaCod, int nbS);
CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM);
CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, SIMBOLO Tabla, int NbS);
int indiceEnTabla(unsigned int codigo, int nbits, SIMBOLO tablaCod, int NbS);
CodigoError salvarcodigos(SIMBOLO tablaCod, int NbS, FILE* out);
void liberarTabla();


CodigoError leertablacodificaciontxt(FILE *fpTdC, SIMBOLO tablaCod, int* nbS) /* <---???? simbolo ** */
{
	CodigoError ret = TODOOK;

	return ret;
}


CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, SIMBOLO tablaCod, int nbS)
{
	CodigoError ret = TODOOK;
	return ret;
}


CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM)
{
	CodigoError ret = TODOOK;
	return ret;
}


CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, SIMBOLO Tabla, int NbS)
{
	CodigoError ret = TODOOK;
	return ret;
}


int indiceEnTabla(unsigned int codigo, int nbits, SIMBOLO tablaCod, int NbS)
{
	int valret = 0;
	/*  CodigoError ret = TODOOK; */
	return valret;
}


CodigoError salvarcodigos(SIMBOLO tablaCod, int NbS, FILE* out)
{
	CodigoError ret = TODOOK;
	return ret;
}


void liberarTabla()
{
	return;
}

