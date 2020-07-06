#include "shared_pointer.h"

shared_pointer::shared_pointer() : digits(), ref_cnt(1) {}

shared_pointer::shared_pointer(const std::vector<uint32_t> &other) : digits(other), ref_cnt(1) {}

bool shared_pointer::unique()
{
    return ref_cnt == 1;
}
