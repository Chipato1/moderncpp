#include "PreAllocString.h"

template<unsigned int LEN>
PreAllocString<LEN>::operator const char*() const
{
    return static_cast<const char*>(buffer);
} 

template<unsigned int LEN>
PreAllocString<LEN>::operator const void*() const
{
    return static_cast<const void*>(buffer);
}

template<unsigned int LEN>
const char& PreAllocString<LEN>::operator[](const int idx)
{
    if((buffer + idx) >= act)
	{
        return nullptr;
	}
    return buffer[idx];
}

template<unsigned int LEN>
size_t PreAllocString<LEN>::GetLength() const
{
	return maxlength;
}


template<unsigned int LEN>
constexpr size_t PreAllocString<LEN>::SizeOf()
{
    return 100;
}

template<unsigned int LEN>
void PreAllocString<LEN>::Empty()
{
    act = buffer;
}

template<unsigned int LEN>
PreAllocString<LEN>& PreAllocString<LEN>::operator=(char rhs)
{
    PreAllocString::Empty();
    act = Printf(act, buffer + maxlength - 1, "%c", rhs);
    return *this;
}

template<unsigned int LEN>
PreAllocString<LEN>& PreAllocString<LEN>::operator=(const char* rhs)
{
    PreAllocString::Empty();
    act = Printf(act, buffer + maxlength - 1, "%s", rhs);
    return *this;
}

template<unsigned int LEN>
PreAllocString<LEN>& PreAllocString<LEN>::operator=(char* const rhs)
{
    PreAllocString::Empty();
    act = Printf(act, buffer + maxlength - 1, "%s", rhs);
    return *this;
}

template<unsigned int LEN>
PreAllocString<LEN>& PreAllocString<LEN>::operator+=(char rhs)
{
    act = Printf(act, buffer + maxlength - 1, "%c", rhs);
    return *this;
}

template<unsigned int LEN>
PreAllocString<LEN>& PreAllocString<LEN>::operator+=(char const* rhs)
{
    act = Printf(act, buffer + maxlength - 1, "%c", rhs);
    return *this;
}