#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array
{
    public:
        Array<T>(void):_size(0), _array(nullptr)
        {
            std::cout << "Default constructor" << std::endl;
        }
        Array<T>(unsigned int n):_size(n)
        {
            std::cout << "Size constructor" << std::endl;
            if(n < 0)
                throw std::overflow_error("Index out of bound");
            this->_array = new T[n];
        }
        Array<T>(const Array<T> &src)
        {
            std::cout << "copy constructor" << std::endl;
            this->_size = src._size;
            this->_array = new T[this->_size];
            for (int i = 0; i < this->_size; i++)
                this->_array[i] = src._array[i];
        }

        ~Array<T>(void)
        {
            std::cout << "Default destructor" << std::endl;
            if(this->_size > 0)
                delete[] this->_array;
        }
        Array<T>    &operator=(const Array<T> &other)
        {
            std::cout << "Assignment operator" << std::endl;
            if(this == &other)
                return *this;
            if (this->_size > 0)
                delete [] this->_array;
            this->_size = other._size();
            this->_array = new T[this->_size];
            for (int i = 0;i < this->_size; i++)
                this->_array[i] = other[i];
            return *this;
        }

        T   &operator[](const int index) const
        {
            if (index >= this->_size || index < 0)
                throw std::overflow_error("Index out of bound");
            return this->_array[index];
        }

        int size(void) const
        {
            return this->_size;
        }


    private:
        int _size;
        T   *_array;
};

#endif