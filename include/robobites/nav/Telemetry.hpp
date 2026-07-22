#pragma once

#include "robobites/nav/Types.hpp"
#include <string>

namespace robobites::nav {

class Telemetry {
public:
    std::string summarizeRoute(const RouteMap& route) const;
    std::string nextCommand(const PathBuffer& path) const;
};

}
