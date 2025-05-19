/*
 * libhuf.c  Huffman
 *
*/
#include <stdint.h>
#include <stdio.h>
#include <stdalign.h>
#include <bits.h>
#include <libHuf.h>


static uint32_t to_big_endian(uint32_t value);

/* struct auxliar Procesamiento record para Codificar y Decodificar */
/* No utilizado */
/* ( para version 2.0 ) */
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
	/* INIT variables */
	CodigoError ret = TODOOK;

	unsigned  char *Msj, aux_char;
	int nbM, curs_nbm, err;

	int ix,ij;  /* variables auxiliares para loops */
	alignas (int) unsigned char buff_work[500]; /* buff_work espacio de trabajo en memoria */
	unsigned int *buf2; /* auxiliar de buff_work */
	int curBit; /* cursor bit dentro del int : acumula los bit concatenados  */
	unsigned int aux_codigo;  /* cargo aca el simbolo.codigo */
	unsigned int aux_nbits;   /* cargo el simbolo.nbits */
	unsigned int curs_buf; /* cursor buff_work */
	typedef struct {
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
	buf2= (( unsigned int * )buff_work)+curs_buf ;   /* ahora buf2 apunta a 4 bytes de buff_work */
	*buf2 = 0;
	curBit = 0;
	fwrite( "\0",1,1, fpOut); /* primer byte reservado para NbStuff */
	while( 1 )
	{

		aux_char   = Msj[ curs_nbm++ ]; /* tomo byte */
		aux_nbits  = maqtab[aux_char].nbits;
		aux_codigo = maqtab[aux_char].codigo;

		if ( (curBit + aux_nbits ) > 32 ) /* problemas de bordes */
		{
			/* curBit podria  ser justo 32 ;; dejo aca preparado para seguir cargando buf2 */
			int dif1; /* diferencia a 32 */

			curs_buf++;
			dif1 = 32 - curBit ;
			if( dif1 > 0 )
			{ 
				/* aca la cantidad de bits sobrepasa el ultimo byte */
				*buf2 = (unsigned int ) concatena( *buf2 , aux_codigo>> (aux_nbits-dif1), dif1 ); /* completo el byte */
				*buf2 = to_big_endian( (uint32_t) *buf2 ); /* problema de endiannes */
				if( curs_buf > 124 ) /* grabar el buffer codificado al archivo de salida  */
				{
					fwrite( buff_work , 1 , sizeof(buff_work) , fpOut ); /* buff completo */
					curs_buf = 0;
				}
				buf2  = ((unsigned int * )buff_work)+curs_buf ;   /* ahora buf2 apunta a 4 bytes de buff_work */
				*buf2 = 0;
				/* Ahora falta completar los bits pendientes de codigo  */
				*buf2 = concatena( *buf2 , aux_codigo, (aux_nbits-dif1) );
				curBit = aux_nbits-dif1;
			}
			else
			{
				/* es justo 32 bit avanzo el buf2 */
				*buf2 = to_big_endian( (uint32_t) *buf2 ); /* problema de endianness */
				if( curs_buf > 124 ) /* grabar el buffer codificado al archivo de salida  */
				{
					fwrite( buff_work , 1 , sizeof(buff_work) , fpOut ); /* buff completo */
					curs_buf = 0;
				}
				buf2= ((unsigned int * )buff_work)+curs_buf ;   /* ahora buf2 apunta a 4 bytes de buff_work */
				*buf2 = 0;
				*buf2 = concatena ( *buf2 , aux_codigo, aux_nbits );
				curBit = aux_nbits;
			}
		}
		else
		{
			*buf2 =  (unsigned int ) concatena ( *buf2 , aux_codigo, aux_nbits );
			curBit += aux_nbits;
		}
	
		if( curs_nbm >= nbM ) /* chequeando si se termina el buffer de entrada */
		{
		/* grabar el buffer de salida pendiente */
			/* chequeo si hay algo pendiente para grabar */
			unsigned char NbStuff = 0; /* variable para indicar la cantidad de ceros de relleno */
			if( !( curs_buf == 0 && curBit == 0 ) )
			{
				/* calculo de byte y fill de zeros para completar el byte */
				int reng, col ;
				curBit--; /* descuento 1 porque estoy parado donde tengo que seguir escribiendo  */
				col = curBit % 8;  /* para saber cuantos zeros para completar el byte (fill) */
				reng =  ( curBit - col ) / 8; /* para saber cual de los 4 bytes estoy */
				NbStuff =  7 - col; /*ceros para completar */
				*buf2 = to_big_endian( (uint32_t) *buf2 ); /* problema de endianness */
				fwrite ( buff_work , 1 , ( curs_buf*4)+reng+1 , fpOut );
			}
			fseek( fpOut, 0,0);
			fwrite( &NbStuff, 1,1, fpOut); /* guardo NbStuff  */
			fclose( fpOut );
			break; /* salgo del while */
		}
	}
	free(maqtab);
	return ret;
}


CodigoError leerArchivotxt(FILE* fpIn, unsigned char **Msj, int* nbM)
{
	CodigoError ret = TODOOK;
	/* calculo la longitud del archivo */
	 fseek( fpIn, (long ) 0, SEEK_END ); /* final del archivo */
	 *nbM = ftell(fpIn);
	 fseek( fpIn, (long ) 0, SEEK_SET ); /* comienzo del archivo */

	 if( *nbM == 0 ) return ERRORLECTURA;
	/* pido Memoria */
	 /* por un tema de compatibilidad con decodificarconTabla le sumo al buffer Msj para que sea
	  * multiplo  de 4 sin cambiar nbM */
	 if ( *nbM % 4 ) 
		 /* no es multiplo */
		 *Msj = calloc( (*nbM + 3 - (*nbM % 4)) , 1 );
	 else
		*Msj = calloc( *nbM, 1 );
	/* asigno el contenido del archivo a Msj */
	if (  fread( *Msj, 1, *nbM , fpIn) != *nbM ) return ERRORLECTURA;
	return ret;
}

CodigoError decodificarConTabla(FILE* fpIn, FILE* fpOut, simbolo *Tabla, int NbS)
{
	CodigoError ret = TODOOK;
	int curBit;
	unsigned int aux_nbits, col, ren;
	int ind_tab;
	/* leer el archivo de entrada ; lo hago con leerarchivotxt igual son todos unsigned char  */
	unsigned  char *MsjCod;
	int nbM, err;
	unsigned int ptr;
	unsigned int aux_codigo,aux_codigo2;

	if ( (err = leerArchivotxt( fpIn,  &MsjCod, &nbM) ) != TODOOK ) return err;
	curBit = 0;
	ptr = 1;
	do
	{
		 aux_codigo  = to_big_endian( (unsigned int) *((unsigned int*)(MsjCod+ptr)) );
		 aux_codigo2 = extraer( aux_codigo , 0, 31-curBit) << curBit;
		/* ind_tab = indiceEnTabla( extraer( to_big_endian( (unsigned int) *((unsigned int*)(MsjCod+ptr)) ) , 0, 31-curBit), NULL  , Tabla, NbS); */
		ind_tab = indiceEnTabla( aux_codigo2, NULL, Tabla, NbS);
		if ( ind_tab < 0 ) /* ERROR no encontro el codigo */
		{
			ret = ERRORCODIGONOEXISTE;
			break;
		}
		else
		{
			fprintf(fpOut, "%c", Tabla[ind_tab].valor );
			fflush(fpOut);
		}

		aux_nbits = Tabla[ind_tab].nbits; /* tomo los nbits del codigo encontrado */
		curBit += aux_nbits; /*  aux_nbits para el proximo codigo */

		/* calcular ptr y CurBit  */
		/* ajustar col dependiendo si hay o no cambio de renglon */ 
		col  =  ( curBit % 8);                   /* columna dentro del byte */
		ren  =  ( curBit - col ) / 8 ;
		if ( ren != 0 )
		{
			/* tengo que ajustar curbit a col */
			curBit = col; 
			ptr   += ren;           /* ptr como renglon es el indice de MsjCod */
		}			
	} while(  ptr < nbM-1 && ( ret == TODOOK ) );
	return ret;
}


/* por ahora no le encuentro sentido a esta funcion,
 * ya que nbits no lo tengo como dato sino lo tengo que buscar dentro de la tabla
 * comenzando de menor a mayor.
 *
 * PASO COMO PUNTERO nbits , para que la funcion me diga cuantos nbits tiene el codigo buscado 
 * return: -1 si no lo encuentra.
 */
/*
 * funcion original 
  int indiceEnTabla(unsigned int codigo, int *nbits, simbolo *tablaCod, int NbS)
DAN int indiceEnTabla(unsigned int codigo, simbolo *tablaCod, int NbS)
*/
int indiceEnTabla(unsigned int codigo, int *nbits, simbolo *tablaCod, int NbS)
{
	
	int valret = -1;
	int ix; /* auxiliares para loops */
	unsigned int aux_codigo, aux_codigoTab;
	int aux_nbits;
	unsigned int mask; /* mascara para testear segun nbits con codigo */
	/* primer intento busco en la tabla sin considerar el orden de los nbits pero comienzo por abajo */
	ix= NbS-1;
	aux_nbits = -1; /* inicio aux_nbits */
	do 
	{
		/* leo el indice ix de la tabla */
		aux_codigoTab = tablaCod[ix].codigo;
		/* aux_valor  = tablaCod[ix].valor; */
		/* armo la mascara para los nbits correspondientes */
		if ( aux_nbits !=  tablaCod[ix].nbits )
		{
			aux_nbits   = tablaCod[ix].nbits;
			mask        = crear_mascara( 31, 32-aux_nbits ); /* verificar  */
			aux_codigo  = extraer( (codigo & mask ),32-aux_nbits , 31);

		}
		/* comparo con codigo */
		 if( aux_codigoTab == aux_codigo ) 
			valret = ix ; /* lo encontro */
	} while( valret == -1  && ix--  );
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


static uint32_t to_big_endian(uint32_t value) 
{
    uint32_t result = 0;
    result |= (value & 0xFF000000) >> 24;  /* Byte 3 (MSB) -> Byte 0 */
    result |= (value & 0x00FF0000) >> 8;   /* Byte 2 -> Byte 1 */
    result |= (value & 0x0000FF00) << 8;    /* Byte 1 -> Byte 2 */
    result |= (value & 0x000000FF) << 24;   /* Byte 0 (LSB) -> Byte 3 */
    return result;
}

