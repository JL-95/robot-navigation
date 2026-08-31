#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace caldova::nav {

struct Waypoint {
    std::string name;
    int x = 0;
    int y = 0;
};

struct Obstacle {
    int x = 0;
    int y = 0;
    std::uint8_t confidence = 0;
};

struct SensorFrame {
    char routeName[32]{};
    std::array<Obstacle, 64> obstacles{};
    std::uint16_t obstacleCount = 0;
    std::uint32_t timestampMs = 0;
};

struct RouteMap {
    int width = 0;
    int height = 0;
    std::vector<Waypoint> waypoints;
};

struct PathPoint {
    int x = 0;
    int y = 0;
};

struct PathBuffer {
    std::vector<PathPoint> points;
};

} 
