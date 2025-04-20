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

simbolo  *tablaCod;
/* Prototitpos */
/* funciones a implementar */
CodigoError leertablacodificaciontxt(FILE *fpTdC, simbolo** tablaCod, int* nbS); /* <---???? simbolo ** */
CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, simbolo* tablaCod, int nbS);
CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM);
CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo* Tabla, int NbS);
int indiceEnTabla(unsigned int codigo, int nbits, simbolo* tablaCod, int NbS);
CodigoError salvarcodigos(simbolo* tablaCod, int NbS, FILE* out);
void liberarTabla();


CodigoError leertablacodificaciontxt(FILE *fpTdC, simbolo** tablaCod, int* nbS) /* <---???? simbolo ** */
{
	CodigoError ret = TODOOK;
	return ret;
}


CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, simbolo* tablaCod, int nbS)
{
	CodigoError ret = TODOOK;
	return ret;
}


CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM)
{
	CodigoError ret = TODOOK;
	return ret;
}


CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo* Tabla, int NbS)
{
	CodigoError ret = TODOOK;
	return ret;
}


int indiceEnTabla(unsigned int codigo, int nbits, simbolo* tablaCod, int NbS)
{
	int valret = 0;
	/*  CodigoError ret = TODOOK; */
	return valret;
}


CodigoError salvarcodigos(simbolo* tablaCod, int NbS, FILE* out)
{
	CodigoError ret = TODOOK;
	return ret;
}


void liberarTabla()
{
	return;
}

