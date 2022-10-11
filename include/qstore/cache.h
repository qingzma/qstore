#ifndef QSTORE_INCLUDE_CACHE_H_
#define QSTORE_INCLUDE_CACHE_H_
#include <cstdint>
#include "qstore/export.h"
#include "qstore/slice.h"

namespace qstore
{
    class QSTORE_EXPORT Cache;
    QSTORE_EXPORT Cache *NewLRUCache(size_t capacity);
    class QSTORE_EXPORT Cache
    {
    public:
        Cache() = default;
        Cache(const Cache &) = delete;
        Cache &operator=(const Cache &) = delete;
        virtual ~Cache();

        struct Handle
        {
        };

        virtual Handle *Insert(const Slice &key, void *value, size_t charge,
                               void (*deleter)(const Slice &key, void *value)) = 0;
        virtual Handle *Lookup(const Slice &key) = 0;

        virtual void Release(Handle *handle) = 0;
        virtual void Value(Handle *handle) = 0;
        virtual void Erase(const Slice &key) = 0;
        virtual uint64_t NewId() = 0;

        virtual void Prune() {}

        virtual size_t TotalCharge() const = 0;
    };
}

#endif // QSTORE_INCLUDE_CACHE_H_