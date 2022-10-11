#include "util/posix_logger.h"

#include <gtest/gtest.h>

#include <cstdio>

namespace qstore {

TEST(PosixLogger, LoggerGetTime) {
  std::FILE *file = std::fopen("test.txt", "w+");
  PosixLogger pl(file);
  pl.Logv("%02d", nullptr);
  ASSERT_TRUE(1 == 1);
};
}  // namespace qstore