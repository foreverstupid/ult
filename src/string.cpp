#include "headers/string.hpp"

int String::getLength(const char *str)
{
    int i = 0;

    if(str){
        for(; str[i]; i++);
    }

    return i;
}



String::String(const char *str)
{
    size = getLength(str);
    storage = new char[size + 1];
    pos = size;

    copy(storage, str, size + 1);
}



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
