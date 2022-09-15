#include "Printf.h"
#include <iostream>

int main(int , char**) 
{
    char buffer[13] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};
    std::cout << std::endl << "Letztes Element im Buffer (Main): " << buffer[12] << std::endl;
    
	const char* combinedStr		= "%b";
    
	char* ergebnis = Printf(buffer, buffer + 12, combinedStr, 0);

	std::cout << "-------Main Test Ausgabe---" << std::endl;

	if(ergebnis == buffer + 3) {
        std::cout << "Pointer stimmt" << std::endl;
    } else {
        std::cout << ergebnis - (buffer + 3) << std::endl;
        std::cout << "Pointer stimmt nicht" << std::endl;
	}
    if(buffer[3] == '\0') {
        std::cout << "Nullterminator so wie erwartet" << std::endl;
    } else {
        std::cout << "Nullterminator nicht so wie erwartet" << std::endl;
	}
       
    for(int i = 0; '\0' != buffer[i]; i++) {
        std::cout << "Element:" << i << " : "<< buffer[i] << std::endl;
    }
    
}

	