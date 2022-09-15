#include "OptParser.h"

bool CmdLineOptParser::Parse(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++) {
        /*calculate the length of the actual char-array out of argv*/
        int length_act = 0;
        while (argv[i][length_act] != '\0') 
		{
            length_act++;
        }
        /*return false if the Input is shorter than 2*/
        if (length_act < 2) 
		{
            return false;
        }
        /*return false if the seconde element is a letter*/
        else if (!((argv[i][1] >= 'A' && argv[i][1] <= 'Z') || (argv[i][1] >= 'a' && argv[i][1] <= 'z'))) 
		{
            return false;
        }
        /*the first character must only be a '-'*/
        else if (argv[i][0] != '-') 
		{
            return false;
        }
        /*if the input is longer than two check for a variable an if the statement is with or without '='*/
        else if (length_act > 2) 
		{
            int start_of_value = -1;
			/*the start of the value depends on if there is a '=' on the third place*/
            if (argv[i][2] == '=') 
			{
                start_of_value = 3;
            } else 
			{
                start_of_value = 2;
            }
			/*check if all characters of the value are accepted*/
            for(int n = start_of_value; argv[i][n] != '\0'; n++) 
			{
                if(argv[i][n] < '!' || argv[i][n] > '~') 
				{
					return false;
                }
            }
			/*pass the second element and the Value to Option. If Option is false: return false*/
            if(Option(argv[i][1], &(argv[i][start_of_value])) == false) 
			{
                return false;
            }

        } 
		else if(length_act == 2) 
		{
            /*If the Program reached the last input return anyway*/
            if(i == (argc - 1)) 
			{
                return Option(argv[i][1], nullptr);
            }
            /*If the next expression starts with an '-' it can not be a value*/
            if(argv[i + 1][0] == '-') {
                if(Option(argv[i][1], nullptr) == false) 
				{
                    return false;
				}
			}
            /*in the other cases the next expression will be a value*/
			else {
                /*check if all characters are numbers, letters or common symbols*/
				for(int n = 0; argv[i + 1][n] != '\0'; n++) 
				{
                    if(argv[i + 1][n] < '!' || argv[i + 1][n] > '~') 
					{
                      return false;
                   }
				}
				/*check Option with the next Element of argv and increment i*/
                if(Option(argv[i][1], argv[i + 1]) == false) 
				{
                    return false;
                }
                i++;
            }
        }
    }
    return true;
}

bool CmdLineOptParser::Option(const char, const char*)
{
    return true;
}