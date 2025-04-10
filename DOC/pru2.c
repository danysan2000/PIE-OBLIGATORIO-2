#include <stdio.h>

union BitMapper {
    unsigned int a;
    struct {
        unsigned int a0  : 1;
        unsigned int a1  : 1;
        unsigned int a2  : 1;
        unsigned int a3  : 1;
        unsigned int a4  : 1;
        unsigned int a5  : 1;
        unsigned int a6  : 1;
        unsigned int a7  : 1;
        unsigned int a8  : 1;
        unsigned int a9  : 1;
        unsigned int a10 : 1;
        unsigned int a11 : 1;
        unsigned int a12 : 1;
        unsigned int a13 : 1;
        unsigned int a14 : 1;
        unsigned int a15 : 1;
        unsigned int a16 : 1;
        unsigned int a17 : 1;
        unsigned int a18 : 1;
        unsigned int a19 : 1;
        unsigned int a20 : 1;
        unsigned int a21 : 1;
        unsigned int a22 : 1;
        unsigned int a23 : 1;
        unsigned int a24 : 1;
        unsigned int a25 : 1;
        unsigned int a26 : 1;
        unsigned int a27 : 1;
        unsigned int a28 : 1;
        unsigned int a29 : 1;
        unsigned int a30 : 1;
        unsigned int a31 : 1;
    } bits;
};

int main() {
    union BitMapper mapper;
    
    mapper.a = 0x0A0A0A0A;  // Asignamos un valor al entero
    printf("Valor de a: %08X\n", mapper.a);
    
    // Accedemos a los bits individualmente
    printf("Bit 0: %u\n", mapper.bits.a0);
    printf("Bit 1: %u\n", mapper.bits.a1);
    printf("Bit 2: %u\n", mapper.bits.a2);
    printf("Bit 3: %u\n", mapper.bits.a3);
    printf("Bit 4: %u\n", mapper.bits.a4);
    printf("Bit 5: %u\n", mapper.bits.a5);
    // ... y así sucesivamente para los demás bits
    
    // Modificamos un bit específico
    mapper.bits.a5 = 1;
    printf("--------------------------------");
    printf("Nuevo valor de a: %08X\n", mapper.a);
    printf("Bit 0: %u\n", mapper.bits.a0);
    printf("Bit 1: %u\n", mapper.bits.a1);
    printf("Bit 2: %u\n", mapper.bits.a2);
    printf("Bit 3: %u\n", mapper.bits.a3);
    printf("Bit 4: %u\n", mapper.bits.a4);
    printf("Bit 5: %u\n", mapper.bits.a5);
    
    return 0;
}
