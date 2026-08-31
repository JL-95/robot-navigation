#pragma once

#include "caldova/nav/Types.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace caldova::nav {

class SensorParser {
public:
    SensorFrame parsePacket(const std::vector<std::uint8_t>& packet) const;
    RouteMap loadRouteFile(const std::string& path) const;
};

}
