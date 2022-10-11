#ifndef QSOTRE_INCLUDE_DUMPFILE_H_
#define QSOTRE_INCLUDE_DUMPFILE_H_
#include <string>
#include "qstore/env.h"
#include "qstore/export.h"
#include "qstore/status.h"

namespace qstore
{
    QSTORE_EXPORT Status DumpFile(Env *env, const std::string &fname, WritableFile *dst);
}
#endif // QSOTRE_INCLUDE_DUMPFILE_H_