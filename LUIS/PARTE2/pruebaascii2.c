#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *salida;
	unsigned char c;
/*	for(c=32;c<255;c++) 
	{
		putc(c,stdout);
	} */
	
	unsigned int i;
/*	i=getchar();
	printf("\n"); */
	salida=fopen("salidaprueba.txt", "w+");
	/* putchar(i);
	printf("\n %d  %c \n", i, (char) i); */
	FILE *fptrnandu;
	if ((fptrnandu = fopen("nandu.txt", "r")) == NULL)
		{
		printf("Error nandu.txt no existe");
		exit(1);
		}
	
	while ((i=fgetc(fptrnandu)) != EOF)
		{
		printf("caracter leído: %d %c\n",i,(char) i);
		fputc(i,stdout);
		fputc(i,salida);
		printf("%c\t)", i);
		}
	fclose(fptrnandu);
	fclose(salida);
	return 0;
}
