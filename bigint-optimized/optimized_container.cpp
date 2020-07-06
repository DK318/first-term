#include "optimized_container.h"

optimized_container::optimized_container() : is_empty(true), is_small(false) {}

optimized_container::optimized_container(uint32_t x) : is_empty(false), is_small(true)
{
    num.value = x;
}

optimized_container::optimized_container(optimized_container const &other) : is_empty(other.is_empty), is_small(other.is_small)
{
    if (is_small) {
        num.value = other.num.value;
    } else if (!is_empty) {
        num.data = other.num.data;
        num.data->ref_cnt++;
    }
}

optimized_container::~optimized_container()
{
    if (!is_small && !is_empty) {
        if (num.data->ref_cnt == 1) {
            delete num.data;
        } else {
            num.data->ref_cnt--;
        }
    }
}

void optimized_container::push_back(uint32_t x)
{
    if (is_empty) {
        is_empty = false;
        is_small = true;
        num.value = x;
    } else if (is_small) {
        is_small = false;
        num.data = new shared_pointer(std::vector<uint32_t>({num.value, x}));
    } else {
        unshare();
        num.data->digits.push_back(x);
    }
}

void optimized_container::pop_back()
{
    if (!is_small && !is_empty) {
        if (num.data->digits.size() == 2) {
            uint32_t tmp = num.data->digits[0];
            num.data->ref_cnt--;
            if (num.data->ref_cnt == 0) {
                delete num.data;
            }
            num.value = tmp;
            is_small = true;
        } else {
            unshare();
            num.data->digits.pop_back();
        }
    } else {
        is_empty = true;
    }
}

void optimized_container::reverse()
{
    if (!is_empty && !is_small) {
        unshare();
        std::reverse(num.data->digits.begin(), num.data->digits.end());
    }
}

size_t optimized_container::size() const
{
    return (is_small ? (is_empty ? 0 : 1) : num.data->digits.size());
}

uint32_t const& optimized_container::operator[](size_t ind) const
{
    return is_small ? num.value : num.data->digits[ind];
}

uint32_t& optimized_container::operator[](size_t ind)
{
    if (is_small) {
        return num.value;
    } else {
        unshare();
        return num.data->digits[ind];
    }
}

uint32_t optimized_container::back() const
{
    return is_small ? num.value : num.data->digits.back();
}

optimized_container &optimized_container::operator=(optimized_container const& other)
{
    if (*this == other) {
        return *this;
    }
    this->~optimized_container();
    is_empty = other.is_empty;
    is_small = other.is_small;
    if (is_small) {
        num.value = other.num.value;
    } else if (!is_empty) {
        num.data = other.num.data;
        num.data->ref_cnt++;
    }
    return *this;
}

bool operator==(const optimized_container &first, const optimized_container &second)
{
    if (first.size() != second.size())
        return false;
    for (size_t i = 0; i < first.size(); i++) {
        if (first[i] != second[i])
            return false;
    }
    return true;
}

void optimized_container::unshare()
{
    if (!num.data->unique()) {
        num.data->ref_cnt--;
        num.data = new shared_pointer(num.data->digits);
    }
}
