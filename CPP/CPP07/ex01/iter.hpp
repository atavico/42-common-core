#ifndef ITER_HPP
# define ITER_HPP

template<typename T>
void    iter(T* arr, int length, void (*processFunc)(T &))
{
    for(int i = 0; i < length; i++){
        processFunc(arr[i]);
    }
}
#endif