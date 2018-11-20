#include "headers/string.hpp"

bool String::operator==(const char *str) const
{
    int i;

    for(i = 0; i < pos; i++){
        if(!str[i] || str[i] != storage[i]){
            return false;
        }
    }

    if(str[i]){
        return false;
    }else{
        return true;
    }
}
