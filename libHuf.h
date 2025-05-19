/*
  libHuf.h
*/
#include <stdlib.h>


typedef struct Simbolo
{
	unsigned char valor;
	int nbits;
	unsigned int codigo;
}simbolo;


typedef enum codigo_error
{
	TODOOK = 0,
	ERRORLECTURA = 1,
	ARCHIVOINEXISTENTE = 2,
	ERRORESCRITURA = 3,
	CODIGOMUYLARGO = 4,
	ERRORMEMORIA = 5,
	ERRORARGUMENTOS = 6, 
	ERRORCODIGONOEXISTE = 7,
} CodigoError ;


CodigoError leertablacodificaciontxt(FILE *fpTdC, simbolo **tablaCod, int* nbS); 
CodigoError codificarConTabla(FILE *fpIn, FILE *fpOut, simbolo *tablaCod, int nbS);
CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM);
CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo *Tabla, int NbS);
int indiceEnTabla(unsigned int codigo, int *nbits, simbolo *tablaCod, int NbS); /* dejo el Original */
/* DAN  int indiceEnTabla(unsigned int codigo, simbolo *tablaCod, int NbS); */
CodigoError salvar_codigos(simbolo *tablaCod, int NbS, FILE* out);
void liberarTabla();


