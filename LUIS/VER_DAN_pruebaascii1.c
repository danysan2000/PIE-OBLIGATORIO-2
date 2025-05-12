#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	unsigned char c;
/*	for(c=32;c<255;c++) 
	{
		putc(c,stdout);
	} */
	
	unsigned int i;
	/*
	i=getchar();
	printf("\n");
	
	putchar(i);
	printf("\n %d  %c \n", i, (char) i);
	*/

	FILE *fptrnandu;
	/* if ((fptrnandu = fopen("nandu.txt", "rb")) == NULL) */
	if ((fptrnandu = fopen("nandu.txt", "r")) == NULL)
	{
		printf("Error nandu.txt no existe");
		exit(1);
	}
	
	printf( "Ahora si reconoce el EOF \n");
	/* while ( c=fgetc(fptrnandu)!= EOF) */
	while ( (i=fgetc(fptrnandu))  != EOF)
	{
		if( i == 195)
	   	{
			*((unsigned char*)&i + 1) = (unsigned char) fgetc(fptrnandu) ;  // Correcto.Segundo caracter
		   	// printf("%.2s\n",(unsigned char*) &i);
			printf("caracter leído: %x %.2s\n",i,(unsigned char *)&i);
		}
		else
		{
			printf("caracter leído: %d %c\n",i,i);
		}
	/* 	fputc((int) c,stdout); /* ????  */
	}
	fclose(fptrnandu);
	return 0;
}
