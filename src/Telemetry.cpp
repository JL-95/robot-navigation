#include "robobites/nav/Telemetry.hpp"

#include <sstream>

namespace robobites::nav {

std::string Telemetry::summarizeRoute(const RouteMap& route) const {
    std::ostringstream out;
    out << "route " << route.width << "x" << route.height << " with "
        << route.waypoints.size() << " stops";
    if (!route.waypoints.empty()) {
        out << ", starting at " << route.waypoints.front().name;
    }
    return out.str();
}

std::string Telemetry::nextCommand(const PathBuffer& path) const {
    if (path.points.size() < 2) {
        return "hold position";
    }

    const auto& from = path.points[0];
    const auto& to = path.points[1];
    std::ostringstream out;
    out << "move from (" << from.x << "," << from.y << ") to ("
        << to.x << "," << to.y << ")";
    return out.str();
}

}
