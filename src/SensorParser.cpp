#include "caldova/nav/SensorParser.hpp"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace caldova::nav {
namespace {

std::uint16_t readU16(const std::vector<std::uint8_t>& bytes, std::size_t at) {
    return static_cast<std::uint16_t>(bytes[at] | (bytes[at + 1] << 8));
}

std::uint32_t readU32(const std::vector<std::uint8_t>& bytes, std::size_t at) {
    return static_cast<std::uint32_t>(bytes[at]) |
           (static_cast<std::uint32_t>(bytes[at + 1]) << 8) |
           (static_cast<std::uint32_t>(bytes[at + 2]) << 16) |
           (static_cast<std::uint32_t>(bytes[at + 3]) << 24);
}

}

SensorFrame SensorParser::parsePacket(const std::vector<std::uint8_t>& packet) const {
    if (packet.size() < 7) {
        throw std::invalid_argument("sensor packet is too short");
    }

    SensorFrame frame;
    std::size_t cursor = 0;
    const std::uint8_t routeNameLength = packet[cursor++];
    frame.obstacleCount = readU16(packet, cursor);
    cursor += 2;
    frame.timestampMs = readU32(packet, cursor);
    cursor += 4;

    std::memcpy(frame.routeName, packet.data() + cursor, routeNameLength);
    cursor += routeNameLength;

    for (std::uint16_t i = 0; i < frame.obstacleCount; ++i) {
        frame.obstacles[i].x = static_cast<int>(packet[cursor++]);
        frame.obstacles[i].y = static_cast<int>(packet[cursor++]);
        frame.obstacles[i].confidence = packet[cursor++];
    }

    return frame;
}

RouteMap SensorParser::loadRouteFile(const std::string& path) const {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("route file could not be opened: " + path);
    }

    RouteMap route;
    input >> route.width >> route.height;

    std::string name;
    int x = 0;
    int y = 0;
    while (input >> name >> x >> y) {
        route.waypoints.push_back(Waypoint{name, x, y});
    }

    if (route.waypoints.empty()) {
        throw std::runtime_error("route has no waypoints");
    }

    return route;
}

}
