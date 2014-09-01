#include <cstdint>

namespace lfpAlloc {
    namespace detail {
        template<std::size_t Count, std::size_t Val=1>
        struct Power : Power<Count-1, Val*2>{};

        template<std::size_t Val>
        struct Power<0, Val> {
            enum {
                value = Val/2
            };
        };
        
        template<std::size_t Val, std::size_t base=2>
        struct log
        {
            enum { value = 1 + log<Val/base, base>::value };
        };

        template<std::size_t base>
        struct log<1, base>
        {
            enum { value = 0 };
        };

        template<std::size_t base>
        struct log<0, base>
        {
            enum { value = 0 };
        };
    }
}
