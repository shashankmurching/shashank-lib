// Vector header file

#ifndef SL_VECTOR_H
#define SL_VECTOR_H

#include <stddef.h>
#include <stdexcept>

namespace SL {

template<class T>
class vector {

public:
    // Ctor - range w/ iterator
    // begin
    // end
    // index

    vector() {
        this->_size = 0;
        this->_capacity = 0;
        this->_data = new T[this->_size];
    }

    vector(size_t count, T val) {
        this->_size = count;
        this->_capacity = count;
        this->_data = new T[this->_capacity];
    
        for (int i = 0; i < this->_size; i++) {
            this->_data[i] = val;
        }
    }

    vector(const vector& v) {
        this->_size = v.size();
        this->_capacity = v.capacity();
        this->_data = new T[this->_capacity];

        for (int i = 0; i < this->_size; i++) {
            this->_data[i] = v._data[i];
        }
    }

    ~vector() {
        delete[] this->_data;
    }

// Capacity:
    size_t size() {
        return this->_size;
    }

    void resize(size_t size) {
        T temp;
        resize(size, temp);
    }

    void resize(size_t size, const T& val) {
        // if n < size
            // content reduced to first n elements + destroying those beyond
        // if n > size
            // if n > capacity -> auto reallocation
            // insert elements to get to size
    }

    size_t capacity() {
        return this->_capacity;
    }

    bool empty() {
        return this->_size == 0;
    }

    void reserve(size_t capacity) {
        if (this->capacity_ < capacity) {
            this->_reallocate(capacity);
        }
    }

    void shrink_to_fit() {
        // reduce capacity to fit current size
            // container impl can optimize and leave vector w/ capacity > size
    }


// Element access
    // operator[], at, front, back, data

// Modifiers
    void push_back(T val) {
        if (this->_size == this->_capacity) {
            this->reallocate();
        }

        this->_data[this->_size++] = val;
    }

    void pop_back() {
        if (this->empty()) {
            throw std::out_of_range("Cannot pop_back on an empty vector.");
        }

        this->size_--;
        // TODO: deallocate last index?
    }

    // insert, erase, swap, clear, emplace, emplace_back


private:
    const size_t _defaultSize = 10;
    const size_t _reallocModifier = 2;

    size_t _size;
    size_t _capacity;
    T* _data;

    void reallocate() {
        reallocate(this->_capacity * this->_reallocModifier);
    }

    void reallocate(size_t capacity) {
        this->_capacity = capacity;
        T* temp = new T[this->_capacity];

        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->_data[i];
        }

        delete[] this->_data;
        this->_data = temp;        
    }
};

}

#endif