#ifndef ARRAY_TEMPLATE_CLASS_HPP
#define ARRAY_TEMPLATE_CLASS_HPP

/*
 * Template class for dynamic array
 */
template <typename T>
class Array{
protected:
    T *storage;         /* storage for holding items */
    int size;           /* current real size of array */
    int pos;            /* position for writing next element */

public:
    /* copies cnt elements from dst to src */
    static void copy(T *dst, const T *src, int cnt);

    /* checks if two arrays are equal */
    static bool equal(const Array<T> &a1, const Array<T> &a2);

    Array(){ pos = 0; size = 64; storage = new T[size]; }
    Array(int sz);
    Array(const Array<T> &arr);

    T &operator[](int i){ return storage[i]; }
    const T&operator[](int i) const { return storage[i]; }
    void operator=(const Array<T> &arr);
    void operator+=(const Array<T> &arr);
    bool operator==(const Array<T> &arr) const
    {
        return equal(*this, arr);
    }
    bool operator!=(const Array<T> &arr) const
    {
        return !this->operator==(arr);
    }

    int getLength() const { return pos; }
    const T &getLast() const { return storage[pos - 1]; }
    T &getLast(){ return storage[pos - 1]; }

    /* adds element to the end of the array */
    void add(T elem);

    /* finds position of the given element */
    int find(T elem) const;

    /* extends the array for cnt elements */
    void extend(int cnt);

    virtual ~Array(){ delete[] storage; }

private:
    /* makes new storage of size elements */
    void makeStorage(int size);

    /* redoubles storage */
    void redouble();
};



template <typename T>
Array<T>::Array(int sz)
{
    size = (sz > 0) ? sz : 64;
    pos = 0;
    storage = new T[size];
}



template <typename T>
Array<T>::Array(const Array<T> &arr)
{
    size = arr.size;
    pos = arr.pos;
    storage = new T[size];
    copy(storage, arr.storage, pos);
}



template <typename T>
void Array<T>::operator=(const Array<T> &arr)
{
    if(size <= arr.pos){
        delete[] storage;
        storage = new T[arr.size];
        size = arr.size;
    }

    pos = arr.pos;
    copy(storage, arr.storage, arr.pos);
}



template <typename T>
void Array<T>::operator+=(const Array<T> &arr)
{
    T *tmp;

    if(pos + arr.pos >= size){
        tmp = new T[size + arr.size];
        copy(tmp, storage, pos);
        copy(tmp + pos, arr.storage, arr.pos);
        size += arr.size;
    }else{
        copy(storage + pos, arr.storage, arr.pos);
    }

    pos += arr.pos;
}



template <typename T>
bool Array<T>::equal(const Array<T> &a1, const Array<T> &a2)
{
    int i;

    for(i = 0; i < a1.pos; i++){
        if(i > a2.pos || a1.storage[i] != a2.storage[i]){
            return false;
        }
    }

    return i == a2.pos;
}



template <typename T>
void Array<T>::add(T elem)
{
    if(pos >= size - 1){
        redouble();
    }

    storage[pos] = elem;
    pos++;
}



template <typename T>
void Array<T>::redouble()
{
    T *tmp = new T[size * 2];

    copy(tmp, storage, size);
    delete[] storage;
    storage = tmp;

    size *= 2;
}



template <typename T>
void Array<T>::copy(T *dst, const T *src, int cnt)
{
    for(int i = 0; i < cnt; i++){
        dst[i] = src[i];
    }
}



template <typename T>
int Array<T>::find(T elem) const
{
    for(int i = 0; i < pos; i++){
        if(storage[i] == elem){
            return i;
        }
    }

    return -1;
}



template <typename T>
void Array<T>::extend(int cnt)
{
    T *tmp;

    if(pos + cnt >= size){
        tmp = new T[(pos + cnt) * 2];
        copy(tmp, storage, pos);
        delete[] storage;

        storage = tmp;
        size = (pos + cnt) * 2;
    }

    pos += cnt;
}

#endif
