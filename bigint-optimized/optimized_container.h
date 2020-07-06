#ifndef OPTIMIZED_CONTAINER_H
#define OPTIMIZED_CONTAINER_H

#include <cstdint>
#include <algorithm>
#include "shared_pointer.h"

struct optimized_container {
public:
    optimized_container();
    optimized_container(uint32_t);
    optimized_container(optimized_container const &);
    ~optimized_container();
    void push_back(uint32_t);
    void pop_back();
    void resize(size_t);
    void reverse();
    size_t size() const;
    uint32_t const& operator[](size_t) const;
    uint32_t& operator[](size_t);
    uint32_t back() const;
    optimized_container& operator=(optimized_container const&);
    friend bool operator==(optimized_container const&, optimized_container const&);

private:
    void unshare();

    bool is_empty;
    bool is_small;
    union {
        uint32_t value;
        shared_pointer *data;
    } num;
};

#endif // OPTIMIZED_CONTAINER_H
