#pragma once

#include "robobites/nav/Types.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace robobites::nav {

class SensorParser {
public:
    SensorFrame parsePacket(const std::vector<std::uint8_t>& packet) const;
    RouteMap loadRouteFile(const std::string& path) const;
};

}
