#ifndef QSTORE_INCLUDE_DB_H_
#define QSTORE_INCLUDE_DB_H_

#include <cstdint>
#include "qstore/export.h"
#include "qstore/iterator.h"
#include "qstore/options.h"

namespace qstore
{
    static const int kMajorVersion = 1;
    static const int kMinorVersion = 0;
    struct Options;
    struct ReadOptions;
    struct WriteOptions;
    class WriteBatch;

    class QSOTRE_EXPORT Snapshot
    {
    protected:
        virtual ~Snapshot();
    };

    struct QSTORE_EXPORT Range
    {
        Slice start;
        Slice limit;
        Range() = default;
        Range(const Slice &s, const Slice &l) : start(s), limit(l){};
    };

    class QSTORE_EXPORT DB
    {
        DB() = default;
        DB(const DB &) = delete;
        DB &operator=(const DB &) = delete;
        virtual ~DB();

        static Status Open(const Options *options, const std::string &name, DB **dbptr);
        virtual Status Put(const WriteOptions &options, const Slice &key, const Slice &value) = 0;
        virtual Status Delete(const WriteOptions &options, const Slice &key) = 0;
        virtual Status Write(const WriteOptions &options, WriteBatch *updates) = 0;
        virtual Status Get(const ReadOptions &options, const Slice &key, std::string *value) = 0;

        virtual Iterator *NewIterator(const ReadOptions &options) = 0;
        virtual const Snapshot *GetSnapshot() = 0;
        virtual void ReleaseSnapshot(const Snapshot *snapshot) = 0;
        virtual bool GetProperty(const Slice &property, std::string *value) = 0;

        virtual void GetApproximateSizes(const Range *range, int n, uint64_t *sizes) = 0;
        virtual void CompactRange(const Slice *begin, const Slice *end) = 0;
    };

    QSTORE_EXPORT Status DestroyDB(const std::string &name, const Options &options);

    QSTORE_EXPORT Status RepairDB(const std::string &name, const Options &options);

}
#endif // QSTORE_INCLUDE_DB_H_