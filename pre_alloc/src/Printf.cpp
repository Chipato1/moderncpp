#include "Printf.h"

/*chararr_out need to have a size bigger than 34*/
void int2bin(char* chararr_out, int sint_in)
{
    if(chararr_out == nullptr) {
        return;
    }
    chararr_out[0] = '0';
    chararr_out[1] = 'b';

    int  numcnt = 2;
	/*return for 0 becaus it is not covered by the algorithm*/
    if(sint_in == 0) {
        chararr_out[2] = '0';
        chararr_out[3] = '\0';
        return;
    }

    bool found1 = false;
	/*Shift all bits into the binary array*/
    for(int bits_n = 31; bits_n >= 0; bits_n--) {
        int shifted_int = sint_in >> bits_n;
        shifted_int     = shifted_int & 1;
		/*use a flag to avoid leading zeros*/
        if(shifted_int == 1) {
            found1              = true;
            chararr_out[numcnt] = '1';
            numcnt++;
        } else {
            if(found1 == true) {
                chararr_out[numcnt] = '0';
                numcnt++;
            }
        }
    }
    chararr_out[numcnt] = '\0';
}

char* Printf(char* dst, const void* end, const char* fmt, ...)
{
	/*catch nullptr and dst can never be at the same spot as end or even smaller*/
    if(dst == nullptr || end == nullptr || fmt == nullptr || dst >= end) {
        return nullptr;
    }

    va_list argp;
    va_start(argp, fmt);

    /*remaining_buffersize is the length of the buffer in the beginning*/
    int buffersize = 0;
    for(char* i = dst; i <= end; i++) {
        buffersize++;
    }

    int remaining_buffersize = buffersize;
	/*Iterate through the hole fmt string up to Null-Terminator*/
    for(int i = 0; '\0' != fmt[i]; i++) {

        int used_length_instep = 0;

        if(fmt[i] != '%') {
            snprintf(dst, remaining_buffersize, "%c", fmt[i]);
            used_length_instep++;

        } else if(fmt[i] == '%') {
			/*use snprintf for all cases except of b*/
            switch(fmt[i + 1]) {
                case 'd': {
                    used_length_instep = snprintf(dst, remaining_buffersize, "%d", va_arg(argp, int));
                    break;
                }
                case 'u': {
                    used_length_instep = snprintf(dst, remaining_buffersize, "%u", va_arg(argp, unsigned int));
                    break;
                }
                case 'c': {
                    used_length_instep = snprintf(dst, remaining_buffersize, "%c", va_arg(argp, int));
                    break;
                }
                case 's': {
                    char* c = va_arg(argp, char*);
                    if(c == nullptr) {
                        return nullptr;
					}
                    used_length_instep = snprintf(dst, remaining_buffersize, "%s", c);
                    break;
                }
                case 'x': {
                    used_length_instep = snprintf(dst, remaining_buffersize, "%s", "0x");
                    used_length_instep += snprintf(dst+2, remaining_buffersize-2, "%x", va_arg(argp, int));
                    break;
                }
                case 'b': {
					/*generate extra string to save the temporary output of the int2bin function */
                    char tmpstring[35] = {'\0'};
                    int2bin(tmpstring, va_arg(argp, int));

                    used_length_instep = snprintf(dst, remaining_buffersize, "%s", tmpstring);
                    break;
                }
                case '%': {
                    used_length_instep = snprintf(dst, remaining_buffersize, "%c", '%');
                    break;
                }
                default: return nullptr;
            }
            i++;
        }

        if(used_length_instep < 0) {
            return nullptr;
		}
		/*control if the buffer is full an eventually return*/
        if(remaining_buffersize - used_length_instep <= 0) {
            *(dst + remaining_buffersize - 1) = '\0';
            return dst + remaining_buffersize -1;
        } else {
            /*set the dst pointer to the next Null-Terminator in the buffer*/
            remaining_buffersize = remaining_buffersize - used_length_instep;
            dst                  = dst + used_length_instep;
        }
    }
    va_end(argp);
	/*return dst if the buffer was not absolutely full after parsing fmt*/
    return dst;
}