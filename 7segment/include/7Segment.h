#ifndef _7SEGMENT_H_
#define _7SEGMENT_H_

/*H**********************************************************************
 * FILENAME :        7Segment.h
 *
 * DESCRIPTION :
 *       Generate a Sting for a Segement-display
 *
 * PUBLIC FUNCTIONS :
 *       Multidigit MultiDigit(const T ... numbers)
 *		 operator const char*() const
 *
 * NOTES :
 *       If Inputparams are not in Range: empty space will be printed.
 *       No Copyright :-)
 *
 * AUTHOR :    Carl Winkler        START DATE :    20. March 19
 *
 *
 *H*/

#include <limits>

#define CHAR_HEIGHT 5
#define CHAR_WIDTH 4

template<typename... T>
class MultiDigit
{
	public:
		constexpr MultiDigit(const T ... numbers)
		{
            /*if Constexpr makes sure that only numbers will be printed if input-params were passed*/
            if constexpr(sizeof...(numbers)) {

                for(unsigned int i = 0; i < sizeof...(T) * CHAR_HEIGHT * CHAR_WIDTH - 1; i++) {
                    buffer[i] = ' ';
                }

				Add(0, numbers...);
				
				buffer[1 * sizeof...(T) * CHAR_WIDTH - 1]          = '\n';
				buffer[2 * sizeof...(T) * CHAR_WIDTH - 1]          = '\n';
				buffer[3 * sizeof...(T) * CHAR_WIDTH - 1]          = '\n';
				buffer[4 * sizeof...(T) * CHAR_WIDTH -1]		   = '\n';
				buffer[5 * sizeof...(T) * CHAR_WIDTH -1]		   = '\0';
            } else {
				/*create an empty string if no params are passed.*/
                buffer[0] = '\0';
            }
		}
        /*This Method recursivly calls itself until no params are left*/
		template<typename T1, typename... Args>
        constexpr void Add(int pos, T1 first_num, Args... args)
        {
            static_assert(std::numeric_limits<T1>::is_integer, "All Params need to be Integers.");
            
			/*Set the qequired char depending on which number is in firstnum*/
            if(first_num == 0 || first_num == 2 || first_num == 3 || first_num == 5 || first_num == 6 || first_num == 7 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 1] = '-';
            } 
            if(first_num == 0 || first_num == 4 || first_num == 5 || first_num == 6 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 1 * sizeof...(T) * CHAR_WIDTH] = '|';
            }
            if(first_num == 0 || first_num == 1 || first_num == 2 || first_num == 3 || first_num == 4 || first_num == 7 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 1 * sizeof...(T) * CHAR_WIDTH + 2] = '|';
            } 

            if(first_num == 2 || first_num == 3 || first_num == 4 || first_num == 5 || first_num == 6 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 2 * sizeof...(T) * CHAR_WIDTH + 1] = '-';
            }

            if(first_num == 0 || first_num == 2 || first_num == 6 || first_num == 8) {
                buffer[pos * CHAR_WIDTH + 3 * sizeof...(T) * CHAR_WIDTH] = '|';
            }
            if(first_num == 0 || first_num == 1 || first_num == 3 || first_num == 4 || first_num == 5 || first_num == 6 || first_num == 7 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 3 * sizeof...(T) * CHAR_WIDTH + 2] = '|';
            }

            if(first_num == 0 || first_num == 2 || first_num == 3 || first_num == 5 || first_num == 6 || first_num == 8 || first_num == 9) {
                buffer[pos * CHAR_WIDTH + 4 * sizeof...(T) * CHAR_WIDTH + 1] = '-';
            }	
			/*Call the add method again with decreased amount of params if there are params left*/
            if constexpr(sizeof...(Args)) {
				Add(pos+1, args...);  
			}
        }

        operator const char*() const 
		{ 
			return static_cast<const char*>(buffer);
		}

	private:
		/*the size of the array is increment by one to make sure that there is one space if no params were passed*/
        char buffer[sizeof...(T) * CHAR_WIDTH * CHAR_HEIGHT + (static_cast<int>(sizeof...(T)) == 0)] = {};
};
#endif
