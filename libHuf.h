/*
  libHuf.h

*/


typedef struct Simbolo 
{
	unsigned char valor;
	int nbits;
	unsigned int codigo;
}simbolo;


typedef enum codigo error
{
	T ODO OK = 0,
	ERROR LECT U RA = 1,
	ARCHIV O IN EXIST EN T E = 2,
	ERROR ESCRIT U RA = 3,
	CODIGO M U Y LARGO = 4,
	ERROR M EM ORIA = 5,
}CodigoError ;


