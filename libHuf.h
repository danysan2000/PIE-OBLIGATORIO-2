/*
  libHuf.h
*/

typedef struct Simbolo **SIMBOLO;

typedef enum codigo_error
{
	TODOOK = 0,
	ERRORLECTURA = 1,
	ARCHIVOINEXISTENTE = 2,
	ERRORESCRITURA = 3,
	CODIGOMUYLARGO = 4,
	ERRORMEMORIA = 5,
} CodigoError ;


