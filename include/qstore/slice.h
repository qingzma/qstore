#ifndef STORAGE_QSTORE_INCLUDE_SLICE_H_
#define STORAGE_QSTORE_INCLUDE_SLICE_H_

#include <cassert>
#include <cstddef>
#include <string>
#include <cstring>
#include "qstore/export.h"

namespace qstore
{
    class QSTORE_EXPORT Slice
    {
    private:
        const char *data_;
        size_t size_;

    public:
        // create an empty slice.
        Slice() : data_(""), size_(0) {}
        Slice(const char *d, size_t n) : data_(d), size_(n) {}
        Slice(const char *d) : data_(d), size_(strlen(d)) {}
        Slice(const std::string &s) : data_(s.data()), size_(s.size()) {}

        // copy
        Slice(const Slice &) = default;
        Slice &operator=(const Slice &) = default;

        const char *data() const { return data_; }
        size_t size() const { return size_; }
        bool empty() const { return size_ == 0; }

        char operator[](size_t n) const
        {
            assert(n < size());
            return data_[n];
        }

        void clear()
        {
            data_ = "";
            size_ = 0;
        }

        void remove_prefix(size_t n)
        {
            assert(n <= size());
            data_ += n;
            size_ -= n;
        }

        std::string ToString() const { return std::string(data_, size_); }

        int compare(const Slice &b) const;

        bool starts_with(const Slice &x) const
        {
            return ((size_ >= x.size_) && (memcmp(data_, x.data_, x.size_) == 0));
        }
    };
    inline bool operator==(const Slice &x, const Slice &y)
    {
        return (x.size() == y.size()) && (memcmp(x.data(), y.data(), x.size() == 0));
    };

    inline bool operator!=(const Slice &x, const Slice &y)
    {
        return !(x == y);
    }

    inline int Slice::compare(const Slice &b) const
    {
        const size_t min_len = (size_ < b.size_ ? size_ : b.size_);
        int r = memcmp(data_, b.data_, min_len);
        if (r == 0)
        {
            if (size_ < b.size_)
                r = -1;
            else if (size_ > b.size_)
                r = +1;
        }
        return r;
    }
}
#endif // STORAGE_QSTORE_INCLUDE_SLICE_H_