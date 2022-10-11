#pragma once

#include <string>
#include "qstore/export.h"

namespace qstore
{
    class Slice;

    class QSTORE_EXPORT Comparator
    {
    public:
        virtual ~Comparator();
        virtual int Compare(const Slice &a, const Slice &b) const = 0;
        virtual const char *Name() const = 0;
        virtual FindShortestSeparator(std::string *start, const Slice &limit) const = 0;

        virtual void FindShortSuccessor(std::string *key) const = 0;
    };

    QSTORE_EXPORT const Comparator *BytewiseComparator();
}
