#ifndef QSTORE_INCLUDE_TABLE_BUILDER_H_
#define QSTORE_INCLUDE_TABLE_BUILDER_H_

#include <cstdint>
#include "qstore/export.h"
#include "qstore/options.h"
#include "qstore/status.h"

namespace qstore
{
    class BlockBuilder;
    class BlockHandle;
    class WritableFile;

    class QSTORE_EXPORT TableBuilder
    {
    private:
        bool ok() { return status().ok(); }
        void writeBlock(BlockBuilder *block, BlockHandle *handle);
        void WriteRawBlock(const Slice &data, CompressionType, BlockHandle *handle);

        struct Rep;
        Rep *rep_;

    public:
        TableBuilder(const Options &options, WritableFile *file);
        TableBuilder(const TableBuilder &) = delete;
        TableBuilder &operator=(const TableBuilder &) = delete;
        ~TableBuilder();

        Status ChangeOptions(const Options &options);
        void Add(const Slice &key, const Slice &value);
        void Flush();
        Status status() const;
        Status Finish();
        void Abandon();
        uint64_t NumEntries() const;
        uint64_t FileSize() const;
    };

}

#endif // QSTORE_INCLUDE_TABLE_BUILDER_H_