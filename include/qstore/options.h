#pragma once

#include <cstddef>

#include "qstore/export.h"

namespace qstore
{
    class Cache;
    class Comparator;
    class Env;
    class FilterPolicy;
    class Logger;
    class Snapshot;

    enum CompressionType
    {
        kNoCompression = 0x0,
        kSnappyCompression = 0x1
    };

    struct QSTORE_EXPORT Options
    {
        const Comparator *comparator;
        bool create_if_missing = false;
        bool error_if_exists = false;
        bool paranoid_checks = false;
        Env *env;

        Logger *info_log = nullptr;
        size_t write_buffer_size = 4 * 1024 * 1024;

        int max_open_files = 1000;
        Cache *block_cache = nullptr;
        size_t block_size = 4 * 1024;

        size_t block_restart_interval = 16;
        size_t max_file_size = 2 * 1024 * 1024;

        CompressionType compression = kSnappyCompression;
        bool reuse_logs = false;

        const FilterPolicy *filter_policy = nullptr;
    };

    struct QSTORE_EXPORT ReadOptions
    {
        bool verify_checksums = false;
        bool fill_cache = true;
        const Snapshot *snapshot = nullptr;
    };

    struct QSTORE_EXPORT WriteOptions
    {
        WriteOptions() = default;
        bool sync = false;
    };

}