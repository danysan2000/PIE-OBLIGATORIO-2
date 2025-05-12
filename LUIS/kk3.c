#include <stdio.h>
#include <wchar.h>


int main()
{

		wchar_t tt;
		tt = 0xC3B1;
//		wprintf("%lc\n", tt);


    // Cadena de caracteres anchos (wide string)
    wchar_t* mensaje = L"¡Hola, mundo! 🌍";
    int numero = 42;

    // Usando wprintf para imprimir
    wprintf(L"Mensaje: %ls\nNúmero: %d\n", mensaje, numero);

    // También puedes imprimir caracteres wide individuales
    wchar_t corazon = L'❤';
    wprintf(L"Corazón: %lc\n", corazon);

	return 0;
}

