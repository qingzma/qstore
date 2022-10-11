#ifndef STORE_QSTORE_INCLUDE_ITERATOR_H
#define STORE_QSTORE_INCLUDE_ITERATOR_H

#include "qstore/slice.h"
#include "qstore/status.h"
#include "qstore/export.h"

namespace qstore
{
    class QSTORE_EXPORT Iterator
    {
    private:
        struct CleanupNode
        {
            bool IsEmpty() const { return function == nullptr; }
            void Run()
            {
                assert(function != nullptr);
                (*function)(arg1, arg2);
            }
            CleanupFunction function;
            void *arg1;
            void *arg2;
            CleanupNode *next;
        };

        CleanupNode cleanup_head_;

    public:
        Iterator();
        Iterator(const Iterator &) = delete;
        Iterator &operator=(const Iterator &) = delete;
        virtual ~Iterator();

        virtual bool Valid() const = 0;
        virtual void SeekToFirst() = 0;
        virtual void SeekToLast() = 0;
        virtual void Seek(const Slice &target) = 0;
        virtual void Next() = 0;
        virtual void Prev() = 0;
        virtual Slice key() const = 0;
        virtual slice value() const = 0;
        virtual Status status() const = 0;

        using CleanupFunction = void (*)(void *arg1, void *arg2);
        void RegisterCleanup(CleanupFunction function, void *arg1, void *arg2);
    };

    QSTORE_EXPORT Iterator *NewEmptyIterator();
    QSTORE_EXPORT Iterator *NewErrorIterator(const Status &status);
}

#endif // STORE_QSTORE_INCLUDE_ITERATOR_H