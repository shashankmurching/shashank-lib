// Vector header file

#ifndef SL_VECTOR_H
#define SL_VECTOR_H

#include <string>
#include <stddef.h>
#include <stdexcept>

namespace SL {

template<class T>
class vector {

public:
    // Iterator - range constructor, begin, end, dereference, insert, erase

    vector() {
        size_ = 0;
        capacity_ = 0;
        data_ = new T[capacity_];
    }

    vector(size_t count, T val) {
        size_ = count;
        capacity_ = count;
        data_ = new T[capacity_];
    
        for (size_t i = 0; i < size_; i++) {
            data_[i] = val;
        }
    }

    vector(const vector& rhs) {
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            data_[i] = rhs.data_[i];
        }
    }

    vector& operator=(const vector& rhs) { // assign
        delete[] data_;
        this->vector(rhs);
    }

    vector& operator= (vector&& rhs) { // move
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;

        delete[] data_;
        data_ = rhs.data_;
    
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
    }

    ~vector() {
        delete[] data_;
    }

// Capacity:
    size_t size() {
        return size_;
    }

    void resize(size_t size) {
        T temp = T{};
        resize(size, temp);
    }

    void resize(size_t n, const T& val) {
        if (n < size_) {
            destroyRange(n, size_ - n);
        }
        else if (n > size_) {
            size_t oldSize = size_;
            reallocate(n);

            for (size_t i = oldSize; i < n; i++) {
                data_[i] = val;
            }
        }

        size_ = n;
    }

    size_t capacity() {
        return capacity_;
    }

    bool empty() {
        return size_ == 0;
    }

    void clear() {
        destroyRange(0, size_);
        size_ = 0;
    }

    void swap (vector& rhs) {
        size_t tempSize = size_;
        size_t tempCapacity = capacity_;
        T* data tempData = data_;

        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        data_ = rhs.data_;

        rhs.size_ = tempSize;
        rhs.capacity_ = tempCapacity;
        rhs.data_ = tempData;
    }

    void reserve(size_t capacity) {
        if (capacity_ < capacity) {
            reallocate(capacity);
        }
    }

    const T& operator[](size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    T& operator[](size_t index) {
        checkIndex(index);
        return data_[index];
    }    

    const T& at(size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    T& at(size_t index) {
        checkIndex(index);
        return data_[index];
    }

    const T& front() const {
        checkIndex(0);
        return data_[0];
    }

    T& front() {
        checkIndex(0);
        return data_[0];
    }

    const T& back() const {
        int index = size_ - 1;
        checkIndex(index);
        return data_[index];
    }

    T& back() {
        int index = size_ - 1;
        checkIndex(index);
        return data_[index];
    }

    const T* data() const noexcept {
        return data_;
    }

    T* data() noexcept {
        return data_;
    }

// Modifiers
    void push_back(T val) {
        if (size_ == capacity_) {
            reallocate();
        }

        data_[size_++] = val;
    }

    void pop_back() {
        size_--;
        destroyIndex(size_);
    }

private:
    const size_t defaultSize_ = 10;
    const size_t reallocModifier_ = 2;

    size_t size_;
    size_t capacity_;
    T* data_;

    void copyHelper(const vector& rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            data_[i] = rhs.data_[i];
        }
    }

    void reallocate() {
        reallocate(capacity_ * reallocModifier_);
    }

    void reallocate(size_t capacity) {
        capacity_ = capacity;
        T* temp = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            temp[i] = data_[i];
        }

        delete[] data_;
        data_ = temp;        
    }

    void checkIndex(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Invalid index " + std::to_string(index) + " for size " + std::to_string(size_));
        }
    }

    void destroyIndex(size_t index) {
        checkIndex(index);
        data_[index]->~T();
    }

    void destroyRange(size_t index, size_t length) {
        size_t lastIndex = index + length - 1;
        checkIndex(lastIndex);
        
        for (; lastIndex >= index; lastIndex--) {
            data_[lastIndex]->~T();            
        }
    }
};

}

#endif