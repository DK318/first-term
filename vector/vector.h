#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <utility>
#include <iostream>

template <typename T>
struct vector {
    using iterator = T*;
    using const_iterator = T const*;

    // O(1) nothrow
    vector() {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    // O(N) strong
    vector(vector const &other) {
        if (other.size_ != 0) {
            data_ = static_cast<T *> (operator new(other.size() * sizeof(T)));
        } else {
            data_ = nullptr;
        }
        size_t pos = 0;
        try {
            for (; pos < other.size(); pos++) {
                new(data_ + pos) T(other.data_[pos]);
            }
        } catch (...) {
            while (pos != 0) {
                data_[pos - 1].~T();
                pos--;
            }
            operator delete(data_);
            throw;
        }
        size_ = other.size_;
        capacity_ = size_;
    }

    // O(N) strong
    vector &operator=(vector const &other) {
        vector<T> result(other);
        swap(result);
        return *this;
    }

    // O(N) nothrow
    ~vector() {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
        operator delete(data_);
    }

    // O(1) nothrow
    T &operator[](size_t i) {
        return data_[i];
    }

    // O(1) nothrow
    T const &operator[](size_t i) const {
        return data_[i];
    }

    // O(1) nothrow
    T *data() {
        return data_;
    }

    // O(1) nothrow
    T const *data() const {
        return data_;
    }

    // O(1) nothrow
    size_t size() const {
        return size_;
    }

    // O(1) nothrow
    T &front() {
        return data_[0];
    }

    // O(1) nothrow
    T const &front() const {
        return data_[0];
    }

    // O(1) nothrow
    T &back() {
        return data_[size_ - 1];
    }

    // O(1) nothrow
    T const &back() const {
        return data_[size_ - 1];
    }

    // O(1)* strong
    void push_back(T const &val) {
        if (size_ == capacity_) {
            T tmp(val);
            reserve(calculate_capacity());
            new(data_ + size_) T(tmp);
        } else {
            new(data_ + size_) T(val);
        }
        size_++;
    }

    // O(1) nothrow
    void pop_back() {
        data_[--size_].~T();
    }

    // O(1) nothrow
    bool empty() const {
        return size_ == 0;
    }

    // O(1) nothrow
    size_t capacity() const {
        return capacity_;
    }

    // O(N) strong
    void reserve(size_t how_much) {
        if (how_much > capacity_) {
            vector<T> tmp;
            tmp.data_ = static_cast<T *>(operator new (how_much * sizeof(T)));
            tmp.capacity_ = how_much;
            for (size_t i = 0; i < size_; i++) {
                tmp.push_back(data_[i]);
            }
            swap(tmp);
        }
    }

    // O(N) strong
    void shrink_to_fit() {
        if (size_ == capacity_) {
            return;
        }
        vector<T> tmp(*this);
        swap(tmp);
    }

    // O(N) nothrow
    void clear() {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
        size_ = 0;
    }

    // O(1) nothrow
    void swap(vector &other) {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    // O(1) nothrow
    iterator begin() {
        return data_;
    }

    // O(1) nothrow
    iterator end() {
        return data_ + size_;
    }

    // O(1) nothrow
    const_iterator begin() const {
        return data_;
    }

    // O(1) nothrow
    const_iterator end() const {
        return data_ + size_;
    }

    // O(N) weak
    iterator insert(const_iterator pos, T const &val) {
        size_t position = pos - data_;
        push_back(val);
        for (size_t i = size_ - 1; i > position; i--) {
            std::swap(data_[i], data_[i - 1]);
        }
        return data_ + position;
    }

    // O(N) weak
    iterator erase(const_iterator pos) {
        size_t position = pos - data_;
        for (size_t i = position; i < size_ - 1; i++) {
            std::swap(data_[i], data_[i + 1]);
        }
        pop_back();
        return data_ + position;
    }

    // O(N) weak
    iterator erase(const_iterator first, const_iterator last) {
        size_t diff = last - first;
        size_t first_pos = first - data_;
        for (size_t i = first_pos; i < size_ - diff; i++) {
            std::swap(data_[i], data_[i + diff]);
        }
        for (size_t i = size_ - diff; i < size_; i++) {
            data_[i].~T();
        }
        size_ -= diff;
        return data_ + first_pos;
    }

private:
    T *data_;
    size_t size_;
    size_t capacity_;

    size_t calculate_capacity() {
        return capacity_ == 0 ? 1 : 2 * capacity_;
    }
};

#endif // !VECTOR_H
