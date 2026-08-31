#pragma once

#include "caldova/nav/Types.hpp"
#include <string>

namespace caldova::nav {

class Telemetry {
public:
    std::string summarizeRoute(const RouteMap& route) const;
    std::string nextCommand(const PathBuffer& path) const;
};

}
