#include "7Segment.h"
#include<iostream>

int main(int , char**) {
    constexpr MultiDigit md2{1 ,2};
    std::cout << static_cast<const char*>(md2);
}