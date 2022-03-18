#pragma 
#include "misc.h"

namespace Basalt
{
    struct NodeId
    {
        uint32_t id;
        size_t deserialize(uint8_t* output) const;
        bool operator==(const NodeId& other) const;
        constexpr size_t dataSize() const { return 4; }
        static NodeId null() { return NodeId{0}; }
    };
    
} // namespace Basalt

