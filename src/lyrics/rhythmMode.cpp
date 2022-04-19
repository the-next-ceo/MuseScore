#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**  
     * if the text field will be empty, it will  return false
     * if the rythm marking will be in the text field, it will return true else false
     * the boolean value will help to determine the toogle switch  
     whether to switch it to Rhythm Mode or Non-Rhythm Mode.
     
     * **/
bool isRhythm(string str)
{
    
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '-' || str[i] == '_' || str[i] == ' '){
            return true;
            break;
        }
    }
    return false;

}