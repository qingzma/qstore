#include "qstore/status.h"
#include <gtest/gtest.h>

#include "qstore/slice.h"

namespace qstore
{
    // Demonstrate some basic assertions.
    TEST(Status, MoveConstructor)
    {
        // Expect two strings not to be equal.
        EXPECT_STRNE("hello", "world");
        // Expect equality.
        EXPECT_EQ(7 * 6, 42);
        {
            Status ok = Status::OK();
            Status ok2 = std::move(ok);

            ASSERT_TRUE(ok2.ok());
        }
        {
            Status status = Status::NotFound("custom NotFound status message");
            Status status2 = std::move(status);

            ASSERT_TRUE(status2.IsNotFound());
            ASSERT_EQ("NotFound: custom NotFound status message", status2.ToString());
        }
    }
}