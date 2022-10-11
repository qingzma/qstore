#ifndef QSTORE_INCLUDE_WRITE_BATCH_H_H
#define QSTORE_INCLUDE_WRITE_BATCH_H_H

#include <string>
#include "qstore/export.h"
#include "qstore/status.h"

namespace qstore
{
    class Slice;
    class QSTORE_EXPORT WriteBatch
    {
    private:
        friend class WriteBatchInternal;
        std::string rep_;

    public:
        class QSTORE_EXPORT Handler
        {
        public:
            virtual ~Handler();
            virtual void Put(const Slice &key, const Slice &value) = 0;
            virtual void Delete(const Slice &key) = 0;
        };
        WriteBatch();
        WriteBatch(const WriteBatch &) = default;
        WriteBatch &operator=(const WriteBatch &) = default;
        ~WriteBatch();

        void Put(const Slice &key, const Slice &value);
        void Delete(const Slice &key);
        void Clear();
        size_t ApproximateSize() const;
        void Append(const WriteBatch &souce);
        Status Iterate(Handler *handler) const;
    };

}

#endif // QSTORE_INCLUDE_WRITE_BATCH_H_H