#include "headers/string.hpp"

bool String::opertator==(const char *str) const
{
    for(int i = 0; i < pos; i++){
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
