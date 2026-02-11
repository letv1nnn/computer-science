#include <iostream>

#ifndef ASM
float process(float a, float b, int c, float d) {
   return (a + b) / ((float)c + d);
}
#else
extern "C" float process(float a, float b, int c, float d);
#endif

// FPU x87 - floating point unit

int main(int argc, char **argv) {
    float a{1.1}, b{2.2}, d{4.4};
    int c{3};

    float res = process(a, b, c, d);
    
    std::cout << res << std::endl;

    return 0;
}

