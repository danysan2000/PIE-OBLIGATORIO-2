/*
 * libhuf.c  Huffman
 *
*/

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
CodigoError leertablacodificacion txt(FILE *fpTdC, simbolo** tablaCod, int* nbS); /* <---???? simbolo ** */

CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, simbolo* tablaCod, int nbS);

CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM);

CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo* Tabla, int NbS);

int indiceEnTabla(unsigned int codigo, int nbits, simbolo* tablaCod, int NbS);

CodigoError salvar codigos(simbolo* tablaCod, int NbS, FILE* out);

void liberarTabla();

