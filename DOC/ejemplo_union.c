#include <stdio.h>



struct pepe {
	unsigned int a0:1;
	unsigned int a1:1;
	unsigned int a2:1;
	unsigned int a3:1;
	unsigned int a4:1;
	unsigned int a5:1;
	unsigned int a6:1;
	unsigned int a7:1;
	unsigned int a8:1;
	unsigned int a9:1;
	unsigned int a10:1;
	unsigned int a11:1;
	unsigned int a12:1;
	unsigned int a13:1;
	unsigned int a14:1;
	unsigned int a15:1;
	unsigned int a16:1;
	unsigned int a17:1;
	unsigned int a18:1;
	unsigned int a19:1;
	unsigned int a20:1;
	unsigned int a21:1;
	unsigned int a22:1;
	unsigned int a23:1;
	unsigned int a24:1;
	unsigned int a25:1;
	unsigned int a26:1;
	unsigned int a27:1;
	unsigned int a28:1;
	unsigned int a29:1;
	unsigned int a30:1;
	unsigned int a31:1;
};


union kakon {
	unsigned int a;
	struct {
		unsigned int b:1;
	} b;
	struct pepe y;
};

int check( union kakon );

int main()
{
	union kakon kk;

	kk.a = 6;
	check( kk );
	kk.a = 21;
	check(kk);
	printf("\n\n kk.a = %d\n", kk.a );
	printf(" kk.y.a0 = %d\n", kk.y.a0 );
	printf(" kk.b.b = %d\n", kk.b.b);
}
	
int check( union kakon kk )
{	
	printf(" kk.a = %d\n", kk.a );
	if( kk.b.b)
		printf("impar\n");
	else 
	   	printf("par\n"); 
}	
	

