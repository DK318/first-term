#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include <vector>
#include <cstdint>

struct shared_pointer {
    shared_pointer();
    shared_pointer(std::vector<uint32_t> const &);
    bool unique();

    std::vector<uint32_t> digits;
    size_t ref_cnt;
};

#endif // SHARED_POINTER_H
