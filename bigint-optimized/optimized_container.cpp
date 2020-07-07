#include "optimized_container.h"

optimized_container::optimized_container() : size_(0), is_small(true) {}

optimized_container::optimized_container(uint32_t x) : size_(1), is_small(true)
{
    num.value[0] = x;
}

optimized_container::optimized_container(optimized_container const &other) : size_(other.size_), is_small(other.is_small)
{
    if (is_small) {
        std::copy(other.num.value, other.num.value + size_, num.value);
    } else {
        num.data = other.num.data;
        num.data->increase_ref();
    }
}

optimized_container::~optimized_container()
{
    if (!is_small) {
        num.data->decrease_ref();
    }
}

void optimized_container::push_back(uint32_t x)
{
    if (!is_small) {
        unshare();
        num.data->push_back(x);
    } else {
        if (size_ == MAX_SZ) {
            is_small = false;
            std::vector<uint32_t> tmp(num.value, num.value + size_);
            tmp.push_back(x);
            num.data = new shared_pointer(tmp);
        } else {
            num.value[size_] = x;
        }
    }
    size_++;
}

void optimized_container::pop_back()
{
    if (!is_small) {
        unshare();
        num.data->pop_back();
    }
    size_--;
}

void optimized_container::reverse()
{
    if (!is_small) {
        unshare();
        num.data->reverse();
    } else {
        std::reverse(num.value, num.value + size_);
    }
}

size_t optimized_container::size() const
{
    return size_;
}

uint32_t const& optimized_container::operator[](size_t ind) const
{
    return (!is_small ? (*num.data)[ind] : num.value[ind]);
}

uint32_t& optimized_container::operator[](size_t ind)
{
    if (is_small) {
        return num.value[ind];
    } else {
        unshare();
        return (*num.data)[ind];
    }
}

uint32_t optimized_container::back() const
{
    return is_small ? num.value[size_ - 1] : num.data->back();
}

optimized_container &optimized_container::operator=(optimized_container const& other)
{
    if (*this == other) {
        return *this;
    }
    this->~optimized_container();
    size_ = other.size_;
    is_small = other.is_small;
    if (is_small) {
        std::copy(other.num.value, other.num.value + size_, num.value);
    } else  {
        num.data = other.num.data;
        num.data->increase_ref();
    }
    return *this;
}

bool operator==(const optimized_container &first, const optimized_container &second)
{
    if (first.size() != second.size()) {
        return false;
    }
    for (size_t i = 0; i < first.size(); i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}

void optimized_container::unshare()
{
    num.data = num.data->release();
}
