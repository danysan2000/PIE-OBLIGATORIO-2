/*
PIE
OBLIGATORIO 1.
Archivo contendor de funciones de operacion binarias.
NOTA:
    CADA FUNCION NO LLAMA A OTRA FUNCION DE ESTA LIBRERIA-ARCHIVO.
MOTIVO:
    ES PARA RESPETAR LA PROGRAMACION MODULAR, UNA FUNCION NO ES USADA DENTRO DE OTRA FUNCION.
    PARA QUE EL LINKEDITOR SOLO TOME LA FUNCION QUE SE USA Y NO CARGUE TODAS LAS FUNCIONES.
    ES EL OBJETIVO DE TODA LIBRERIA QUE SE CARGUE LO QUE SE NECESITA.
*/

#include <stdio.h>
#include "bits.h"


/* ----- FUNCIONES AUXILIARES ---------
 * Todas staticas locales al modulo bits.c
Funcion power(int , int)
Motivo:
    Cuando se simula en software operaciones con bits,
    es muy conveniente tener la funcion potencia entera
    para poder trabajar con 2 elevado a la n.
    Facilita la generacion de mascaras como por ejemplo.
    Lenguaje C no tiene implementado como operador el 
    operador de potencia, como en otros lenguajes.
    exiten librerias como math.a donde estan las mayorias
    de las funciones matematica.
RESTRICCION:
    NO SE PUEDE USAR LA LIBRERIA MATH POR RESTRICION
    DEL TRABAJO OBLIGATORIO.
    Entiendo que el objetivo es usar los operadores 
    shit left and right para adquirir practica.
*/


static unsigned int power(base,exp )
int base,exp;
{
    unsigned int res;
    for(res=1 ; exp ; exp--) res *= base;
    return res;
}    

/* --------------FIN FUNCIONES AUXILIARES ----- */

#define rotoLeft(a , b)   ( a <<(b) )  
#define rotoRight(a , b)  ( a >>(b) ) 


/* bit( )
.- Retorna el valor del bit nb del entero sin signo buffer.
buffer: como entero sin signo.
nb: como entero.

Descripcion del codigo.
   mascara inicial   00000001 
    sobre mascara inicial left shit hasta el
    bit deseado.
    si el valor resultante es distinto de cero retorno 1 sino retorno 0;
Nota:    
    se podria usar la funcion pow() para reemplazar la operacion shit left
    pero la restriccion de la letra no se puede usar la libreria math.
*/    

int bit(unsigned int buffer, int nb)
{
    if ( (nb > (int)  (sizeof(int) * 8) )  ) return -1;
    return ( buffer & rotoLeft( 1, nb)  ) ? 1 : 0 ;
}    

/* int ver_binario( )
   Esta función debe enviar al puntero de archivo nombrearchivo (en forma
   binaria) los nb bits menos significativos del entero sin signo buffer. Luego
   de hacerlo, se debe finalizar con un salto de línea.

buffer: como entero sin signo.
nb: NOTA : aca es la cantidad de bits. 
nombreArchivo: como puntero a FILE.
*/

int ver_binario(unsigned int buffer, int nb, FILE* nombreArchivo)
{
    unsigned char buf[70];
    int aux1;
    int vsize;


    vsize = sizeof(int) * 8;
    if ( nb > vsize || nb < 1  || nombreArchivo == NULL ) return -1; /* error de rango */

    /*  incializo el vector con cero NO CON '0'  */
    for( aux1=0; aux1 < 70; aux1++ )
        buf[aux1] = 0; 
    
    for( aux1 = nb; aux1 ; aux1-- ) 
        buf[aux1-1]= ( buffer &  rotoLeft(1,nb-aux1)  ) ? '1' : '0' ;
    buf[nb] = '\n';

    if ( (int) fwrite( buf,1,nb, nombreArchivo ) != nb )
        return -1;
    return 0;
}

/*
   Debe imprimir en pantalla (en forma binaria) los nb bits menos
   significativos del entero sin signo buffer. Luego de hacerlo, se debe
   finalizar con un salto de línea. 

buffer: como entero sin signo.
nb: como entero
*/

void print_binario(unsigned int buffer, int nb)
    /* aca nb bits no es el numero de bit es la cantidad de bits */
{
    int aux1;
    if( nb > (int) (sizeof(int) * 8) ) return; /* valido nb */
    for( aux1=nb; aux1 ; aux1-- )
        printf("%1d", (buffer & rotoLeft( 1, aux1-1 ) ? 1 : 0 ) );
    printf("\n");
}

/*
   Debe setear el bit nb del entero sin signo buffer con el valor
   de val  (0 o 1).
   Esta función retornará el nuevo buffer como entero sin signo.

buffer: como entero sin signo.
nb: como entero.
val: como entero
*/

unsigned int setbit(unsigned int buffer, int nb, int val)
{
    unsigned int res;
    unsigned int msk1;

    /* preparo  mascara todos en 1 menos el bit seleccionado en 0 */
    msk1 =  ~power(2,nb);
    res  =  ( buffer & msk1 );
    return  ( val ) ? res | ~msk1 : res;
}

/*
   Concatena lo que había en el entero sin signo buffer con los nb bits más
   significativos del entero sin signo codigo.

buffer: como entero sin signo.
PIE Obligatorio 1 - Biblioteca de trabajo con bits 8
codigo: como entero sin signo.
nb: como entero. Cantidad de bits
*/

unsigned int concatena(unsigned int buffer, unsigned int codigo, int nb)
{
    unsigned int  msk1;
    msk1 = (power(2,nb)-1)  ; /* pongo en 1 los nb primeros de la mascara */
    return ( ( buffer << nb ) | ( codigo & msk1  ) );
}


/*
   Debe crear una máscara cuyos bits valgan 0 con excepción de los que se
   encuentran entre el bit min y el bit max (incluyéndolos).
   
max: como entero.
min: como entero
*/

unsigned int crear_mascara(int max, int min)
{
    unsigned int  msk ;
    int nb ; /* numero de bits */

    /* Valido max y min */
    if( ( max <= min ) || ( max > (int) (sizeof(unsigned int)* 8) ) ) 
    {
            printf("ERROR en crear_mascara: Parametros invalidos \n" );
            return 0;
    }
    nb = max - min + 1; /* numero de bits */
    msk = 0;
    msk = power( 2, nb ) - 1;  /* armo el paquete inicial de 1 al principio msk */
    msk =  msk << min ; 
    return msk ;
}

/*
   Debe tomar los nbits menos significativos de un entero sin signo in y
   espejarlos.

in: como entero sin signo.
nbits: como entero
*/

unsigned int espejar(unsigned int in, int nbits)
{
    unsigned int aux1, aux2;
    unsigned int msk1;
    unsigned int res;
    /* Valido argumentos de entrada */
    if( nbits > (int) (sizeof(int) * 8 ) )
    {
        printf("Error en espejar: Argumento invalido\n");
        return 0;
    }
    msk1 = power(2,nbits)-1; /* mascara con los primeros nbits en 1   */
    aux1 =  in & msk1 ;  /* en aux1 me quedan solo los primeros nbits  */
    res = 0;
    for( aux2=nbits ; aux2 ; aux2-- )
        res = (res << 1) | ( ( aux1 & (1<<(nbits-aux2))) ? 1 : 0 ); /* roto res por 1 y sumo bit a bit  de in enmascarado (aux1) */
    return res ;
}


/*
   Devuelve un entero sin signo donde los bits menos signficativos contienen
   los bits entre min y max de buffer (incluyéndolos) y el resto de los bits
   vale 0.

buffer: como entero sin signo.
min: como entero.
max: como entero
*/

unsigned int extraer(unsigned int buffer, int min, int max)
{
    unsigned int msk1;
    unsigned int res;

    /* Valido argumentos */
    if( max > (int)(sizeof(int)* 8) )
    {
        printf("Error en extraer: Argumentos invalidos \n");
        return 0;
    }
    /*  armo mascara hago and y luego roto derecha */
       /* msk1 : tengo los bits max-min y roto min a la izq  */
    msk1= ( (power(2,(max-min+1))-1)) << (min) ;
    res = buffer & msk1;
    res = res >> min;
    return res; 
}


