#include <stdio.h>

unsigned int getbits(unsigned int x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

/* Set n bits at pos in x with n least significat bits in y
   ex: setbits(0b1111, 2, 2, 0b00) would return result 0b1001 */
unsigned int setbits(unsigned int x, int pos, int n, unsigned int y) {
    unsigned int mask = ~(~0 << n); 
    unsigned int bits_to_shift = pos + 1 - n; // number of bits needed to shift to original position

    unsigned int new_bits, shifted_mask;

    new_bits = y & mask;                      // get only the n least significant bits
    new_bits <<= bits_to_shift;               // shift new_bits into position you want to change them in for x

    shifted_mask = ~(mask << bits_to_shift);  // shift the mask to bitwise-not it to bitwise-or it with the new_bits later
    shifted_mask &= x;                        // bitwise-and shifted_mask with x to cut off the left-most trailing 1-bits 

    return new_bits | shifted_mask;           // combines new_bits and shifted_mask giving final result
}

void print_bits(unsigned int num){
    unsigned int size = sizeof(unsigned char);
    unsigned int max_pow = 1<<(size*8-1);

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < 8; ++j) {
            // print last bit and shift left.
            printf("%u", num&max_pow ? 1 : 0);
            num = num << 1;
        }
    }
    printf("\n");
}

int main() {
    print_bits(getbits(0b00011100, 4, 3));         // 00000111
    print_bits(setbits(0b00000000, 5, 4, 0b1111)); // 00111100

    return 0;
}

