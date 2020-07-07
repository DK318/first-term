#include "shared_pointer.h"

shared_pointer::shared_pointer() : digits(), ref_cnt(1) {}

shared_pointer::shared_pointer(const std::vector<uint32_t> &other) : digits(other), ref_cnt(1) {}

shared_pointer::shared_pointer(const shared_pointer &other) : digits(other.digits), ref_cnt(1) {}

bool shared_pointer::is_unique()
{
    return ref_cnt == 1;
}

shared_pointer *shared_pointer::release()
{
    if (is_unique()) {
        return this;
    } else {
        ref_cnt--;
        return new shared_pointer(*this);
    }
}

void shared_pointer::increase_ref()
{
    ref_cnt++;
}

void shared_pointer::decrease_ref()
{
    if (ref_cnt == 1) {
        delete this;
    } else {
        ref_cnt--;
    }
}

void shared_pointer::reverse()
{
    std::reverse(digits.begin(), digits.end());
}

void shared_pointer::push_back(uint32_t val)
{
    digits.push_back(val);
}

void shared_pointer::pop_back()
{
    digits.pop_back();
}

const uint32_t &shared_pointer::operator[](size_t ind) const
{
    return digits[ind];
}

uint32_t &shared_pointer::operator[](size_t ind)
{
    return digits[ind];
}

uint32_t shared_pointer::back() const
{
    return digits.back();
}
