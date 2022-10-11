#ifndef QSTORE_INCLUDE_TABLE_H
#define QSTORE_INCLUDE_TABLE_H

#include <cstdint>

#include "qstore/export.h"
#include "qstore/iterator.h"
namespace qstore
{
    class Block;
    class BlockHandle;
    class Footer;
    struct Options;
    class RandomAccessFile;
    struct ReadOptions;
    class TableCache;
    class QSTORE_EXPORT Table
    {
    private:
        friend class TableCache;
        struct Rep;
        static Iterator *BlockReader(void *, const ReadOptions &, const Slice &);
        explicit Table(Rep *rep) : rep_(rep) {}

        Rep *const rep_;
        Status InternalGet(const ReadOptions &, const Slice &key, void *arg, void (*handle_result)(void *arg, const Slice &k, const Slice &v));

        void ReadMeta(const Footer &footer);
        void ReadFilter(const Slice &filter_handle_value);

    public:
        Table(const Table &) = delete;
        Table &operator=(const Table &) = delete;
        ~Table();
        Status Open(const Options &options, RandomAccessFile *file, uint64_t file_size, Table **table);

        Iterator *NewIterator(const ReadOptions &) const;
        uint64_t ApproximateOffSetOf(const Slice &key) const;
    };

}
#endif // QSTORE_INCLUDE_TABLE_H