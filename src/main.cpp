#include "robobites/nav/PathPlanner.hpp"
#include "robobites/nav/RouteCache.hpp"
#include "robobites/nav/SensorParser.hpp"
#include "robobites/nav/Telemetry.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using robobites::nav::PathPlanner;
using robobites::nav::RouteCache;
using robobites::nav::SensorParser;
using robobites::nav::Telemetry;

namespace {

std::vector<std::uint8_t> roverSensorFrame() {
    std::vector<std::uint8_t> bytes;
    const std::string route = "downtown";
    bytes.push_back(static_cast<std::uint8_t>(route.size()));
    bytes.push_back(2);
    bytes.push_back(0);
    bytes.push_back(0x40);
    bytes.push_back(0x42);
    bytes.push_back(0x0f);
    bytes.push_back(0);
    bytes.insert(bytes.end(), route.begin(), route.end());
    bytes.push_back(7);
    bytes.push_back(4);
    bytes.push_back(86);
    bytes.push_back(9);
    bytes.push_back(5);
    bytes.push_back(35);
    return bytes;
}

void runNavigationTick(const std::string& routeFile, RouteCache& cache) {
    SensorParser parser;
    PathPlanner planner;
    Telemetry telemetry;

    auto priorPath = cache.restore();
    if (!priorPath.points.empty()) {
        std::cout << "cached " << telemetry.nextCommand(priorPath) << '\n';
    }

    const auto route = parser.loadRouteFile(routeFile);
    const auto frame = parser.parsePacket(roverSensorFrame());
    const auto path = planner.plan(route, frame);

    std::cout << telemetry.summarizeRoute(route) << '\n';
    std::cout << telemetry.nextCommand(path) << '\n';
    cache.remember(path);
}

}

int main(int argc, char** argv) {
    const std::string routeFile = argc > 1 ? argv[1] : "config\\downtown.route";
    RouteCache cache;

    try {
        runNavigationTick(routeFile, cache);
        runNavigationTick(routeFile, cache);
    } catch (const std::exception& error) {
        std::cerr << "navigation stopped: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
