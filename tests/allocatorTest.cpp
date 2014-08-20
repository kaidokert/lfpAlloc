
#include <lfpAlloc/Allocator.hpp>
#include <gtest/gtest.h>
#include <list>
#include <thread>
#include <future>

TEST(AllocatorTest, Equality) {
    lfpAlloc::lfpAllocator<int, 8> allocator;
    lfpAlloc::lfpAllocator<int, 8> otherAllocator(allocator);

    EXPECT_EQ(allocator, otherAllocator);

    auto val = allocator.allocate(1);
    otherAllocator.deallocate(val, 1);
}

TEST(AllocatorTest, Allocate) {
    lfpAlloc::lfpAllocator<int> allocator;
    for (std::size_t s=0; s<5e6; ++s) {
        EXPECT_NE(allocator.allocate(1), nullptr);
    }
}

TEST(AllocatorTest, STLContainer) {
    std::list<int, lfpAlloc::lfpAllocator<int, 8>> l;
    std::vector<int, lfpAlloc::lfpAllocator<int, 8>> v;

    for (std::size_t s=0; s<5e5; ++s) {
        l.push_back(s);
        v.push_back(s);
    }
    EXPECT_TRUE(std::equal(l.begin(), l.end(), v.begin()));
}

TEST(AllocatorTest, Concurrent) {
    lfpAlloc::lfpAllocator<int, 8> allocator;
    auto future1 = std::async(std::launch::async, [&]{
        std::vector<int, lfpAlloc::lfpAllocator<int, 8>> v(allocator);
        for (std::size_t s=0; s<5e6; ++s) {
            v.push_back(s);
        }
        return v;
    });

    auto future2 = std::async(std::launch::async, [&]{
        std::vector<int, lfpAlloc::lfpAllocator<int, 8>> v(allocator);
        for (std::size_t s=0; s<5e6; ++s) {
            v.push_back(s);
        }
        return v;
    });
    auto result1 = future1.get();
    auto result2 = future2.get();
    EXPECT_TRUE(std::equal(result1.begin(), result1.end(), result2.begin()));
}
