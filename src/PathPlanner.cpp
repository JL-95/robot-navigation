#include "robobites/nav/PathPlanner.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace robobites::nav {
namespace {

int stepToward(int current, int target) {
    if (current < target) {
        return current + 1;
    }
    if (current > target) {
        return current - 1;
    }
    return current;
}

}

CostGrid::CostGrid(int width, int height)
    : width_(width), height_(height), cells_(width * height, 1) {
    if (width_ <= 0 || height_ <= 0) {
        throw std::invalid_argument("grid dimensions must be positive");
    }
}

void CostGrid::applySensorFrame(const SensorFrame& frame) {
    for (std::uint16_t i = 0; i < frame.obstacleCount; ++i) {
        const auto& obstacle = frame.obstacles[i];
        if (obstacle.confidence < 40) {
            continue;
        }
        cells_[offset(obstacle.x, obstacle.y)] = 25;
    }
}

int CostGrid::costAt(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        return 100;
    }
    return cells_[offset(x, y)];
}

int CostGrid::width() const {
    return width_;
}

int CostGrid::height() const {
    return height_;
}

int CostGrid::offset(int x, int y) const {
    return y * width_ + x;
}

PathBuffer PathPlanner::plan(const RouteMap& route, const SensorFrame& frame) const {
    CostGrid grid(route.width, route.height);
    grid.applySensorFrame(frame);

    PathBuffer path;
    if (route.waypoints.size() < 2) {
        return path;
    }

    int x = route.waypoints.front().x;
    int y = route.waypoints.front().y;
    path.points.push_back(PathPoint{x, y});

    for (std::size_t wp = 1; wp < route.waypoints.size(); ++wp) {
        const auto& target = route.waypoints[wp];
        int guard = grid.width() * grid.height();
        while ((x != target.x || y != target.y) && guard-- > 0) {
            const int nextX = stepToward(x, target.x);
            const int nextY = stepToward(y, target.y);
            if (grid.costAt(nextX, y) <= grid.costAt(x, nextY)) {
                x = nextX;
            } else {
                y = nextY;
            }
            path.points.push_back(PathPoint{x, y});
        }
    }

    return path;
}

}
