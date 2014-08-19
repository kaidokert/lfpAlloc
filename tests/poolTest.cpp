
#include <lfpAlloc/Pool.hpp>
#include <gtest/gtest.h>

TEST(PoolTest, Allocate) {
    lfpAlloc::Pool<int, 1, 40000> pool;

    std::vector<int*> v;
    for (std::size_t s=0; s < 5e6; ++s) {
        EXPECT_NE(pool.allocate(), nullptr);
    }
}

TEST(PoolTest, Deallocate) {
    lfpAlloc::Pool<int, 1, 40000> pool;

    std::vector<int*> v;
    for (std::size_t s=0; s < 5e5; ++s) {
        auto val = pool.allocate();
        EXPECT_NE(val, nullptr);
        pool.deallocate(val);
    }

}
