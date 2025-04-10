#include <stdio.h>

int main() {
    unsigned int x = 0x0A0B0C0D;
    unsigned char *p = (unsigned char*)&x;
    
    printf("Byte en posición 0: %02X\n", p[0]); // LSB (0D en little-endian)
    printf("Byte en posición 1: %02X\n", p[1]); // 0C
    printf("Byte en posición 2: %02X\n", p[2]); // 0B
    printf("Byte en posición 3: %02X\n", p[3]); // MSB (0A en little-endian)
    
    if (p[0] == 0x0D) {
        printf("Es little-endian (Intel)\n");
    } else {
        printf("Es big-endian\n");
    }
    
    return 0;
}

