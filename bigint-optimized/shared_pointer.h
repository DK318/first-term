#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include <vector>
#include <cstdint>
#include <algorithm>

struct shared_pointer {
public:
    shared_pointer();
    shared_pointer(std::vector<uint32_t> const &);
    shared_pointer(shared_pointer const &);
    bool is_unique();
    shared_pointer* unshare();
    void increase_ref();
    void decrease_ref();
    void reverse();
    void push_back(uint32_t);
    void pop_back();
    uint32_t const& operator[](size_t) const;
    uint32_t& operator[](size_t);
    uint32_t back() const;

private:
    std::vector<uint32_t> digits;
    size_t ref_cnt;
};

#endif // SHARED_POINTER_H
