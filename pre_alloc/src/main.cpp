#include "PreAllocString.h"
#include <iostream>
int main(int , char**) 
{
    PreAllocString<12> xzy;
    const char*        c = "ABC";
    xzy                  = c;
}

	