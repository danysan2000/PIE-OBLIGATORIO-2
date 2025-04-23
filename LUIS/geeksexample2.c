#include <stdio.h>
#include <stdlib.h>

struct threeNum {
	unsigned int n1, n2, n3;
};


int main()
{
	int n, i;
	struct threeNum num;
	FILE *fptr;
	if ((fptr= fopen("program5.bin",  "rb")) == NULL)
	{
		printf("Error! opening  file");
		exit(1);
	}
	/* for (n=1;n<5;++n)	
		{
		size_t result = fread(&num, sizeof(struct threeNum), 1, fptr);
		printf("elemnetos leidos %d\tn1: %d\tn2 %d\tn3: %d\n", result, num.n1, num.n2, num.n3);
		}
		*/
	for (i=1;i<5;i++)
	{
		fscanf(fptr, " %x %x %x", &num.n1, &num.n2, &num.n3);
		printf("n1: %d\tn2 %d\tn3: %d\t n1hex: %x\tn2hex: %x\tn3hex: %x\n", num.n1, num.n2, num.n3, num.n1, num.n2, num.n3);
	}
	fclose(fptr);
	return 0;
}
/* archivo de salida */
/*
luisrepetto@fedora:~/UdelarFing/PIE/obligatorios/obligatorio2$ ./a.out
n1: 1	n2 5	n3: 6	 n1hex: 1	n2hex: 5	n3hex: 6
n1: 2	n2 16	n3: 17	 n1hex: 2	n2hex: 10	n3hex: 11
n1: 3	n2 15	n3: 22	 n1hex: 3	n2hex: f	n3hex: 16
n1: 4	n2 32	n3: 33	 n1hex: 4	n2hex: 20	n3hex: 21
luisrepetto@fedora:~/UdelarFing/PIE/obligatorios/obligatorio2$ 
*/

/* Archivo de entrada program5.bin */
/*
1        5       6
2       10      11
3     	f     16
4       20      21
*/
		

