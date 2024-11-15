/*
	Makro oder ander L�sung f�r Template vor jeder Funktion?
    const char& PreAllocString<LEN>::operator[](const int idx)  nullptr??????
	Linker Problem
*/

#ifndef PREALLOCSTRING_H
#define PREALLOCSTRING_H

#include "Printf.h"
#include "stddef.h"


#define CREATE(varName, size)

template<unsigned int LEN>
class PreAllocString 
{	
	public:

		PreAllocString();
        ~PreAllocString();

		operator const char*() const;
		operator const void*() const;

		const char& operator[](const int idx);

		/* Current number of characters in string */
		size_t GetLength() const;

		/* Maximum number of characters possible */
		constexpr size_t SizeOf();

		/* Empty the string , set length field to zero */
		void            Empty();

		PreAllocString& operator=(char rhs);
		PreAllocString& operator=(const char* rhs);
		PreAllocString& operator=(char* const rhs);
		PreAllocString& operator+=(char rhs);
		PreAllocString& operator+=(char const* rhs);

		void            AddFormat(const char* format, ...);
		void            AddWhiteSpace(); 

	private:
        char		buffer[LEN];
        char*		act;
        const int	maxlength = LEN;
};          

#endif